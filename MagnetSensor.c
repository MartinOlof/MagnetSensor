#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

#define ADC_VALUE 614 //3V
#define LED_INDICATOR_ON PORTB |= (1 << PB4)
#defome LED_INDICATOR_OFF PORTB &= ~(1 << PB4)
#define Q_GATE_ON PORTB |= (1 << PB3)
#define Q_GATE_OFF PORTB &= ~(1 << PB3)
//DDRB =  0x018 // PB3 och PB4 som output 0b011000
void setupADC();
uint16_t adcConvert(void);
sei(); // enable global interrupt
void WDT_OFF(void); // Turn off WDT
void idleSleep();

/*
TODO:
Check system values with LED's, do we get an input from increasing/decreasing voltage, is the limit 3V?
Implement sleep/interrupt system
*/




int main(void)
{
      setupADC();
      uint16_t adcConvert(void);            
    while(1){
            if(adcConvert(val) >= ADC_VALUE){
		EMPTY_INTERRUPT(ADC_vect);
		LED_INDICATOR_ON;
		Q_GATE_ON;
	    }
	    else{
		LED_INDICATOR_OFF; 
		Q_GATE_OFF;
		void idleSleep();
	    }
    }
}

void setupADC(){
      ADMUX |= (1 << MUX0); //Vcc som ref och ADC1 PB2
      ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // ADC Enable, prescaler 128bit
      DIDR0 = (1 << ADC1D); //disable digital input, behövs den ens?
      ADCSRA = (1 << ADIE); // Enable adc interrupt

}

uint16_t adcConvert(void){
	ADCSRA |= (1 << ADSC);

	while ((ADCSRA & (1 << ADSC)) == 1){}
	uint8_t adcl = ADCL;
	uint8_t adch = ADCH;
	uint16_t val = ((adch << 8) | adcl) & 0x3FF;
	return val;
}

/*
ISR(ADC_vect){
	adc_flag = 1;
}
*/



void WDT_OFF(void){
	_WDR();

	MCUSR = 0x00;
	WDTCR |= (1 << WDCE) | (1 << WDE);
	WDTCR = 0x00;
}

void idleSleep(){

	MCUCR |= (1 << SE) | (0 << SM1) | (0 << SM0); //Sleep mode EN, IDLE mode set
}
