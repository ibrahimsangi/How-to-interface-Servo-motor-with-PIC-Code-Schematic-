/* 
 * File:   LCD.h
 * Author: IBRAHIM LABS
 *
 * Created on June 23, 2013, 7:18 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*  *****************************************************************   */

    #define LCD_BUS     LATE                        /*  DATA BUS FOR LCD 8bits  */
    #define ENABLE_LCD  LATGbits.LATG12              /*  Enable pin of LCD       */
    #define RS_LCD      LATGbits.LATG13              /*  RS pin of LCD           */

    #define LCD_BUS_DIRECTION   TRISE               /*  DATA bus tristate register  */
    #define ENABLE_DIRECTION    TRISGbits.TRISG12    /*  Enable pin tristate register*/
    #define RS_DIRECTION        TRISGbits.TRISG13    /*  RS pin tristate register    */

    #define FirstLine   0x80
    #define SecondLine  0xC0
    #define ThirdLine   0x94
    #define FourthLine  0xD4


/*--------------------------------------------------------------------------------------------*/

    /*  Functions for LCD   */

    void Initilize_LCD(void);
    void ClearScreen_LCD(void);
    void Toggle_Enable_Pin_LCD(void);
    void WriteCmd_LCD(unsigned char Cmd);
    void WriteData_LCD(unsigned char Data);
    void WriteString_LCD(const char *String);
    unsigned char MoveCursorToPosition(unsigned char Address);
    void ShowSymbol(unsigned char Value);
    void DisplayFiguresUptoThreeDigits(unsigned char Value);
    void ShowSymbolicPercentageOnLCD(unsigned int Value, unsigned int Percent);
    void ShowSymbolicDegreesOnLCD(unsigned int Value, unsigned int Percent);
    void DisplaySymbols(unsigned char Value, unsigned char PerDiv);

/*  *****************************************************************   */

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

