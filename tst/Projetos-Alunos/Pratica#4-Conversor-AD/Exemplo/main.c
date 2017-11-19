/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VER�O EM COMPUTA��O                         *
 ******************************************************************************
 *                      MINICURSO SISTEMAS EMBARCADOS                         *
 *             PROF. JOS� AUGUSTO MIRANDA NACIF - JNACIF@UFV.BR               *
 *                PR�TICA #4 - CONVERSOR ANAL�GICO DIGITAL                    *
 ******************************************************************************
 *                          DESCRI��O DO EXEMPLO                              *
 *     O  exemplo  configura  o  conversor  anal�gico  digital para  realizar *
 * aquisi��es   do   term�metro   interno   periodicamente.    Inicialmente a *
 * temperatura ambiente  �  armazenada  e  periodicamente  comparada  com  os *
 * valores correntes. Se os valores forem iguais, o  LED  vermelho  (P1.0)  � *
 * ativado. Caso contr�rio, o LED verde (P1.6) � ativado.                     *
 ******************************************************************************
 *                        ATIVIDADE PR�TICA PROPOSTA                          *
 *     Altere o exemplo, de forma que:                                        * 
 * - O LED vermelho (P1.0) ativado indique uma varia��o positiva de tempratura*
 * - O LED verde (P1.6) ativado indique uma varia��o negativa  de temperatura *
 *     A  temperatura  calibrada  �  lida  e  armazenada  quando  o sistema � *
 * energizado. A vari�vel utilizada � a "tempCalibrated".                     *
 ******************************************************************************/

#include "msp430g2553.h"
//Variavel que recebe o valor do conversor a/d ao ser ligado
unsigned int tempCalibrated = 0;

//Rotina de configura��o do conversor a/d
void ConfigureAdc(void) {
  ADC10CTL1 = INCH_10 + ADC10DIV_3;        
  ADC10CTL0 = SREF_0 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
  __delay_cycles(1000);                   
  ADC10CTL0 |= ENC + ADC10SC;            
  __bis_SR_register(CPUOFF + GIE);  
  tempCalibrated = ADC10MEM;
}

unsigned int value = 0;

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);       
}

int main( void ) {
  WDTCTL = WDTPW + WDTHOLD;          // Desliga Watchdog timer
  P1DIR = 0x01 + 0x40;               // Define pinos 1.0 e 1.6 como sa�da (0100 0001)
  BCSCTL1 = CALBC1_1MHZ;             // Seleciona fonte de clock           
  DCOCTL = CALDCO_1MHZ;              // Configura fonte de clock
  BCSCTL2 &= ~(DIVS_3);              // Demais configura��es de clock         
  ConfigureAdc();    
  __enable_interrupt();              // Habilita interrup��es
  while(1) {    
    __delay_cycles(1000);            // Atraso de 1000 ciclos
    ADC10CTL0 |= ENC + ADC10SC;      // Valor do AD = sensor interno de temp.
    __bis_SR_register(CPUOFF + GIE); // Desliga CPU e habilita interrup��es
    value= ADC10MEM;                 // Obtem o valor do AD
    if (value == tempCalibrated) 
      P1OUT = 0x01;
    else    
      P1OUT = 0x40;  
  }
}
 


