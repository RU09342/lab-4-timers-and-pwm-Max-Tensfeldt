
//SoftwarePWM5994

#include <msp430.h>
int state = 0;
int PWM = 500;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                                // to activate previously configured port settings

    P1OUT &= ~BIT0;
    P1DIR |= BIT0;//set P1.0
    P1DIR |= BIT1;
    P5DIR &= ~BIT5;//set P1.1 as input
    P5REN |= BIT5;//enables the pull up resistor at P1.1
    P5OUT |= BIT5;//set pull up resistor at P1.1
    P5IE |= BIT5;//enable interrupt
    P5IES |= BIT5;//toggle edge
    P5IFG &= ~BIT5;//clear flag

    TA0CCR0 = 1000;
    TA0CTL = TASSEL_2 + MC_1 + TACLR;
    TA1CCTL0 = CCIE;
    TA1CCR0 = 50000;


    __enable_interrupt();
    __bis_SR_register(GIE); // LPM0 with interrupts enabled

    for(;;)
    {
        if(TA0R <= PWM)
        {
            P1OUT ^= BIT0;
        }
        else if(TA0R > PWM)
        {
             P1OUT &= ~BIT0;
        }
    }
}

#pragma vector= PORT5_VECTOR
__interrupt void PORT_5(void)
{
    TA1CTL = TASSEL_2 + MC_1 + TACLR;
    if(state == 0)
    {
        P1OUT |= BIT1;
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
        P1OUT &= ~BIT1;
    }
    P5IFG &= ~BIT5;
    P5IE &= ~BIT5;
}

// Timer A0 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    P5IE |= BIT5;
    if(state == 0)
    {
        P5IES &= ~BIT5;
        state = 1;
    }
    else if(state == 1)
    {
        P5IFG &= ~BIT5;
        P5IES |= BIT5;
        state = 0;
    }


    TA1CTL &= ~TASSEL_2;
    TA1CTL |= TACLR;

}
