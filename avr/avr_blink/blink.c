#include <avr/io.h>
#include <util/delay.h>

#define TIME 1000000

int main(void)
{
  DDRB = 0xff;
  PORTB = 0xff;
  DDRD = 0xff;
  PORTD = 0;

  for(;;)
  {
    _delay_us(TIME);
    PORTB ^= 0xff;
    PORTD ^= 0xff;
  }
}
