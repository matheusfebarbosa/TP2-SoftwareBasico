/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VERÃO EM COMPUTAÇÃO                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOSÉ AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                    PRÁTICA #2 - E/S POR INTERRUPÇÃO                        *
 ******************************************************************************
 *                          DESCRIÇÃO DO EXEMPLO                              *
 *     O exemplo  executa um laço repetidas vezes até que  a  chave S2   seja *
 * pressionada,  gerando  uma  alteração  no  nível  lógico  no  pino  P1.3 e *
 * consequentemente uma interrupção. Quando a interrupção ocorre, a rotina de *
 * tratamento de interrupção é executada e o LED  verde  (P1.6)  inverte  seu *
 * nível lógico.                                                              *
 ******************************************************************************
 *                        ATIVIDADE PRÁTICA PROPOSTA                          *
 *     Altere o exemplo  para  que  a  chave  S2  (P1.3) simule  um sensor de *               
 * contagem de itens que passam  por  uma  esteira.  Inicialmente o LED verde *
 * (P1.6) deve estar ativado. Quando o número  de  itens  que  passaram  pela *
 * esteira atingir o valor 5, o LED verde (P1.6) deve ser desativado e o  LED *
 * vermelho (P1.0) deve ser ativado.                                          *
 ******************************************************************************/

#include "msp430g2553.h"  
  
void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;  // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;       // Define pinos 1.0 e 1.6 como saída (0100 0001)
  P1REN = 0x08;              // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08;              // Define pullup para o pino 1.3 (0000 1000)
  P1IE = 0x08;               // Habilita interrupção no pino 1.3 (00001000)
  P1IFG = 0x00;              // Zera flag de interrupção da porta 1 (00000000)
  _BIS_SR(CPUOFF + GIE);     // Entra em modo de baixo consumo e habilita 
                             // interrupções
  while(1);                                  
} 

#pragma vector=PORT1_VECTOR  // Rotina de tratamento de interrupção da porta 1
__interrupt void Port_1(void) {
   __delay_cycles(100000);   // Gera um atraso 
   P1OUT = P1OUT ^ 0x40;     // Inverte saida no pino 1.6 com ou-exclusivo
   P1IFG = 0x00;             // Zera flag de interrupção da porta 1 (00000000)
}