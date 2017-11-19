/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VER�O EM COMPUTA��O                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOS� AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                    PR�TICA #2 - E/S POR INTERRUP��O                        *
 ******************************************************************************
 *                          DESCRI��O DO EXEMPLO                              *
 *     O exemplo  executa um la�o repetidas vezes at� que  a  chave S2   seja *
 * pressionada,  gerando  uma  altera��o  no  n�vel  l�gico  no  pino  P1.3 e *
 * consequentemente uma interrup��o. Quando a interrup��o ocorre, a rotina de *
 * tratamento de interrup��o � executada e o LED  verde  (P1.6)  inverte  seu *
 * n�vel l�gico.                                                              *
 ******************************************************************************
 *                        ATIVIDADE PR�TICA PROPOSTA                          *
 *     Altere o exemplo  para  que  a  chave  S2  (P1.3) simule  um sensor de *               
 * contagem de itens que passam  por  uma  esteira.  Inicialmente o LED verde *
 * (P1.6) deve estar ativado. Quando o n�mero  de  itens  que  passaram  pela *
 * esteira atingir o valor 5, o LED verde (P1.6) deve ser desativado e o  LED *
 * vermelho (P1.0) deve ser ativado.                                          *
 ******************************************************************************/

#include "msp430g2553.h"  
  
void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;  // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;       // Define pinos 1.0 e 1.6 como sa�da (0100 0001)
  P1REN = 0x08;              // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08;              // Define pullup para o pino 1.3 (0000 1000)
  P1IE = 0x08;               // Habilita interrup��o no pino 1.3 (00001000)
  P1IFG = 0x00;              // Zera flag de interrup��o da porta 1 (00000000)
  _BIS_SR(CPUOFF + GIE);     // Entra em modo de baixo consumo e habilita 
                             // interrup��es
  while(1);                                  
} 

#pragma vector=PORT1_VECTOR  // Rotina de tratamento de interrup��o da porta 1
__interrupt void Port_1(void) {
   __delay_cycles(100000);   // Gera um atraso 
   P1OUT = P1OUT ^ 0x40;     // Inverte saida no pino 1.6 com ou-exclusivo
   P1IFG = 0x00;             // Zera flag de interrup��o da porta 1 (00000000)
}