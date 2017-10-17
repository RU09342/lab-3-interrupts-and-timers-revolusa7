#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	
	P1DIR |= BIT1;
	P4DIR |= BIT7;

	// Timer 0 configuration
	    TA0CTL = MC_0; // stop the timer
	    TA0CTL = TASSEL_2 + ID_3 + TAIE; // TIMER CLOCK = SMCLK, 1MHz/8 = 12

	    TA0CCR0 = 10000; // Count in CCR0 register
	    TA0CCR1 = 300000; // Count in CCR1 register
	    TA0CCR2 = 3000000; // Count in CCR2 register

	    TA0CCTL0 |= CCIE; // Enable CCR0 interrupt
	    TA0CCTL1 |= CCIE; //enable CCR0 interrupt
	    TA0CCTL2 |= CCIE + OUTMOD_7; // enable CCR2 interrupt

	    TA0CTL |= MC_2; // Start the timer continuous mode

	    _BIS_SR(LPM0_bits + GIE); //sleep in LPM0 with interrupts enabled
	    __bis_SR_register(LPM0_bits + GIE);  // Enter LPM0 w/interrupt




}

        //TIMER A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT1;      //Toggle P1.0
    TA0CCR0 += 4000;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TA0IV)
    {
    case 2:         //CCR1
    {
        P1OUT^= BIT1;     //Toggle P1.0
        TA0CCR1 += 500000;     // add offset to CCR1
    }
        break;
    case 4:
    {
        P4OUT^= BIT7;
        TA0CCR2+=5000;

    }

        break;
    case 10:

        break;
    }
}


