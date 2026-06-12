#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "includes/pinDefines.h"

#define DELAY_ms 3

volatile uint8_t brightnessA;
volatile uint8_t brightnessB;

static inline void initTimer0(void)
{
    TCCR0B |= (1 << CS01) | (1 << CS00);

    TIMSK0 |= ((1 << OCIE0A) | (1 << OCIE0B));
    TIMSK0 |= (1 << TOIE0);
    sei();
}

ISR(TIMER0_OVF_vect)
{
    LED_PORT = 0xff;
    OCR0A = brightnessA;
    OCR0B = brightnessB;
}
ISR(TIMER0_COMPA_vect)
{
    LED_PORT &= 0b11110000;
}
ISR(TIMER0_COMPB_vect)
{
    LED_PORT &= 0b00001111;
}

int main(void)
{
    uint8_t i;
    LED_DDR = 0xff;
    initTimer0();

    while (1)
    {
        for (i = 0; i < 255; i++)
        {
            _delay_ms(DELAY_ms);
            brightnessA = i;
            brightnessB = 255 - i;
        }

        for (i = 254; i > 0; i--)
        {
            _delay_ms(DELAY_ms);
            brightnessA = i;
            brightnessB = 255 - i;
        }
    }
    return 0;
}