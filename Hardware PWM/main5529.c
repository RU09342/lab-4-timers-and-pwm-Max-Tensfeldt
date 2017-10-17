
//HardwarePWM5529

#include <msp430.h>
int state = 0;
int PWM = 500;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    P1DIR |= BIT0;//set P1.0 as output
    P4DIR |= BIT7;//set P9.7
    P1DIR &= ~BIT1;//set P1.1 as input
    P1REN |= BIT1;//enables the pull up resistor at P1.1
    P1OUT |= BIT1;//set pull up resistor at P1.1
    P1IE |= BIT1;//enable interrupt
    P1IES |= BIT1;//toggle edge
    P1IFG &= ~BIT1;//clear flag


    TA0CCTL0 = CCIE;
    TA0CCR0 = 30000;

    TA1CCTL1 = OUTMOD_7;
    TA1CCR0 = 1000-1;
    TA1CCR1 = 500;
    TA1CTL = TASSEL_2 | MC_1;

    __enable_interrupt();
    __bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled


}

#pragma vector= PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P4OUT |= BIT7;
    TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_2;//start the timer

    if(state == 0)
    {
        P1IFG &= BIT1;
        if(PWM < 1000)
        {
            PWM = PWM + 100;
        }
        else
        {
            PWM = 0;
        }
    }
    else
    {
        P1IFG &= ~BIT1;
    }
    P1IE &= ~BIT1;//stop P1.1 from inputting
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
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
        P4OUT &= ~BIT7;
        state = 0;
    }

    P1IE |= BIT1;
    TA0CTL &= ~TASSEL_2;
    TA0CTL |= TACLR;

}
