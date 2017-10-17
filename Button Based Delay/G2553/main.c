#include <msp430.h>

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;   //stop watchdog timer
    P1DIR |= BIT0 + BIT6;   // pins 1.0 and 1.6 are set as outputs
    P1REN|= BIT3;   // pullup or pulldown resistor enabled
    P1OUT|= BIT3;   // pullup resistor selected
    P1IE |= BIT3;   // interrupt enable on port 1.3
    P1IES |= BIT3;  // set interrupt to falling edge
    P1IFG &= ~BIT3; // clear interrupt flag
    TA0CCTL0 = CCIE;    // capture/compare interrupt enabled
  //  TA0CCR0 = 10000;
    TA0CTL= TASSEL_1+MC_1;  // Set timerA0 to ACLK, up mode
    __bis_SR_register(LPM0_bits + GIE); // enter LPM0 mode and enable global interrupts

}

#pragma vector= TIMER0_A0_VECTOR // TimerA0 interrupt
__interrupt void Timer_A0 (void)
    {
        P1OUT ^= BIT0;  // toggle first LED
    }


#pragma vector=PORT1_VECTOR     // button interrupt

    __interrupt void PORT_1(void)

    {

        if (P1IES & BIT3) // if button is pressed...

        {

            TA1CTL = TASSEL_1 + MC_2;   // timerA1 is set to ACLK, continuous mode

            P1OUT ^= BIT6;              // toggle second LED

            P1IES &= ~BIT3;             // set interrupt to rising edge

        }

        else                // if button is depressed...

        {

            TA0CCR0 = TA1R; // set CCR0 to the value counted in TA1R

            P1OUT &= ~BIT6; // turn off the second LED

            P1IES |= BIT3; // set interrupt to falling edge

            TA1CTL = TACLR; // clear timerA1

        }



        P1IFG &= ~BIT3; // clear interrupt flag

}

