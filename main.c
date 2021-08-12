#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCDmodule.h"
void PrintByte(char *OutputString,
               char *PromptString,
               char ByteVar);

int main(void)
{
DDRB |= 0xFF;//defined all the portb pins as output
DDRD = 0x30;

LCD_Init();
LCD_Clear();

int sPIND;
char LCDtext[16];
unsigned char Abyte=007;

    while(1){

    PORTD|= _BV(PORTD4);
    sPIND=PIND;


        if((sPIND==0x02 || sPIND==0x12)  && Abyte>1){
            Abyte=Abyte-1;

            //PORTD|= _BV(PORTD4);
            PrintByte(LCDtext,"Atten ",Abyte);
            //PORTD &= ~_BV(PORTD4);

            PORTD|= _BV(PORTD5);
            LCD_MoveCursor(1,1);
            LCD_WriteString(LCDtext);
            PORTD &= ~_BV(PORTD5);

        }else if((sPIND==0x01 || sPIND==0x11) && Abyte<11){
            Abyte=Abyte+1;

            //PORTD|= _BV(PORTD4);
            PrintByte(LCDtext,"Atten ",Abyte);
            //PORTD &= ~_BV(PORTD4);

            PORTD|= _BV(PORTD5);
            LCD_MoveCursor(1,1);
            LCD_WriteString(LCDtext);
            PORTD &= ~_BV(PORTD5);
        }

        while(sPIND==0x02 || sPIND==0x01 || sPIND==0x12 || sPIND==0x11){
            sPIND=PIND;
        }


    _delay_us(500);

    PORTD &= ~_BV(PORTD4);
    };

    return 0;
}
