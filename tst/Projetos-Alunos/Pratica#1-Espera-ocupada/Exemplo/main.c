/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VERÃO EM COMPUTAÇÃO                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOSÉ AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                       PRÁTICA #1 - E/S POR ESPERA OCUPADA                  *
 ******************************************************************************
 *                          DESCRIÇÃO DO EXEMPLO                              *
 *    O exemplo lê repetidas vezes o valor do pino  de entrada P1.3, que está *
 * ligado à chave S2. Se o valor lido é 0 (chave pressionada), o led vermelho *
 * é ativado. Se o valor lido é 1 (chave em posição normal), o led vermelho é *
 * desativado.                                                                *
 ******************************************************************************
 *                        ATIVIDADE PRÁTICA PROPOSTA                          *
 *    Altere o exemplo para que ao pressionar a chave S2 (P1.3), uma variável *
 * seja incrementada. Os LEDs devem indicar se o valor do contador é:         *
 * - Par: LED vermelho ativado (P1.0)                                         *
 * - Ímpar: LED verde ativado (P1.6)                                          *
 ******************************************************************************/

#include "msp430g2553.h"

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;  // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;       // Define pinos 1.0 e 1.6 como saída (0100 0001)
  P1REN = 0x08;              // Habilita pullup/pulldown do pino 1.3 (0000 1000)
  P1OUT = 0x08;              // Define pullup para o pino 1.3 (0000 1000)

  while(1) {
    
    if( (P1IN & 0x08) == 0 )  // Verifica se pino 1.3 está em nível lógico 0
      P1OUT =  P1OUT | 0x01;  // Coloca pino 1.0 em nível lógico 1
                              // Máscara = 0000 0001 (0x01)
    else
      P1OUT = P1OUT & 0xfe;   // Coloca pino 1.0 em nível lógico 0
                              // Máscara = 1111 1110 (0xfe)
  }
} 
