#include "msp430g2553.h"  

volatile unsigned int temporizador = 0;

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;        // Define os pinos 1.0 e 1.6 como saída (0100 0001)
  P1REN = 0x08;              // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08 + 0x01;       // Define pullup para o pino 1.3 e liga o led 1.0 (0000 1001)

  CCTL0 = CCIE;               // Habilita interrupção de comparação do timer A           
  TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)      
  CCR0 =  62500;              // Modo up/down: chega no valor e depois volta
                              // para zero, portanto cada interrupção acontece
                              // 2 * 62500 * 8 us = 1 segundo  

  P1IE = 0x08;               // Habilita interrupção no pino 1.3 (00001000)
  P1IFG = 0x00;              // Zera flag de interrupção da porta 1 (00000000)

  temporizador = 0;
  _BIS_SR(CPUOFF + GIE);                    
  while(1);             
} 

// Timer A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {
  temporizador += 1;
  
  if((P1OUT & 0x01 && !(P1OUT & 0x40)) && temporizador >= 2){
    P1OUT = P1OUT ^ (0x01 + 0x40);
    temporizador = 0;
  }else if(P1OUT & 0x40 && !(P1OUT & 0x01) && temporizador >= 8){
    P1OUT = P1OUT | (0x01 + 0x40);
    temporizador = 0;
  }else if((P1OUT & 0x01) && (P1OUT & 0x40) && temporizador >= 1){
    P1OUT = P1OUT ^ (0x40);
    temporizador = 0;
  }
}

#pragma vector=PORT1_VECTOR  // Rotina de tratamento de interrupção da porta 1
__interrupt void Port_1(void) {
    if(P1OUT & 0x40 && !(P1OUT & 0x01) && temporizador <=5){
      temporizador = 5;         
      P1IFG = 0x00;             // Zera flag de interrupção da porta 1 (00000000)
    }
}