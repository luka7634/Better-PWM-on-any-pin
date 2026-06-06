#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "includes/pinDefines.h"

#define DELAY_ms 3

static inline void initTimer0(void)
{
    TCCR0B |= (1 << CS01) | (1 << CS00);

    TIMSK0 |= ((1 << OCIE0A) | (1 << OCIE1B));
    TIMSK0 |= (1 << TOIE0);
    sei();
}