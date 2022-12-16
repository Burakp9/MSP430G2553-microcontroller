#include <msp430.h>

int main ( void){
    WDTCTL = WDTPW | WDTHOLD; // S top wa tchdog t ime r
    P1DIR |= 0x40 ; // Se t P1 . 6 t o o u t p u t d i r e c t i o n
    P1REN |= 0x08 ;
    P1OUT |= 0X08 ;
    while ( 1 ) {
            if ( ( P1IN & BIT3 ) ) { // I f b u t t o n i s open (P1 . 3 HIGH)
                P1OUT = P1OUT & ~BIT6 ;
                _delay_cycles(1)*16000000;
            } // or P1OUT |= BIT0 ;
            else {
                P1OUT = P1OUT |  BIT6 ;
                // or P1OUT &= ˜BIT0
            }
    }
}
