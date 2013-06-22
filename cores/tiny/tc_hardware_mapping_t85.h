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

#ifndef tc_hardware_mapping_t85_h
#define tc_hardware_mapping_t85_h

#include <tc_select_processor.h>


/*=============================================================================
  Hardware definitions for the ATtiny85
=============================================================================*/

#if defined( __AVR_ATtinyX5__ )

#define TC_PWM_0        TCCR0A, COM0A
#define TC_PWM_1        TCCR0A, COM0B

#define TC_PWM_COUNT          (2)

#define TC_B0           B, 0, 0,         TC_NO_DIDR
#define TC_B1           B, 1, 1,         TC_NO_DIDR
#define TC_B2           B, 2, TC_NO_PWM, 0
#define TC_B3           B, 3, TC_NO_PWM, 0
#define TC_B4           B, 4, TC_NO_PWM, 0
#define TC_B5           B, 5, TC_NO_PWM, 0

#define TC_PIN_0        TC_B0
#define TC_PIN_1        TC_B1
#define TC_PIN_2        TC_B2
#define TC_PIN_3        TC_B3
#define TC_PIN_4        TC_B4
#define TC_PIN_5        TC_B5

#define TC_PIN_6        TC_B5
#define TC_PIN_7        TC_B2
#define TC_PIN_8        TC_B4
#define TC_PIN_9        TC_B3

#define TC_DEFAULT_DIGITAL_MAPPING  (1)

#define TC_DIGITAL_COUNT      (6)

#define TC_RESET_INCLUDED     (1)

// fix: #define TC_ANALOG_COUNT       (4)

// fix: #define TC_BASE_IO_PORT       B
// fix: #define TC_BASE_IO_REGISTER   PIN

#define TC_TIMER_COUNT        (1)

#define TC_TIMER_0_IS_GENERIC_8_BIT   (1)

// fix? Allow the following to be overridden by a variants header file?
// rmv #define TC_TIMER_TO_USE_FOR_TONE      0

// Provide unified register names

#if defined(TIMSK) && ! defined(TIMSK0)
#define TIMSK0 TIMSK
#endif

#if defined(TIFR) && ! defined(TIFR0)
#define TIFR0 TIFR
#endif

#endif


#endif  // tc_hardware_mapping_t85_h
