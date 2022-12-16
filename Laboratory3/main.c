#include <msp430.h> 

void turnON(int);
void turnOFF(int);
void configpin(void);
void configWDT(void);
void updateLeds(void);
volatile int count=0;

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

void updateLeds(void){
int reminder= count % 8;
if(reminder == 0) turnOFF(BIT0 + BIT1 + BIT2); //000
else if(reminder == 1){ //001
turnOFF(BIT1 + BIT2);
turnON(BIT0);
}
else if(reminder == 2){ //010
turnOFF(BIT0 + BIT2);
turnON(BIT1);
}
else if(reminder == 3){ //011
turnOFF(BIT2);
turnON(BIT1 + BIT0);
}
else if(reminder == 4){ //100
turnOFF(BIT0 + BIT1);
turnON(BIT2);
}
else if(reminder == 5){ //101
turnOFF(BIT1);
turnON(BIT2 + BIT0);
}
else if(reminder == 6){ //110
turnOFF(BIT0);
turnON(BIT2 + BIT1);
}
else if(reminder == 7){ //111
turnON(BIT0 + BIT1 + BIT2);
}
}
void configWDT(void)
{
WDTCTL = WDTPW | WDTHOLD;
}

void turnON(int a){
P1OUT |= a; // set 1 .
}
void turnOFF(int a){
P1OUT &= ~a; // Set 0.
}

#pragma vector = PORT1_VECTOR
__interrupt void port1_ISR(void){
 count++;
 updateLeds();
 __delay_cycles(50000);
 P1IFG &= ~BIT5; // Interrupt is cleaned.
}
