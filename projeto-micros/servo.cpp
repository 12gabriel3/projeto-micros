#include "servo.h"
#include <inttypes.h>
#include <avr/io.h>


Servo::Servo(){
	DDRB |= (1<<DDB2);  // Configura o pino do servo como saida
  
  /*
    Seta o timer1 com as seguintes configuracoes:
    modo 15: fast-PWM de 16 bits
    Unidade de Output compare canal A ativa
    Prescaler de 8
  */
  
  TCCR1A |= 1<<WGM11 | 1<<WGM10 | 1<<COM1B1;
  TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
  
  //Periodo de 20ms
  OCR1A = 39999;
}

void Servo::setAngle(uint8_t angle){
	// Faz uma regrinha de tres
	// O angulo 0 corresponde ao valor 1000 do registrador - largura de pulso de 0.5ms
	// e o angulo 180 corresponde ao valor 5000 - largura de 2.5 ms
	uint16_t registrador = (uint16_t)(angle*(400.0)/18.0) + 1000;
	OCR1B = registrador;
}