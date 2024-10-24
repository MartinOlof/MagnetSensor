#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define ADC_VALUE 614 //3V
#define LED_IND_ON PORTB |= (1 << PB4)
#define LED_IND_OFF PORTB &= ~(1 << PB4)
#define Q_GATE_ON PORTB |= (1 << PB3)
#define Q_GATE_OFF PORTB &= ~(1 << PB3)
uint16_t adcConvert();
void setupADC();


int main(void)
{
	setupADC();
	DDRB |= (1 << PB3) | (1 << PB4); // Init portarna för output
	
    while(1)
    {
		
		uint16_t val = adcConvert();
		if(val >= ADC_VALUE){
			Q_GATE_ON;
			LED_IND_ON;
			Q_GATE_OFF;
			LED_IND_OFF;
		}
		else{
			Q_GATE_OFF;
			LED_IND_OFF;
		}
    }
}

void setupADC(){
	ADMUX |= (0 << MUX0) | (0 << MUX1) | (0 << MUX2) | (0 << MUX3); //ADC0 (PB5) 
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //EN ADC, Prescaler 128bit
	DIDR0 = (1 << ADC1D);
	ADMUX |= (0 << REFS0); // Spänningsref Vcc
	
	
}

uint16_t adcConvert(){
	
	int Ain, AinLow;
	ADCSRA |= (1 << ADSC);
	
	while(ADCSRA &(ADIF) == 0);
	
	AinLow = (int)ADCL;
	Ain = (int)ADCH*256;
	
	Ain += AinLow;
	
	return Ain;
	
}
