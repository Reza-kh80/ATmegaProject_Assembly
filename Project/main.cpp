#include <avr/io.h>
#include <util/delay.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
#define F_CPU 3000000UL

unsigned int Read(unsigned char adc_input) {
	ADMUX=adc_input | ADC_VREF_TYPE;
	_delay_ms(10);
	ADCSRA|=(1<<ADSC);
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCW;
}

float RVoltage(unsigned char ADC_rea) {
	int i = Read(ADC_rea);
	return float((i * 5) / 1023);
}


int main(void) {
	DDRC = 0b111000000;
	while (1) {
		PORTC = 0b00000000;
		int ST = 10;
		float sw_volt_value = RVoltage(1);
		if (sw_volt_value >= 2.5) {
			PORTC = 0b00100000;
			float timer = RVoltage(0);
			if (timer >= 0 && timer < 1.5) {
				_delay_ms(ST * 1000 + 3000);
			}
			else if (timer > 1.5 && timer <= 2.5) {
				_delay_ms(ST * 1000 + 6000);
			}
			else if (timer > 2.5 && timer <= 3.5) {
				_delay_ms(ST * 1000 + 9000);
			}
			else if (timer > 3.5 && timer <= 4.5) {
				_delay_ms(ST * 1000 + 12000);
			}
			else{
				_delay_ms(ST * 1000 + 15000);
			}
			PORTC = 0b00000000;
			_delay_ms(3000);
		}
		else {
			PORTC = 0b10000000;
			float timer = RVoltage(0);
			if (timer >= 0 && timer < 1.5) {
				_delay_ms(ST * 1000 + 3000);
			}
			else if (timer > 1.5 && timer <= 2.5) {
				_delay_ms(ST * 1000 + 6000);
			}
			else if (timer > 2.5 && timer <= 3.5) {
				_delay_ms(ST * 1000 + 9000);
			}
			else if (timer > 3.5 && timer <= 4.5) {
				_delay_ms(ST * 1000 + 12000);
			}
			else{
				_delay_ms(ST * 1000 + 15000);
			}
			PORTC = 0b00000000;
			_delay_ms(3000);
		}
	}
}