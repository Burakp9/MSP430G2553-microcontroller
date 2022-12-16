#include <msp430.h> 


/**
 * main.c
 */
int main ( void){
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x40 ; //Set P1.6 to  output direction
    P1REN |= 0x08 ;
    P1OUT |= 0X08 ;
    while ( 1 ) {
            if ( ( P1IN & BIT3 ) ) { // If button is open (P1.3 HIGH)
                P1OUT = P1OUT | BIT6 ; // turn on LED
                _delay_cycles(16000000);
            } // or P1OUT |= BIT0 ;
            else {
                P1OUT = P1OUT & ~BIT6 ; // else turn it off .
                // or P1OUT &= ˜BIT0
            }
    }
}
