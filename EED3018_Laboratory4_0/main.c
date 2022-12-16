#include <msp430.h> 

void turnON(int);
void turnOFF(int);
void configpin(void);
void configWDT(void);
int main(void)
{
    configWDT();
    configpin();
    turnOFF(BIT0+BIT1+BIT2);
}
    void configpin(void){
        P1DIR |= BIT0 + BIT1 + BIT2; //set  P1.0, P1.1, P1.2 output
        P1DIR &= ~BIT5; // set P1.5  input
        P1OUT |= BIT5; //Pull up mode selected.
        P1IFG &= ~BIT5; // Flag clear
        P1IE |= BIT5; // Interrupt is enabled
        P1IES |= BIT5; //  set with a high/low edge.
    __bis_SR_register(LPM4_bits + GIE);// enable LPM4 interrupt
    _no_operation();
}
    void configWDT(void) {
    WDTCTL = WDTPW | WDTHOLD;
    }
    void turnON(int a){
    P1OUT |= a; // set 1 .
    }
    void turnOFF(int a){
    P1OUT &= ~a; // Set 0.
    }
