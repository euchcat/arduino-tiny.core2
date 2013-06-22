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

#include <Arduino.h>

#include <tc_hardware_mapping.h>
#include <tc_timer_types.h>

// fix: #include <tc_internal.h>

// fix: Move the following to an internal header file like wiring_private.h
// fix: void MillisAlaWatchdog_Init( void );


/*=============================================================================
  (fix? move to a header file)
=============================================================================*/

void tc_MillisViaWatchdog_Init( void );


/*=============================================================================
  Prepare type definitions for the timers (fix? move to a header file)
=============================================================================*/

void tc_MillisViaTimer_Init( void );

/** fix or rmv
#if TC_TIMER_0_IS_GENERIC_8_BIT

typedef tcTimerInterfaceGeneric8<0> tcTimerInterface0;

class tcTimer0: public tcTimerInterface0
{
public:
  __attribute__((always_inline)) static inline 
  void Initialize( void )
  {
    tc_MillisViaTimer_Init();
    CoreInitialize( 
        Fast_PWM_FF, 
        TC_PASTE2(Prescale_Value_,TC_MILLIS_TIMER_PRESCALE_VALUE) );
  }
};

class tcTimer0: public tcTimerInterface0
{
public:
  __attribute__((always_inline)) static inline 
  void Initialize( void )
  {
    CoreInitialize( 
        Phase_Correct_PWM_FF, 
        TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE) );
  }
};

#define TC_TIMER0  (1)

typedef tcTimer0 tcMillisTimer;

#endif
*/


/*=============================================================================
  Timer initialization functions 
=============================================================================*/

/* fix
#if defined( CORE_TIMER_COUNT )

//rmv #define MillisTimer_Prescale_Index  MillisTimer_(Prescale_Value_8)

// fix: Move to a header so other code has access to the values...
#if F_CPU >= 3000000L
  #define TimerInit_Prescale_Value  Prescale_Value_64
  #define TimerInit_Prescaler       (64)
#else
  #define TimerInit_Prescale_Value  Prescale_Value_8
  #define TimerInit_Prescaler       (8)
#endif

//rmv #define MillisTimer_(f)                           TIMER_PASTE_A( Timer, TC_TIMER_TO_USE_FOR_MILLIS_OR_TICKS, f )

#if CORE_TIMER_COUNT >= 1

__attribute__((weak)) void Timer0_Init( void )
{
//rmv?  Timer0_SetToPowerup();

//  Timer0_SetWaveformGenerationMode( Timer0_Fast_PWM_FF );

  Timer0_SetWaveformGenerationMode( Timer0_Phase_Correct_PWM_FF );

  Timer0_ClockSelect( TIMER_PASTE_A( Timer, 0, TimerInit_Prescale_Value ) );

//rmv  Timer0_ClockSelect( Timer0_Prescale_Value_64 );  // Timer0_Prescale_Value_8
}
#endif

#if CORE_TIMER_COUNT >= 2
void Timer1_Init( void );
#endif

#if CORE_TIMER_COUNT >= 3
void Timer2_Init( void );
#endif

#if CORE_TIMER_COUNT >= 4
#error Add more prototypes.
#endif

#endif
*/


/*=============================================================================
  Called from main to bring the application to life
=============================================================================*/
void init( void )
{
  sei();

/* fix 
  #if TC_NEED_PROCESSOR_INIT
    tc_ProcessorInit();
  #endif
*/

/* fix
  #if defined( CORE_TIMER_COUNT )

    #if CORE_TIMER_COUNT >= 1
      Timer0_Init();
    #endif

    #if CORE_TIMER_COUNT >= 2
      Timer1_Init();
    #endif

    #if CORE_TIMER_COUNT >= 3
      Timer2_Init();
    #endif

    #if CORE_TIMER_COUNT >= 4
      #error Add more calls.
    #endif

  #endif
*/

/* rmv
  tcMillisTimer::CoreInitialize( tcMillisTimer::Fast_PWM_FF, tcMillisTimer_Prescale_Index );
*/

  #if TC_TIMER_COUNT >= 1
    tcTimer0::Initialize();
  #endif

  #if TC_TIMER_COUNT >= 2
    tcTimer1::Initialize();
  #endif

  #if defined( EEARH )
    EEARH = (E2END >> 8) & 0xFF;
  #endif

#if TC_USE_WATCHDOG_FOR_MILLIS
    tc_MillisViaWatchdog_Init();
  #endif

/* fix
  // fix: Merge the following two #if into one...

  #if USE_WATCHDOG_FOR_MILLIS
    MillisAlaWatchdog_Init();
  #endif

  #if defined( TC_TIMER_TO_USE_FOR_MILLIS_OR_TICKS )
    #if TC_USE_TICKS_INSTEAD_OF_MILLIS
      tc_TicksInit();
    #elif ! USE_WATCHDOG_FOR_MILLIS
      tc_MillisAlaTimerInit();
    #endif
  #endif

  // ...fix
*/

  #if TC_ANALOG_COUNT > 0
    #if TC_INITIALIZE_ADC
      tcADC::CoreInitialize();
      #if defined( TC_FIXED_ANALOG_REFERENCE )
        tcADC::SetVoltageReference( (tcADC::adc_vr_t) TC_FIXED_ANALOG_REFERENCE );
      #endif
      #if TC_ENABLE_ADC_WHEN_NEEDED
        tcADC::Disable();
      #endif
    #endif
  #endif
}
