
#include<msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x41; // Set P1.6 and P1.0 to output direction
    P1REN |= 0x08; //resistor enable of P1.3
    P1OUT |= 0X08; //initial condition of output
    while(1) {
        if ((P1IN & BIT3)) {
            P1OUT = P1OUT & ~0X41; // turn off leds
            P1OUT = P1OUT | 0X40; // turn on LED2
        }
        else {
            P1OUT = P1OUT & ~0X41; //turn of leds
            P1OUT = P1OUT^BIT0; //turn on led1
        }
    }
}

