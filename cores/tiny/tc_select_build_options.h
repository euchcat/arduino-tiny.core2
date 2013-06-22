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

#ifndef tc_select_build_options_h
#define tc_select_build_options_h


/*=============================================================================
  Available random number generators
=============================================================================*/

#define TC_RANDOM_PARK_MILLER      1
#define TC_RANDOM_XORSHIFT         2
#define TC_RANDOM_JKISS32          3
#define TC_RANDOM_CRC32            4
#define TC_RANDOM_XORSHIFT_16      5


/*=============================================================================
  Include options for the selected variant
=============================================================================*/

#include <tc_build_options.h>
#include <tc_hardware_mapping.h>
#include <tc_macros.h>


/*=============================================================================
  The standard behaviour is to turn of PWM in digitalWrite and digitalRead.
  For mosting applications, the standard behaviour is not relevant.  Turning 
  this option off reduces the image size.
=============================================================================*/

#if ! defined( DIGITAL_TURNS_OFF_PWM )
#define DIGITAL_TURNS_OFF_PWM  1
#endif


/*=============================================================================
  This option allows inline versions of various core functions to be used to 
  reduce the image size
=============================================================================*/

#if ! defined( MAKE_IT_REALLY_TINY )
#define MAKE_IT_REALLY_TINY  1
#endif


/*=============================================================================
  This option allows digitalRead to return zero (LOW) / non-zero instead of 
  LOW / HIGH
=============================================================================*/

#if ! defined( USE_DIRTY_DIGITAL_READ )
#define USE_DIRTY_DIGITAL_READ  1
#endif


/*=============================================================================
  This option ensures that the digital I/O functions are atomic / ISR safe
=============================================================================*/

#if ! defined( MAKE_DIGITAL_IO_ATOMIC )
#define MAKE_DIGITAL_IO_ATOMIC  1
#endif


/*=============================================================================
  Macros based on options specified above
=============================================================================*/

#if MAKE_DIGITAL_IO_ATOMIC
#define TC_ATOMIC_OPTION  ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
#else
#define TC_ATOMIC_OPTION
#endif


/*=============================================================================
  Initialize the "secondary" timers?  Secondary timers are all the timers 
  except the one used for millis.
=============================================================================*/

#if ! defined( TC_INITIALIZE_SECONDARY_TIMERS )
#define TC_INITIALIZE_SECONDARY_TIMERS  1
#endif


/*=============================================================================
  Eliminate micros (saves four bytes of SRAM).
=============================================================================*/

#if ! defined( TC_NO_MICROS )
#define TC_NO_MICROS  0
#endif


/*=============================================================================
  Use the watchdog for millis instead of a timer?
=============================================================================*/

#if ! defined( TC_USE_WATCHDOG_FOR_MILLIS )
#define TC_USE_WATCHDOG_FOR_MILLIS  0
#endif


/*=============================================================================
  Use a timer for millis instead of the watchdog?
=============================================================================*/

#if ! defined( TC_USE_TIMER_FOR_MILLIS )
  #if TC_USE_WATCHDOG_FOR_MILLIS
    #define TC_USE_TIMER_FOR_MILLIS  0
  #else
    #define TC_USE_TIMER_FOR_MILLIS  1
  #endif
#endif


/*=============================================================================
  If a random number has not yet been specified use a basic good fast one
=============================================================================*/

#if ! defined( TC_RANDOM_FUNCTION_IS )
  #define TC_RANDOM_FUNCTION_IS  TC_RANDOM_XORSHIFT
#endif


/*=============================================================================
  Should the analog-to-digital converter be initialized by the core?
=============================================================================*/

#if ! defined( TC_INITIALIZE_ADC )
  #define TC_INITIALIZE_ADC  1
#endif


/*=============================================================================
  If the analog reference never changes, setting this to the analog reference 
  value saves some code and data space.  analogReference is not available if
  this is defined.
=============================================================================*/

// #define TC_FIXED_ANALOG_REFERENCE  (DEFAULT)


/*=============================================================================
  Calling analogRead disables the digital input buffer.
=============================================================================*/

#if ! defined( TC_ANALOG_READ_DISABLES_DIGITAL_READ )
  #define TC_ANALOG_READ_DISABLES_DIGITAL_READ  0
#endif


/*=============================================================================
  The ADC is left disabled except in the analogRead function.  A conversion
  takes longer (25 ADC clock cycles instead of 13).  Use this option to save 
  power when analogRead is not called very often.
=============================================================================*/

#if ! defined( TC_ENABLE_ADC_WHEN_NEEDED )
  #define TC_ENABLE_ADC_WHEN_NEEDED  0
#endif


/*=============================================================================
  Allow analogRead to be inline.  If not true, analogReadF is always used.
=============================================================================*/

#if ! defined( TC_INLINE_ANALOG_READ )
  #define TC_INLINE_ANALOG_READ  1
#endif


/*=============================================================================
  Sleep while performing an analog-to-digital conversion.
=============================================================================*/

#if ! defined( TC_SLEEP_DURING_ADC )
  #define TC_SLEEP_DURING_ADC  0
#endif


/*=============================================================================
  Try to ensure the millis interrupt will not wake the processor before an 
  analog-to-digital conversion finishes.  Only has an effect if 
  TC_SLEEP_DURING_ADC is enabled.
=============================================================================*/

#if ! defined( TC_SYNCHRONIZE_ADC_TO_MILLIS )
  #define TC_SYNCHRONIZE_ADC_TO_MILLIS  0
#endif


/*=============================================================================
  Ensure analogRead is safe to use in an interrupt service routine.  This only
  has an effect if TC_SLEEP_DURING_ADC is enabled.  If analogRead is never
  called in an interrupt service routine, disabling this options saves about
  a dozen Flash bytes.
=============================================================================*/

#if ! defined( TC_ANALOG_READ_IS_ISR_SAFE )
  #define TC_ANALOG_READ_IS_ISR_SAFE  1
#endif


/*=============================================================================
  Sanity checks 
=============================================================================*/

#if (TC_USE_WATCHDOG_FOR_MILLIS) && (TC_USE_TIMER_FOR_MILLIS)
#error TC_USE_WATCHDOG_FOR_MILLIS and TC_USE_TIMER_FOR_MILLIS cannot both be true.
#endif

#if ( TC_ENABLE_ADC_WHEN_NEEDED ) && ( ! TC_INITIALIZE_ADC ) && ( TC_ANALOG_COUNT > 0 )
#error TC_ENABLE_ADC_WHEN_NEEDED requires TC_INITIALIZE_ADC.
#endif


/*=============================================================================
  Composite settings
=============================================================================*/


/*=============================================================================
  Timer assignments
=============================================================================*/

#if TC_USE_TIMER_FOR_MILLIS

  #if TC_TIMER_COUNT >= 1
    #define TC_TIMER_TO_USE_FOR_MILLIS  0
  #endif

  #if TC_TIMER_COUNT == 2
    #define TC_TIMER_TO_USE_FOR_TONE  1
  #elif TC_TIMER_COUNT > 2
    #define TC_TIMER_TO_USE_FOR_USER  1
    #define TC_TIMER_TO_USE_FOR_TONE  2
  #endif

#else // ! TC_USE_TIMER_FOR_MILLIS (implying TC_USE_WATCHDOG_FOR_MILLIS or no millis) 

  #if TC_TIMER_COUNT >= 1
    #define TC_TIMER_TO_USE_FOR_TONE  0
  #endif
  #if TC_TIMER_COUNT >= 2
    #define TC_TIMER_TO_USE_FOR_USER  1
  #endif

#endif // TC_USE_TIMER_FOR_MILLIS


/*=============================================================================
  Prescaler for the timers depends on the processor clock speed
=============================================================================*/

#if F_CPU >= 3000000L
  #define TC_DEFAULT_TIMER_PRESCALE_VALUE  64
#elif F_CPU >= 1000000L
  #define TC_DEFAULT_TIMER_PRESCALE_VALUE  8
#else
  #define TC_DEFAULT_TIMER_PRESCALE_VALUE  1
#endif

#if defined( TC_USE_TIMER_FOR_MILLIS )

  #if ! defined( TC_MILLIS_TIMER_PRESCALE_VALUE ) // rmv? fix? || ! TC_USE_TICKS_INSTEAD_OF_MILLIS
    #define TC_MILLIS_TIMER_PRESCALE_VALUE  TC_DEFAULT_TIMER_PRESCALE_VALUE
  #endif

  #define tcMillisTimer_Prescale_Index  tcMillisTimer::TC_PASTE2(Prescale_Value_,TC_MILLIS_TIMER_PRESCALE_VALUE)
  #define tcMillisTimer_Prescale_Value  (TC_MILLIS_TIMER_PRESCALE_VALUE)

  #define MILLISTIMER_OVF_vect  TC_PASTE3(TIM,TC_TIMER_TO_USE_FOR_MILLIS,_OVF_vect)

#endif // TC_USE_TIMER_FOR_MILLIS


#endif
