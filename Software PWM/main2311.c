
//SoftwarePWM2311

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
    P2DIR |= BIT0;
    P1DIR &= ~BIT1;//set P1.1 as input
    P1REN |= BIT1;//enables the pull up resistor at P1.1
    P1OUT |= BIT1;//set pull up resistor at P1.1
    P1IE |= BIT1;//enable interrupt
    P1IES |= BIT1;//toggle edge
    P1IFG &= ~BIT1;//clear flag

    TB0CCR0 = 1000;
    TB0CTL = TBSSEL_2 + MC_1 + TBCLR;
    TB1CCTL0 = CCIE;
    TB1CCR0 = 50000;


    __enable_interrupt();
    __bis_SR_register(GIE); // LPM0 with interrupts enabled

    for(;;)
    {
        if(TB0R <= PWM)
        {
            P1OUT ^= BIT0;
        }
        else if(TB0R > PWM)
        {
             P1OUT &= ~BIT0;
        }
    }
}

#pragma vector= PORT1_VECTOR
__interrupt void PORT_1(void)
{
    TB1CTL = TBSSEL_2 + MC_1 + TBCLR;
    if(state == 0)
    {
        P2OUT |= BIT0;
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
        P2OUT &= ~BIT0;
    }
    P1IFG &= ~BIT1;
    P1IE &= ~BIT1;
}

// Timer B0 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer_B (void)
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


    TB1CTL &= ~TBSSEL_2;
    TB1CTL |= TBCLR;

}
