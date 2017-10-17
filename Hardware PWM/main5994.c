
//HardwarePWM5994

#include <msp430.h>
int state = 0;
int PWM = 500;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                                // to activate previously configured port settings

    P1DIR |= BIT0;//set P1.0 as output
    P1DIR |= BIT1;//set P1.1
    P5DIR &= ~BIT5;//set P5.5 as input
    P5REN |= BIT5;//enables the pull up resistor at P5.5
    P5OUT |= BIT5;//set pull up resistor at P5.5
    P5IE |= BIT5;//enable interrupt
    P5IES |= BIT5;//toggle edge
    P5IFG &= ~BIT5;//clear flag


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
    P1OUT |= BIT1;
    TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_2;//start the timer

    if(state == 0)
    {
        P5IFG &= BIT5;
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
        P5IFG &= ~BIT5;
    }
    P5IE &= ~BIT5;//stop P5.5 from inputting
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

    if(state == 0)
    {
        P5IES &= ~BIT5;
        state = 1;
    }
    else if(state == 1)
    {
        P5IFG &= ~BIT5;
        P5IES |= BIT5;
        P1OUT &= ~BIT1;
        state = 0;
    }

    P5IE |= BIT5;
    TA0CTL &= ~TASSEL_2;
    TA0CTL |= TACLR;

}
