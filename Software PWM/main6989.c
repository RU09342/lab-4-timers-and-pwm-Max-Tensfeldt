
//SoftwarePWM6989

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
    P9DIR |= BIT7;
    P1DIR &= ~BIT1;//set P1.1 as input
    P1REN |= BIT1;//enables the pull up resistor at P1.1
    P1OUT |= BIT1;//set pull up resistor at P1.1
    P1IE |= BIT1;//enable interrupt
    P1IES |= BIT1;//toggle edge
    P1IFG &= ~BIT1;//clear flag

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

#pragma vector= PORT1_VECTOR
__interrupt void PORT_1(void)
{
    TA1CTL = TASSEL_2 + MC_1 + TACLR;
    if(state == 0)
    {
        P9OUT |= BIT7;
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
        P9OUT &= ~BIT7;
    }
    P1IFG &= ~BIT1;
    P1IE &= ~BIT1;
}

// Timer A0 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1IE |= BIT1;
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


    TA1CTL &= ~TASSEL_2;
    TA1CTL |= TACLR;

}
