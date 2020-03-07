/*
 * File:   LCD.c
 * Author: IBRAHIM LABS
 *
 * Created on June 23, 2013, 7:21 AM
 */

#define CRYSTAL_FREQUENCY 10000000      /*  10 MHz  */
#define FCY CRYSTAL_FREQUENCY/2UL       /*  Cylce frequency 5 MHz*/

#include <p33FJ64GS610.h>
#include <libpic30.h>
#include <stddef.h>
#include <math.h>
#include "LCD.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Initilize_LCD(void)
{
    /*  making Pins as output   */

    ENABLE_DIRECTION    = 0;
    RS_DIRECTION        = 0;
    LCD_BUS_DIRECTION   = 0;

    /*  Writing zero to pins and port   */

    ENABLE_LCD  = 0;
    RS_LCD      = 0;
    LCD_BUS     = 0;
  
   __delay_ms(10);          /*  ten miliseconds delay   */

   /*   writing commonds for initialization of LCD  */

   WriteCmd_LCD(0x38);  /*  Functions Set as Given in Datasheet */
   WriteCmd_LCD(0x0C);  /*  Display ON; Cursor OFF; Blink OFF   */
   WriteCmd_LCD(0x06);  /*  Display Shifting OFF                */
   WriteCmd_LCD(0x01);  /*  Clear Display                       */
  
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ClearScreen_LCD(void)
{
    WriteCmd_LCD(0x01);         /*  Clear Screen command    */
    __delay_ms(3);              /*  Delay for cursor to return home must be
                                 *  atleast 3ms menstioned in datasheet
                                 */
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Toggle_Enable_Pin_LCD(void)
{
    /*  toggling Enable PIN is must for data to be displayed on screen
        After every Command and data for more details see datasheet
    */
    ENABLE_LCD = 1;
    __delay_us(100);
    ENABLE_LCD = 0;
    __delay_us(100);
    
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteCmd_LCD(unsigned char Cmd)
{
    RS_LCD  = 0;        /*  For command RS must be low (0)      */
    LCD_BUS &= 0xFF00;  /*  Masking from 16bit register         */
    LCD_BUS |= Cmd;     /*  write Command to data bus of LCD    */

    Toggle_Enable_Pin_LCD();
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteData_LCD(unsigned char Data)
{
    RS_LCD  = 1;        /*  For data RS must be high (1)    */
    LCD_BUS &= 0xFF00;  /*  Masking from 16bit register     */
    LCD_BUS |= Data;    /*  write data to data bus of LCD   */
    
    Toggle_Enable_Pin_LCD();
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteString_LCD(const char *String)
{
    while(*String != NULL)
    {
        WriteData_LCD(*String++);   /*  Display data untill string ends */
    }
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

unsigned char MoveCursorToPosition(unsigned char Address)
{
    /*  valid addresses are for line one 0x80 and line two are 0xC0   */
    if ((Address >= 0x80 && Address <= 0xA8) || (Address >= 0xC0 && Address <= 0xE8))
    {
        WriteCmd_LCD(Address);
        return 1;
    }
    else
        return 0;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
void ShowSymbolicPercentageOnLCD(unsigned int Value, unsigned int Percent)
{
    float Temp = 0;
    unsigned char Temp1 = 0;
    unsigned char Character[] = "0123456789";
    
    Temp = ((((float)(Value))/((float)Percent)) * 100.0);
    if (Temp < 100)
        Temp = ceil(Temp);
    else
        Temp = floor(Temp);

    Temp1 = (unsigned char) Temp;

    WriteString_LCD("  0 ");
    DisplaySymbols(Temp1, 10);
    WriteData_LCD(' ');
    DisplayFiguresUptoThreeDigits(Temp1);
    WriteString_LCD(" %");
        
}

void ShowSymbol(unsigned char Value)
{
    char Temp = 0;
    for (Temp = 0; Temp < Value; Temp++)
        WriteData_LCD(0xFF);
    for (Temp = Value; Temp < 10; Temp++)
        WriteData_LCD('_');        
}

void ShowSymbolicDegreesOnLCD(unsigned int Value, unsigned int Per)
{
    float Temp = 0;
    unsigned char Temp1 = 0;
    
    Temp = ((((float)(Value))/((float)Per)));
    if (Temp < 180)
        Temp = ceil(Temp);
    else
        Temp = floor(Temp);
    Temp1 = (unsigned char) Temp;
    
    WriteString_LCD("  0 ");
    DisplaySymbols(Temp1, 18);
    WriteData_LCD(' ');
    DisplayFiguresUptoThreeDigits(Temp1);
    WriteData_LCD(223);
    
}

void DisplayFiguresUptoThreeDigits(unsigned char Value)
{
    unsigned char Character[] = "0123456789";
    
    if (Value < 10)
    {
        WriteData_LCD(' ');
        WriteData_LCD(' ');
        WriteData_LCD(Character[Value]);
    }
    else if (Value < 100)
    {
        WriteData_LCD(' ');
        WriteData_LCD(Character[Value/10]);
        WriteData_LCD(Character[Value%10]);
    }
    else
    {
        WriteData_LCD(Character[Value/100]);
        WriteData_LCD(Character[Value%100/10]);
        WriteData_LCD(Character[Value%100%10]);
    }
}

void DisplaySymbols(unsigned char Value, unsigned char PerDiv)
{
    unsigned char Index = 0;
    if (Value < (PerDiv*10))
    {
        for (Index = 1; Index <= 10; Index++)
        {
            if (Value < (PerDiv*Index))
            {
                ShowSymbol(Index - 1);
                break;
            }
        }
    }
    else
        ShowSymbol(10);
}
