#include "msp430g2553.h"  

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer
  P1DIR = 0x01;        // Define pino 1.0 como saída (0001)

  CCTL0 = CCIE;               // Habilita interrupção de comparação do timer A           
  TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)      
  CCR0 =  62500;              // Modo up/down: chega no valor e depois volta
                              // para zero, portanto cada interrupção acontece
                              // 2 * 62500 * 8 us = 1 segundo    
  _BIS_SR(CPUOFF + GIE);                    
  while(1);             
} 
// Timer A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) { 
  if(P1OUT & 0x01)
    TACTL = TASSEL_2+MC_3+ID_3; 
  else
    TACTL = TASSEL_2+MC_3+ID_2;

  P1OUT = P1OUT ^ 0x01;      // Inverte saida no pino 1.0 com ou-exclusivo                 
} 
