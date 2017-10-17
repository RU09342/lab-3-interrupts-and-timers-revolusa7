void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    P1DIR |= BIT6;                          // Set P1.0 to output direction
    P1DIR &=~(BIT3);                        // Set P1.1 to input direction
    P1REN|=BIT3;                            // enable pull- up resistor
    P1OUT|=BIT3;

    P1IE |= BIT3;             //enable the interrupt on port 1.1
    P1IES |= BIT3;            //set as falling edge
    P1IFG &=~(BIT3);          //clear interrupt flag

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);
}
    //Port 1 ISR
  #pragma vector=PORT1_VECTOR
  __interrupt void PORT_1(void)
{
    P1OUT ^= BIT3;
    P1IFG &= ~(BIT3);
}







