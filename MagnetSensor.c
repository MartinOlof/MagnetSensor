#define LED_INDICATOR PB4
#define Q_GATE PB3
DDRB =  0x18 // PB3 och PB4 som output 0b011000
void setupADC();
uint16_t adcConvert(void);

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
		PORTB |= (1 << PB3) | (1 << PB4); 
	    }
	    else{
		PORTB ~= (1 << PB3) | (1 << PB4);
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
