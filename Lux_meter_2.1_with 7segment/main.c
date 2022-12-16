#include <msp430.h>

#define SegA BIT0;
#define SegB BIT1;
#define SegC BIT2;
#define SegD BIT3;
#define SegE BIT4;
#define SegF BIT5;
#define SegG BIT6;
#define SegDP BIT7;


#define D1 BIT0;
#define D2 BIT1;
#define D3 BIT2;

void timerConfig(void);
void clockConfig(void);
void pinConfig(void);
void ADC_config(void);
void disp(int number){

    if(number == 0){
        P1OUT |= SegA;
        P1OUT |= SegB;
        P1OUT |= SegC;
        P1OUT |= SegD;
        P1OUT |= SegE;
        P1OUT |= SegF;
        P1OUT &= ~SegG;
    }
    else if(number ==1){
        P1OUT &= ~SegA;
        P1OUT |= SegB;
        P1OUT |= SegC;
        P1OUT &= ~SegD;
        P1OUT &= ~SegE;
        P1OUT &= ~SegF;
        P1OUT &= ~SegG;

    }
    else if(number ==2){
         P1OUT |= SegA;
         P1OUT |= SegB;
         P1OUT &= ~SegC;
         P2OUT |= SegD;
         P1OUT |= SegE;
         P1OUT &= ~SegF;
         P1OUT |= SegG;

    }
    else if(number ==3){
        P1OUT |= SegA;
         P1OUT |= SegB;
         P1OUT |= SegC;
         P2OUT |= SegD;
         P1OUT &= ~SegE;
         P1OUT &= ~SegF;
         P1OUT |= SegG;
    }
    else if(number ==4){
        P1OUT &= ~SegA;
         P1OUT |= SegB;
         P1OUT |= SegC;
         P2OUT &= ~SegD;
         P1OUT &= ~SegE;
         P1OUT |= SegF;
         P1OUT |= SegG;
    }
    else if(number == 5){
        P1OUT |= SegA;
         P1OUT &= ~SegB;
         P1OUT |= SegC;
         P2OUT |= SegD;
         P1OUT &= ~SegE;
         P1OUT |= SegF;
         P1OUT |= SegG;
    }
    else if(number ==6){
        P1OUT |= SegA;
         P1OUT &= ~SegB;
         P1OUT |= SegC;
         P2OUT |= SegD;
         P1OUT |= SegE;
         P1OUT |= SegF;
         P1OUT |= SegG;

    }
    else if(number==7){
        P1OUT |= SegA;
         P1OUT |= SegB;
         P1OUT |= SegC;
         P2OUT &= ~SegD;
         P1OUT &= ~SegE;
         P1OUT &= ~SegF;
         P1OUT &= ~SegG;

    }
    else if(number ==8){
        P1OUT |= SegA;
         P1OUT |= SegB;
         P1OUT |= SegC;
         P2OUT |= SegD;
         P1OUT |= SegE;
         P1OUT |= SegF;
         P1OUT |= SegG;
    }
    else if(number ==9){
        P1OUT |= SegA;
         P1OUT |= SegB;
         P1OUT |= SegC;
          P2OUT |= SegD;
          P1OUT &= ~SegE;
          P1OUT |= SegF;
          P1OUT |= SegG;

    }
}

int temp;
int digit1;
int digit2;
int digit3;

int resistorVoltage;
int ldrVoltage;
int ldrResistance;
int ldrLux;

int main(void){
    WDTCTL = WDTPW | WDTHOLD;
    pinConfig();
    timerConfig();
    clockConfig();
    ADC_config();


    __bis_SR_register(GIE);
    _no_operation();

    while(1){


        digit1 = (temp)%10;
        digit2 = (temp/10)%10;
        digit3 = (temp/100)%10;

        P2OUT |= BIT0 +BIT1+BIT2;
        P1OUT &= ~SegDP;
        disp(digit1);
        P2OUT &= ~BIT0;
        __delay_cycles(5000);

        P1OUT |= SegDP;
        P2OUT |= BIT0+BIT1+BIT2;
        disp(digit2);
        P2OUT &= ~D2;
        __delay_cycles(5000);

        P2OUT |= BIT0+BIT1+BIT2;
        P1OUT &= ~SegDP;
        disp(digit3);
        P2OUT &= ~D3;
        __delay_cycles(5000);

    }

}

void pinConfig(void){
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
    P2DIR |= BIT0 + BIT1 + BIT2 + BIT7;

    P1DIR &= ~LM35;
}

void timerConfig(void){
    TA0CCR0 = 15625;
    TA0CTL = TASSEL_2 + MC_1 + ID_3 + TAIE;
}

void clockConfig(void){
    BCSCTL1 |= CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 |= DIVS_3;


}

void ADC_config(void){
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
    ADC10CTL1 = INCH_3;
    ADC10AE0 |= 0x08;
}



#pragma vector = TIMER0_A1_VECTOR

__interrupt void timer(void){
    TA0CTL &= ~TAIFG;
    ADC10CTL0 |= ENC + ADC10SC;

    int rawdata = ADC10MEM;
    resistorVoltage = rawdata/(1023*5);
    ldrVoltage = 5 - resistorVoltage;
    ldrResistance = ldrVoltage/(resistorVoltage*5000);
    ldrLux = 12518931 * (1/ldrResistance);
    temp = ldrLux;
}
