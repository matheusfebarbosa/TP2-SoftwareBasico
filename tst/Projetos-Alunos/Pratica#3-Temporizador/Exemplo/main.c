/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VER�O EM COMPUTA��O                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOS� AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                        PR�TICA #3 - TEMPORIZADOR                           *
 ******************************************************************************
 *                          DESCRI��O DO EXEMPLO                              *
 *     O exemplo  configura  o Timer A para gerar uma interrup��o peri�dica a *
 * cada 1 segundo. Quando a rotina de tratamento de interrup��o �  executada, *
 * o valor do LED vermelho (P1.0) � invertido.                                *
 ******************************************************************************
 *                        ATIVIDADE PR�TICA PROPOSTA                          *
 *     Altere o exemplo, utilizando o temporizador para simular um  semaf�ro, * 
 * no qual:                                                                   *
 * - O LED vermelho (P1.0) permane�a ativado por 10 segundos                  *
 * - O LED verde (P1.6) permane�a ativado por 20 segundos                     *
 ******************************************************************************/
#include "msp430g2553.h"  

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;        // Define pinos 1.0 e 1.6 como sa�da (0100 0001)
  P1REN = 0x08;               // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08;               // Define pullup para o pino 1.3 (0000 1000)

  CCTL0 = CCIE;               // Habilita interrup��o de compara��o do timer A           
  TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)      
  CCR0 =  62500;              // Modo up/down: chega no valor e depois volta
                              // para zero, portanto cada interrup��o acontece
                              // 2 * 62500 * 8 us = 1 segundo    
  _BIS_SR(CPUOFF + GIE);                    
  while(1);             
} 
// Timer A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {   
   P1OUT = P1OUT ^ 0x01;      // Inverte saida no pino 1.0 com ou-exclusivo                 
} 
