/*==============================================================================

  Copyright 2010 Rowdy Dog Software.

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


#if TC_ANALOG_COUNT > 0

#if TC_SLEEP_DURING_ADC
#include <avr/sleep.h>
#endif

uint8_t tc_analog_reference = DEFAULT;

#if TC_ANALOG_READ_DISABLES_DIGITAL_READ

#if TC_HAVE_ONE_DIDR

static uint8_t const didr_map[] PROGMEM =
{
  TC_DIO_BITMASK( TC_ADC_0 ),
#if defined( TC_ADC_1 )
  TC_DIO_BITMASK( TC_ADC_1 ),
#endif
#if defined( TC_ADC_2 )
  TC_DIO_BITMASK( TC_ADC_2 ),
#endif
#if defined( TC_ADC_3 )
  TC_DIO_BITMASK( TC_ADC_3 ),
#endif
#if defined( TC_ADC_4 )
  TC_DIO_BITMASK( TC_ADC_4 ),
#endif
#if defined( TC_ADC_5 )
  TC_DIO_BITMASK( TC_ADC_5 ),
#endif
#if defined( TC_ADC_6 )
  TC_DIO_BITMASK( TC_ADC_6 ),
#endif
#if defined( TC_ADC_7 )
  TC_DIO_BITMASK( TC_ADC_7 ),
#endif
#if defined( TC_ADC_8 )
  TC_DIO_BITMASK( TC_ADC_8 ),
#endif
#if defined( TC_ADC_9 )
  #error Add more entries.
#endif
};

#define didr_pin_map_entry_read  pgm_read_byte

#endif // TC_HAVE_ONE_DIDR

#endif // #if TC_ANALOG_READ_DISABLES_DIGITAL_READ

int analogReadF( uint8_t pin )
{
  int rv;

  pin = (pin >= A0) ? (pin - A0) : (pin);

  #if TC_ANALOG_READ_DISABLES_DIGITAL_READ
    #if TC_HAVE_ONE_DIDR
      if ( pin < TC_NUMBER_OF(didr_map) )
      {
        uint8_t mask;
        mask = didr_pin_map_entry_read( & didr_map[ pin ] );
        TC_THE_ONE_DIDR |= mask;
      }
    #else 
      #error Need code.
    #endif
  #endif

  #if TC_ENABLE_ADC_WHEN_NEEDED
    tcADC::Enable();
  #endif

  if ( pin != CURRENTCHANNEL )
  {
    #if ! defined( TC_FIXED_ANALOG_REFERENCE )
      tcADC::SetVoltageReference( (tcADC::adc_vr_t) tc_analog_reference );
    #endif
    tcADC::SetInputChannel( (tcADC::adc_ic_t) pin );
  }

  #if TC_SLEEP_DURING_ADC

    set_sleep_mode( SLEEP_MODE_IDLE );
    sleep_enable();

    #if TC_SYNCHRONIZE_ADC_TO_MILLIS

      if ( tcMillisTimer::GetCount() >= TC_StartConversionThreshold )
      {
        int8_t NapCount;

        NapCount = 0;
        
        do
        {
          sleep_cpu();
          ++NapCount;
        }
        while ( (tcMillisTimer::GetCount() >= TC_StartConversionThreshold) && (NapCount < 3) );
      }

    #endif

    if ( (!TC_ANALOG_READ_IS_ISR_SAFE) || (SREG & (1 << SREG_I)) )
    {
      ADCSRA |= (1 << ADIF) | (1 << ADIE);

      do
      {
        sei();
        sleep_cpu();
        cli();
      }
      while ( (ADCSRA & (1 << ADSC)) != 0 );
      sei();

      ADCSRA &= ~ _BV( ADIE );
    }
    else
    {
      tcADC::StartConversion();
      while( tcADC::ConversionInProgress() );
    }

    sleep_disable();

    rv = tcADC::GetDataRegister();

  #else

    tcADC::StartConversion();

    while( tcADC::ConversionInProgress() );

    rv = tcADC::GetDataRegister();

  #endif

  #if TC_ENABLE_ADC_WHEN_NEEDED
    tcADC::Disable();
  #endif

  return( rv );
}

#if TC_SLEEP_DURING_ADC
EMPTY_INTERRUPT( ADC_vect );
#endif

#endif
