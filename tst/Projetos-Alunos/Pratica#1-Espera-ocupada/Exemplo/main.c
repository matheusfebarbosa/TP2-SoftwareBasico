/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VER�O EM COMPUTA��O                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOS� AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                       PR�TICA #1 - E/S POR ESPERA OCUPADA                  *
 ******************************************************************************
 *                          DESCRI��O DO EXEMPLO                              *
 *    O exemplo l� repetidas vezes o valor do pino  de entrada P1.3, que est� *
 * ligado � chave S2. Se o valor lido � 0 (chave pressionada), o led vermelho *
 * � ativado. Se o valor lido � 1 (chave em posi��o normal), o led vermelho � *
 * desativado.                                                                *
 ******************************************************************************
 *                        ATIVIDADE PR�TICA PROPOSTA                          *
 *    Altere o exemplo para que ao pressionar a chave S2 (P1.3), uma vari�vel *
 * seja incrementada. Os LEDs devem indicar se o valor do contador �:         *
 * - Par: LED vermelho ativado (P1.0)                                         *
 * - �mpar: LED verde ativado (P1.6)                                          *
 ******************************************************************************/

#include "msp430g2553.h"

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;  // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;       // Define pinos 1.0 e 1.6 como sa�da (0100 0001)
  P1REN = 0x08;              // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08;              // Define pullup para o pino 1.3 (0000 1000)

  while(1) {
    
    if( (P1IN & 0x08) == 0 )  // Verifica se pino 1.3 est� em n�vel l�gico 0
      P1OUT =  P1OUT | 0x01;  // Coloca pino 1.0 em n�vel l�gico 1
                              // M�scara = 0000 0001 (0x01)
    else
      P1OUT = P1OUT & 0xfe;   // Coloca pino 1.0 em n�vel l�gico 0
                              // M�scara = 1111 1110 (0xfe)
  }
} 
