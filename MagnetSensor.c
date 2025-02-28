#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 1000000UL // Frekvens till 1MHz
#define ADC_VALUE 614 // ADC-värde för 3V
#define LED_IND_ON PORTB |= (1 << PB4) // LED port PÅ
#define LED_IND_OFF PORTB &= ~(1 << PB4) // LED port AV
#define Q_GATE_ON PORTB |= (1 << PB3) // MOSFET Gate PÅ
#define Q_GATE_OFF PORTB &= ~(1 << PB3) // MOSFET Gate AV
uint16_t adcConvert(); // Funktion för att konvertera adc
void setupADC(); // Funktion för att starta ADC
void turnOn(); // Funktion för att starta LED och relä
void turnOff(); // Funktion för att stänga av LED och relä

int main(void)
{
	setupADC(); // Starta ADC
	DDRB |= (1 << PB3) | (1 << PB4); // Init portarna för output
	
    while(1)
    {
		
		uint16_t val = adcConvert(); // Lägg värdet i variabeln "val"
		if(val >= ADC_VALUE){ //Om värdet är större eller mindre än angivna värdet, MOSFET gate och LED startar
			turnOn();
			_delay_ms(30000); // Delay på 30 sekunder
			turnOff();
		}
		else{
			turnOff();
		}
    }
}

void setupADC(){
	ADMUX |= (1 << MUX0) | (0 << MUX1) | (0 << MUX2) | (0 << MUX3); //ADC1 (PB2) 
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //EN ADC, Prescaler 128bit
	DIDR0 = (1 << ADC1D); // Disable digital input
	ADMUX |= (0 << REFS0); // Spänningsref Vcc
	
	
}

uint16_t adcConvert(){
	
	int Ain, AinLow;
	ADCSRA |= (1 << ADSC); // Start Conversion bit
	
	while(ADCSRA &(ADIF) == 0); // ADIF == 1 när konvertering är färdig, startar konvertering när ADIF == 0
	
	AinLow = (int)ADCL; // Low Values
	Ain = (int)ADCH*256; // High Values
	
	Ain += AinLow;
	
	return Ain; // return digitala värdet
	
}

void turnOff(){
	Q_GATE_OFF;
	LED_IND_OFF;
}

void turnOn(){
	Q_GATE_ON;
	LED_IND_ON;
}
