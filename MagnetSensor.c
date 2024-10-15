#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_VALUE 614 //3V
#define LED_INDICATOR PB4
#define Q_GATE PB3
DDRB =  0x18 // PB3 och PB4 som output 0b011000
void setupADC();
uint16_t adcConvert(void);


int main(void)
{
      setupADC();
      uint16_t adcConvert(void);            
    while(1){
            if(adcConvert(val) >= ADC_VALUE){
		DDRB |= (1 << PB3) | (1 << PB4); 
	    }
	    else{
		DDRB ~= (1 << PB3) | (1 << PB4);
	    }
    }
}

void setupADC(){
      ADMUX |= (1 << MUX0); //Vcc som ref och ADC1 PB2
      ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // ADC Enable, prescaler 128bit
      DIDR0 = (1 << ADC1D); //disable digital input
      

}

uint16_t adcConvert(void){
	ADCSRA |= (1 << ADSC);

	while ((ADCSRA & (1 << ADSC)) == 1){}
	uint8_t adcl = ADCL;
	uint8_t adch = ADCH;
	uint16_t val = ((adch << 8) | adcl) & 0x3FF;
	return val;
}
