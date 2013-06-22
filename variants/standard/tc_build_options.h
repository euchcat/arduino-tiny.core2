/*==============================================================================

  Copyright 2011 Rowdy Dog Software.

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

#ifndef tc_build_options_h
#define tc_build_options_h


/*=============================================================================
  Initialize the analog-to-digital converter?  If it is not needed, leaving 
  it uninitialized will save a considerable amount of power.
=============================================================================*/

// #define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER  1


/*=============================================================================
  Initialize the "secondary" timers?  Secondary timers are all the timers 
  except the one used for millis.
=============================================================================*/

// #define TC_INITIALIZE_SECONDARY_TIMERS  1


/*=============================================================================
  Provide a ticks function instead of millis/micros for time management.
=============================================================================*/

// #define TC_USE_TICKS_INSTEAD_OF_MILLIS  0


/*=============================================================================
  Use a 16 bit datatype instead of a 32 bit datatype for millis and micros
=============================================================================*/

// #define TC_USE_16_BIT_FOR_MILLIS  0


/*=============================================================================
  Use the watchdog for millis instead of a timer
=============================================================================*/

// #define TC_USE_WATCHDOG_FOR_MILLIS  0


/*=============================================================================
  The standard behaviour is to turn of PWM in digitalWrite and digitalRead.
  For mosting applications, the standard behaviour is not relevant.  Turning 
  this option off reduces the image size.
=============================================================================*/

// #define DIGITAL_TURNS_OFF_PWM  1


/*=============================================================================
  This option allows inline versions of various core functions to be used in 
  an attempt to dramatically reduce the image size
=============================================================================*/

// #define MAKE_IT_REALLY_TINY  1


/*=============================================================================
  This option allows digitalRead to return zero (LOW) / non-zero instead of 
  LOW / HIGH
=============================================================================*/

// #define USE_DIRTY_DIGITAL_READ  1


/*=============================================================================
  Select a specific random number generator.  The choices are...

    TC_RANDOM_PARK_MILLER   - Libc generator used in the Standard Core
    TC_RANDOM_XORSHIFT      - Marsaglia's favourite from his paper on XorShift generators
    TC_RANDOM_JKISS32       - No multiply generator from David Jones' paper on Good Practice
    TC_RANDOM_CRC32         - CRC32 generator mentioned by Bob Jenkins on his website
    TC_RANDOM_XORSHIFT_16   - Generator mention by "cjh" on his blog

  The default generator is XorShift.  XorShift16 will very likely be used for 
  the t13 processor and maybe for the t24 and t25 processors.
=============================================================================*/

// #define TC_RANDOM_FUNCTION_IS      TC_RANDOM_XORSHIFT


/*=============================================================================
  Automatically reseed random each time the processor resets?  The current 
  seed is stored towards the end of EEPROM (near E2END).
=============================================================================*/

// #define TC_RESEED_RANDOM  1


/*=============================================================================
  Automatically set OSCCAL from a value obtained by Tiny Tuner 2.  The ideal
  OSCCAL value is stored towards the end of EEPROM (near E2END).
=============================================================================*/

// #define TC_SET_OSCCAL_FROM_TINY_TUNER  1


/*=============================================================================
  Normally, code in this core selects the timer prescalers based on the 
  processors clock speed.  These macros allow the prescalers to be 
  overridden.  The millis timer prescaler can only be changed if 
  TC_USE_TICKS_INSTEAD_OF_MILLIS is 1 otherwise the value selected by the 
  core is always used.
=============================================================================*/

// #define TC_MILLISTIMER_PRESCALE_VALUE   64
// #define TC_TONETIMER_PRESCALE_VALUE     64
// #define TC_OTHERTIMER_PRESCALE_VALUE    64


/*=============================================================================
  This option ensures that the digital I/O functions are atomic / ISR safe
=============================================================================*/

// #define MAKE_DIGITAL_IO_ATOMIC  1


#endif
