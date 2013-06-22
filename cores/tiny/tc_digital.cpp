#include <Arduino.h>

#include <avr/pgmspace.h>

// fix or rmv: #include "wiring_private.h"
// fix or rmv: #include "pins_arduino.h"
// fix or rmv: #include "tc_pins.h"
// fix or rmv: #include "core_timers.h"
// fix or rmv: #include "PwmTimer.h"


#if TC_HAVE_ONE_DIO

typedef union
{
/*
  struct
  {
    unsigned bit:4;
    unsigned pwmid:4;
  };
*/
  uint8_t raw;
}
dio_pin_map_entry_4_t;

#define dio_pin_map_entry_read_4  pgm_read_byte


static dio_pin_map_entry_4_t const pin_map_4[] PROGMEM =
{
  { ( ~ TC_DIO_CHANNEL( TC_PIN_0 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_0 ) & 0x0F ) },
#if defined( TC_PIN_1 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_1 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_1 ) & 0x0F ) },
#endif
#if defined( TC_PIN_2 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_2 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_2 ) & 0x0F ) },
#endif
#if defined( TC_PIN_3 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_3 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_3 ) & 0x0F ) },
#endif
#if defined( TC_PIN_4 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_4 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_4 ) & 0x0F ) },
#endif
#if defined( TC_PIN_5 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_5 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_5 ) & 0x0F ) },
#endif
#if defined( TC_PIN_6 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_6 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_6 ) & 0x0F ) },
#endif
#if defined( TC_PIN_7 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_7 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_7 ) & 0x0F ) },
#endif
#if defined( TC_PIN_8 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_8 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_8 ) & 0x0F ) },
#endif
#if defined( TC_PIN_9 )
  { ( ~ TC_DIO_CHANNEL( TC_PIN_9 ) & 0xF0 ) | ( TC_DIO_BIT( TC_PIN_9 ) & 0x0F ) },
#endif
};


/******************************************************************************
rmv: tc_bit_to_mask generates five machine instructions.  The following also 
generates five machine instructions...
  mask = pgm_read_byte( & bit_to_mask[ bit ] );

Add in the extra eight for the array and tc_bit_to_mask is cheaper.

static uint8_t bit_to_mask[] PROGMEM =
{
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000
};
******************************************************************************/


__attribute__((always_inline, const)) 
uint8_t const tc_bit_to_mask( uint8_t const bit )
{
  uint8_t i;

  asm
  (
    "ldi   %[i], 1"                           "\n\t"
    "rjmp  L%=bottom"                         "\n\t"
  "L%=loop: "                                 "\n\t"
    "add   %[i], %[i]"                        "\n\t"
  "L%=bottom: "                               "\n\t"
    "dec   %[bit]"                            "\n\t"
    "brpl  L%=loop"                           "\n\t"
    : 
      [i] "=&r" ( i )
    : 
      [bit] "r" ( bit )
    :
  );
  return( i );
}


void pinModeF( uint8_t const pin, uint8_t const mode )
{
  dio_pin_map_entry_4_t map;
  uint8_t mask;

  if ( pin < TC_NUMBER_OF(pin_map_4) )
  {
    map.raw = dio_pin_map_entry_read_4( & pin_map_4[ pin ] );

/**
rmv: This is -very- expensive.  pin_map_2 plus the line of code above is cheaper.
    switch ( pin )
    {
    case 6: pin = 5; break;
    case 7: pin = 2; break;
    case 8: pin = 4; break;
    case 9: pin = 3; break;
    }
**/

/**
rmv: tc_bit_to_mask is cheaper by a few machine instructions.
    mask = (uint8_t)((uint8_t)(1) << pin);
**/

/**
rmv: See note above for bit_to_mask.
    mask = pgm_read_byte( & bit_to_mask[ pin ] );
**/

/**
rmv: To ensure bit is the bottom nibble we will not rely on the compiler for placement.
    mask = tc_bit_to_mask( map.bit );
**/

    mask = tc_bit_to_mask( map.raw & 0x0F );

    TC_ATOMIC_OPTION
    {
      if ( mode == OUTPUT )
      {
        TC_THE_ONE_DDR |= mask;
      }
      else if ( mode == INPUT_PULLUP ) 
      { 
        TC_THE_ONE_DDR &= ~ mask;
        TC_THE_ONE_PORT |= mask;
      }
      else 
      { 
        TC_THE_ONE_DDR &= ~ mask;
        TC_THE_ONE_PORT &= ~ mask;
      }
    }
  }
}


void digitalWriteF( uint8_t pin, uint8_t val )
{
  dio_pin_map_entry_4_t map;
  uint8_t mask;

  if ( pin < TC_NUMBER_OF(pin_map_4) )
  {
    map.raw = dio_pin_map_entry_read_4( & pin_map_4[ pin ] );

    mask = tc_bit_to_mask( map.raw & 0x0F );

    TC_ATOMIC_OPTION
    {
      #if DIGITAL_TURNS_OFF_PWM
        TCCR0A = TCCR0A & ((map.raw & 0xF0) | 0x0F);
      #endif

      if ( val == LOW )
      {
        TC_THE_ONE_PORT &= ~ mask;
      }
      else
      {
        TC_THE_ONE_PORT |= mask;
      }
    }
  }
}


uint8_t digitalReadF( uint8_t const pin )
{
  dio_pin_map_entry_4_t map;
  uint8_t mask;
  uint8_t rv;

  if ( pin < TC_NUMBER_OF(pin_map_4) )
  {
    map.raw = dio_pin_map_entry_read_4( & pin_map_4[ pin ] );

    mask = tc_bit_to_mask( map.raw & 0x0F );

    TC_ATOMIC_OPTION
    {
      #if DIGITAL_TURNS_OFF_PWM
        TCCR0A = TCCR0A & ((map.raw & 0xF0) | 0x0F);
      #endif

      #if USE_DIRTY_DIGITAL_READ
        rv = TC_THE_ONE_PIN & mask;
      #else
        rv = ((uint8_t)(TC_THE_ONE_PORT & mask) != (uint8_t)(0)) ? HIGH : LOW;
      #endif
    }
  }
  else
  {
    rv = LOW;
  }

  return( rv );
}

#endif // TC_HAVE_ONE_DIO
