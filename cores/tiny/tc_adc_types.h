/*==============================================================================

  Copyright 2012 Rowdy Dog Software.

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

#ifndef tc_adc_types_h
#define tc_adc_types_h

#include <tc_macros.h>


/*=============================================================================
  ADC definitions common to all processors that have an ADC
=============================================================================*/

class tcADCBase
{
public:

  __attribute__((always_inline)) static inline 
  void Enable( void )
  {
    ADCSRA |= MASK1( ADEN );
  }

  __attribute__((always_inline)) static inline 
  void Disable( void )
  {
    ADCSRA &= ~ MASK1( ADEN );
  }

  typedef enum
  {
    Prescaler_Value_2     = 0b001,
    Prescaler_Value_4     = 0b010,
    Prescaler_Value_8     = 0b011,
    Prescaler_Value_16    = 0b100,
    Prescaler_Value_32    = 0b101,
    Prescaler_Value_64    = 0b110,
    Prescaler_Value_128   = 0b111,
    Prescaler_Index_1     = 0b001,
    Prescaler_Index_2     = 0b010,
    Prescaler_Index_3     = 0b011,
    Prescaler_Index_4     = 0b100,
    Prescaler_Index_5     = 0b101,
    Prescaler_Index_6     = 0b110,
    Prescaler_Index_7     = 0b111,
    Prescaler_Mask        = 0b111
  }
  adc_ps_t;

  __attribute__((always_inline)) static inline 
  void PrescalerSelect( adc_ps_t ps )
  {
    ADCSRA = (ADCSRA & ~MASK3(ADPS2,ADPS1,ADPS0)) | ((ps & Prescaler_Mask) << ADPS0);
  }

#if   F_CPU <=   200000
  // 200 KHz / 1 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  1
#elif F_CPU <=   400000
  // 400 KHz / 2 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  2
#elif F_CPU <=   800000
  // 800 KHz / 4 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  4
#elif F_CPU <=  1600000
  // 1.6 MHz / 8 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  8
#elif F_CPU <=  3200000
  // 3.2 MHz / 16 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  16
#elif F_CPU <=  6400000
  // 6.4 MHz / 32 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  32
#elif F_CPU <= 12800000
  // 12.8 MHz / 64 = 200 KHz
  #define TC_ADC_PRESCALE_VALUE  64
#elif F_CPU <= 20000000
  // 20.0 MHz / 128 = 156250 Hz
  #define TC_ADC_PRESCALE_VALUE  128
#else
  #error Add an entry for the selected processor speed.
#endif

  static const adc_ps_t PRESCALER   = TC_PASTE2(Prescaler_Value_,TC_ADC_PRESCALE_VALUE);
  static const unsigned DIVISOR     = (TC_ADC_PRESCALE_VALUE);

  __attribute__((always_inline)) static inline 
  void CoreInitialize( void )
  {
    ADCSRA = MASK1( ADEN ) | (PRESCALER << ADPS0);
  }

  __attribute__((always_inline)) static inline 
  void StartConversion( void )
  {
    ADCSRA |= MASK1( ADSC );
  }

  __attribute__((always_inline)) static inline 
  uint8_t ConversionInProgress( void )
  {
    return( (ADCSRA & (1<<ADSC)) != 0 );
  }

  __attribute__((always_inline)) static inline 
  uint16_t GetDataRegister( void )
  {
    return( ADC );
  }

};


#endif
