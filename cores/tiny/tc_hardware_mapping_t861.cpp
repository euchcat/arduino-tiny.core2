/*==============================================================================

  Copyright 2013 Rowdy Dog Software.

  This file is part of Arduino-Tiny.

  Arduino-Tiny is free software: you can redistribute it and/or modify it 
  under the terms of the GNU Lesser General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  Arduino-Tiny is distributed in the hope that it will be useful, but 
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with Arduino-Tiny.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

#include <Arduino.h>

#if defined( __AVR_ATtinyX61__ )

#if TC_DEFAULT_DIGITAL_MAPPING

#include <avr/io.h>

#define TC_PASTE2I(a,b)         a##b
#define TC_PASTE2(a,b)          TC_PASTE2I(a,b)

#define DIO_REGISTER_TO_OFFSET(r)     ( (uint8_t)((unsigned)(&r)) )

#define DIO_BASE                      DIO_REGISTER_TO_OFFSET(TC_PASTE2( TC_BASE_REGISTER, TC_BASE_PORT ))

#define DIO_PIN_OFFSET                ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(PIN,TC_BASE_PORT)) - DIO_BASE))
#define DIO_DDR_OFFSET                ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(DDR,TC_BASE_PORT)) - DIO_BASE))
#define DIO_PORT_OFFSET               ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(PORT,TC_BASE_PORT)) - DIO_BASE))

#if defined( PINA )
#define DIO_PORT_A_OFFSET             ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(TC_BASE_REGISTER,A)) - DIO_BASE))
#define DIO_PORT_A_INDEX              (DIO_PORT_A_OFFSET/3)
#endif

#if defined( PINB )
#define DIO_PORT_B_OFFSET             ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(TC_BASE_REGISTER,B)) - DIO_BASE))
#define DIO_PORT_B_INDEX              (DIO_PORT_B_OFFSET/3)
#endif

#if defined( PINC )
#define DIO_PORT_C_OFFSET             ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(TC_BASE_REGISTER,C)) - DIO_BASE))
#define DIO_PORT_C_INDEX              (DIO_PORT_C_OFFSET/3)
#endif

#if defined( PIND )
#define DIO_PORT_D_OFFSET             ((uint8_t)(DIO_REGISTER_TO_OFFSET(TC_PASTE2(TC_BASE_REGISTER,D)) - DIO_BASE))
#define DIO_PORT_D_INDEX              (DIO_PORT_D_OFFSET/3)
#endif

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
/*
  uint8_t mask;

  if ( pin < TC_NUMBER_OF(pin_map_4) )
  {
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
*/
}

#endif

#endif
