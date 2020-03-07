/* 
 * File:   main.c
 * Author: IBRAHIM LABS
 *
 * Website: http://ibrahimlabs.blogspot.com/
 *
 * Created on August 18, 2013, 5:10 AM
 */

#define CRYSTAL_FREQUENCY   8000000         // Crystal of 16MHz
#define FCY CRYSTAL_FREQUENCY/2UL            // Instruction Cycle Clock must be defined

#include <p33FJ64GS610.h>
#include <libpic30.h>
#include "LCD.h"
#include "PWM.h"

//==================================================================================================

/*  ****    FUSES SETTING   ****    */

_FGS(GSS_OFF & GWRP_OFF);
_FOSCSEL(IESO_OFF & FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);
/*
 *
 */
int main(void)
{
    unsigned int DutyCycle = 2483;
/*
    InitializeTimer2For_PWM();
    Initilize_LCD();
    Initialize_PWM1();
    ClearScreen_LCD();
    WriteString_LCD("    Welcome To");
    MoveCursorToPosition(SecondLine);
    WriteString_LCD("    IbrahimLabs");
    MoveCursorToPosition(ThirdLine);
    WriteString_LCD("This is Servo Motor");
    MoveCursorToPosition(FourthLine);
    WriteString_LCD("    Tutorial.");
    __delay_ms(4000);
    ClearScreen_LCD();

    
    CNPU2bits.CN21PUE = 1;
    CNPU2bits.CN20PUE = 1;

    UP_DIRECTION = Input;
    DOWN_DIRECTION = Input;

    MoveCursorToPosition(FirstLine);
    WriteString_LCD("     IbrahimLabs");
    MoveCursorToPosition(SecondLine);
    WriteString_LCD("Servo Motor Angle");
    SetDutyCycle_PWM1(DutyCycle);
    
    while(1)
    {
        if (!UP)
        {
            __delay_us(100);
            while (!UP);
            if (DutyCycle < 12383)          // 24 of 49999
            {
                DutyCycle += 55;            // one degree addition
                SetDutyCycle_PWM1(DutyCycle);
            }
        }
        else if (!DOWN)
        {
            __delay_us(100);
            while (!DOWN);
            if (DutyCycle > 2483)            // 5 % of 49999
            {
                DutyCycle -= 55;            // one degree subtraction
                SetDutyCycle_PWM1(DutyCycle);
            }
        }
        MoveCursorToPosition(ThirdLine);
        ShowSymbolicDegreesOnLCD((DutyCycle - 2483), 55);
        MoveCursorToPosition(FourthLine);
        ShowSymbolicPercentageOnLCD(DutyCycle, 49667);
    }*/

    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;

    LATBbits.LATB0 = 1;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 1;

    while(1)
    {
        LATBbits.LATB0 = ~LATBbits.LATB0;
        LATBbits.LATB1 = ~LATBbits.LATB1;
        LATBbits.LATB2 = ~LATBbits.LATB2;
        LATBbits.LATB3 = ~LATBbits.LATB3;
        LATBbits.LATB4 = ~LATBbits.LATB4;

        __delay_ms(1000);
    }
}

