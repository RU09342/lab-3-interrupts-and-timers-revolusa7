void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    P1DIR |= BIT1;                          // Set P1.0 to output direction
    P5DIR &=~(BIT6);                        // Set P1.1 to input direction
    P5REN|=BIT6;                            // enable pull- up resistor
    P5OUT|=BIT6;

    P1IE |= BIT1;             //enable the interrupt on port 1.1
    P1IES |= BIT1;            //set as falling edge
    P1IFG &=~(BIT1);          //clear interrupt flag

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);
}
    //Port 1 ISR
  #pragma vector=PORT1_VECTOR
  __interrupt void PORT_1(void)
{
    P1OUT ^= BIT1;
    P1IFG &= ~(BIT1);
}







