
//Debouncing2311

#include <msp430.h>
int state = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= BIT0;//set P1.0 as output
    P2DIR |= BIT0;//set P2.0
    P1DIR &= ~BIT1;//set P1.1 as input
    P1REN |= BIT1;//enables the pull up resistor at P1.1
    P1OUT |= BIT1;//set pull up resistor
    P1IE |= BIT1;//enable interrupt
    P1IES |= BIT1;//toggle edge
    P1IFG &= ~BIT1;//clear flag


    TB0CCTL0 = CCIE;
    TB0CCR0 = 30000;

    __enable_interrupt();
    __bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

#pragma vector= PORT1_VECTOR
__interrupt void PORT_1(void)
{
    TB0CTL = TBSSEL__SMCLK + MC__UP + TBCLR + ID_2;//start the timer
    if(state == 0)
    {
        P1OUT ^= BIT0;
        P1IFG &= BIT1;
        P2OUT &= ~BIT0;
    }
    else
    {
        P1IFG &= ~BIT1;
        P2OUT |= BIT0;
    }
    P1IE &= ~BIT1;//stop P1.1 from inputting
}

// Timer B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{

    if(state == 0)
    {
        P1IES &= ~BIT1;
        state = 1;
    }
    else if(state == 1)
    {
        P1IFG &= ~BIT1;
        P1IES |= BIT1;
        state = 0;
    }

    P1IE |= BIT1;
    TB0CTL &= ~TBSSEL__SMCLK;
    TB0CTL |= TBCLR;

}
