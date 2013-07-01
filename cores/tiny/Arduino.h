#ifndef Arduino_h
#define Arduino_h

#define TC_VERSION 200

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/atomic.h>

// fix or rmv #include <binary.h>

#include "tc_select_build_options.h"
// fix or rmv #include "tc_adc.h"
#include "tc_macros.h"
#include "tc_hardware_mapping.h"  // fix?  Header for each processor?
#include "tc_timer_types.h"
// fix or rmv #include <core_timers.h>

// fix or rmv #include <PwmTimer.h>
// fix or rmv #include <TinyDebugSerial.h>

#if defined( TIMER_TO_USE_FOR_TONE )
// fix or rmv #include <ToneTimer.h>
#endif

#include <Print.h>


/*=============================================================================
  Support for inline PROGMEM string constants
=============================================================================*/

class __FlashStringHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))


#ifdef __cplusplus


/*=============================================================================
  Arduino datatypes
=============================================================================*/

typedef /*uint8_t*/ bool boolean;
typedef uint8_t byte;


/*=============================================================================
  Arduino general purpose constants
=============================================================================*/

static const double PI =          (M_PI);
static const double HALF_PI =     (M_PI/(2.0));
static const double TWO_PI =      ((2.0)*M_PI);
static const double DEG_TO_RAD =  (PI/(180.0));
static const double RAD_TO_DEG =  ((180.0)/PI);


/*=============================================================================
  Arduino macros
=============================================================================*/

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )


/*=============================================================================
  abs - return the absoluate value
=============================================================================*/

/* Libc provides an abs macro for the int datattype.  Remove the macro so we 
can provide an overloaded function.  The Libc functions are used instead of a 
macro because they seem to result in a smaller image. */

#ifdef abs
#undef abs
#endif

inline int abs( int __i ) { return( __builtin_abs( __i ) ); }
inline long abs( long __i ) { return( __builtin_labs( __i ) ); }
inline double abs( double __d ) { return( fabs( __d ) ); }


/*=============================================================================
  round - round a floating-point number away from zero return a long
=============================================================================*/

/* round is just not going to work.  Like provideyourown@gmail.com, I have no 
idea why it works for ATmega processors.  The problem is Libc defines a round 
that is not compatible with the Arduino round and the Libc version cannot be 
overridden.  round gets the boot. */

/*
#ifdef round
#undef round
#endif

inline long round( float x ) { return( lroundf( x ) ); }
inline long round( double x ) { return( lround( x ) ); }
inline long round( long double x ) { return( lroundl( x ) ); }
*/


/*=============================================================================
  max - return the maximum of two numbers
=============================================================================*/

/* http://arduino.cc/forum/index.php/topic,84364.msg640438.html#msg640438 */

#define max(a,b) \
  ({ \
    typeof (a) _a = (a); \
    typeof (b) _b = (b); \
    _a > _b ? _a : _b; \
  })


/*=============================================================================
  min - return the minimum of two numbers
=============================================================================*/

/* http://arduino.cc/forum/index.php/topic,84364.msg640438.html#msg640438 */

#define min(a,b) \
  ({ \
    typeof (a) _a = (a); \
    typeof (b) _b = (b); \
    _a < _b ? _a : _b; \
  })


/*=============================================================================
  constrain - constrain a value between a minimum and a maximum
=============================================================================*/

/*
#define constrain(v,lo,hi) \
  ({ \
    typeof (v) _v = (v); \
    typeof (lo) _lo = (lo); \
    typeof (hi) _hi = (hi); \
    (_v < _lo) ? (_lo) : ( (_v > _hi) ? (_hi) : (_v) ); \
  })
*/
#define constrain(v,lo,hi) ( max( min(v,hi), lo ) )


/*=============================================================================
  sq - return a value squared
=============================================================================*/

#define sq(x) \
  ({ \
    typeof (x) _x = (x); \
    _x * _x; \
  })


/*=============================================================================
  radians - convert degress to radians
=============================================================================*/

// inline double radians( double deg ) { return((deg)*DEG_TO_RAD); }


/*=============================================================================
  degrees - convert radians to degress
=============================================================================*/

// inline double degrees( double rad ) { return((rad)*RAD_TO_DEG); }


/*=============================================================================
  Define macros that have the Compare Match Output Mode bits combined
=============================================================================*/

#define TC_DEFINE_COM1( _timer_, _channel_ )  (((1 << TC_PASTE4(COM,_timer_,_channel_,0))))
#define TC_DEFINE_COM2( _timer_, _channel_ )  (((1 << TC_PASTE4(COM,_timer_,_channel_,1)) | (1 << TC_PASTE4(COM,_timer_,_channel_,0))))

#if defined( COM0A0 )
  #if defined( COM0A2 )
    #error Timer 0 / channel A / bit 2 not supported by this version.
  #endif
  #if defined( COM0A1 )
    #define COM0A  TC_DEFINE_COM2(0,A)
  #else
    #define COM0A  TC_DEFINE_COM1(0,A)
  #endif
#endif

#if defined( COM0B0 )
  #if defined( COM0B2 )
    #error Timer 0 / channel B / bit 2 not supported by this version.
  #endif
  #if defined( COM0B1 )
    #define COM0B  TC_DEFINE_COM2(0,B)
  #else
    #define COM0B  TC_DEFINE_COM1(0,B)
  #endif
#endif

#if defined( COM0C0 )
  #error Timer 0 / channel C not supported by this version.
#endif

#if defined( COM0D0 )
  #error Timer 0 / channel D not supported by this version.
#endif


#if defined( COM1A0 )
  #if defined( COM1A2 )
    #error Timer 1 / channel A / bit 2 not supported by this version.
  #endif
  #if defined( COM1A1 )
    #define COM1A  TC_DEFINE_COM2(0,A)
  #else
    #define COM1A  TC_DEFINE_COM1(0,A)
  #endif
#endif

#if defined( COM1B0 )
  #if defined( COM1B2 )
    #error Timer 1 / channel B / bit 2 not supported by this version.
  #endif
  #if defined( COM1B1 )
    #define COM1B  TC_DEFINE_COM2(0,B)
  #else
    #define COM1B  TC_DEFINE_COM1(0,B)
  #endif
#endif

#if defined( COM1C0 )
  #error Timer 1 / channel C not supported by this version.
#endif

#if defined( COM1D0 )
  #warning Timer 1 / channel D not supported by this version.
#endif


#if defined( COM2A0 )
#error
#endif

#if defined( COM2B0 )
#error
#endif

#if defined( COM2C0 )
  #error Timer 2 / channel C not supported by this version.
#endif

#if defined( COM2D0 )
  #error Timer 2 / channel D not supported by this version.
#endif


/*=============================================================================
  Macros summarizing the hardware
=============================================================================*/

#if defined( PORTA )
  #define TC_HAVE_PORTA  1
  #define TC_COUNT_PORTA  1
#else
  #define TC_HAVE_PORTA  0
  #define TC_COUNT_PORTA
#endif

#if defined( PORTB )
  #define TC_HAVE_PORTB  1
  #define TC_COUNT_PORTB  1
#else
  #define TC_HAVE_PORTB  0
  #define TC_COUNT_PORTB
#endif

#if defined( PORTC )
  #define TC_HAVE_PORTC  1
  #define TC_COUNT_PORTC  1
#else
  #define TC_HAVE_PORTC  0
  #define TC_COUNT_PORTC
#endif

#if defined( PORTD )
  #define TC_HAVE_PORTD  1
  #define TC_COUNT_PORTD  1
#else
  #define TC_HAVE_PORTD  0
  #define TC_COUNT_PORTD
#endif

#define TC_HAVE_PORT_LIST  TC_PASTE5( 9, TC_HAVE_PORTA, TC_HAVE_PORTB, TC_HAVE_PORTC, TC_HAVE_PORTD )
#define TC_COUNT_PORT_LIST  TC_PASTE4( TC_COUNT_PORTA, TC_COUNT_PORTB, TC_COUNT_PORTC, TC_COUNT_PORTD )

#if (TC_COUNT_PORT_LIST == 1)
  #define TC_PORT_COUNT  1
  #if (TC_HAVE_PORT_LIST == 90100)
    #define TC_HAVE_ONE_DIO  (1)
    #define TC_THE_ONE_PORT  PORTB
    #define TC_THE_ONE_PIN  PINB
    #define TC_THE_ONE_DDR  DDRB
  #endif
#elif (TC_COUNT_PORT_LIST == 11)
  #define TC_PORT_COUNT  2
#elif (TC_COUNT_PORT_LIST == 111)
  #define TC_PORT_COUNT  3
#elif (TC_COUNT_PORT_LIST == 1111)
  #define TC_PORT_COUNT  4
#endif

#if defined( DIDR0 )
  #define TC_HAVE_DIDR0  1
  #define TC_COUNT_DIDR0  1
#else
  #define TC_HAVE_DIDR0  0
  #define TC_COUNT_DIDR0
#endif

#if defined( DIDR1 )
  #define TC_HAVE_DIDR1  1
  #define TC_COUNT_DIDR1  1
#else
  #define TC_HAVE_DIDR1  0
  #define TC_COUNT_DIDR1
#endif

#define TC_HAVE_DIDR_LIST  TC_PASTE3( 9, TC_HAVE_DIDR0, TC_HAVE_DIDR1 )
#define TC_COUNT_DIDR_LIST  TC_PASTE2( TC_COUNT_DIDR0, TC_COUNT_DIDR1 )

#if (TC_COUNT_DIDR_LIST == 1)
  #define TC_DIDR_COUNT  1
  #if (TC_HAVE_DIDR_LIST == 910)
    #define TC_HAVE_ONE_DIDR  (1)
    #define TC_THE_ONE_DIDR  DIDR0
  #endif
#elif (TC_COUNT_DIDR_LIST == 11)
  #define TC_DIDR_COUNT  2
#endif


/*=============================================================================
  Convenient interfaces for the timers
=============================================================================*/

#if TC_TIMER_0_IS_GENERIC_8_BIT
typedef tcTimerInterfaceGeneric8<0> tcTimerInterface0;
#endif

#if TC_TIMER_1_IS_GENERIC_16_BIT
typedef tcTimerInterfaceGeneric16<1> tcTimerInterface1;
#endif


/*=============================================================================
  millis timer interface
=============================================================================*/

#if defined( TC_TIMER_TO_USE_FOR_MILLIS )

void tc_MillisViaTimer_ForceReference( void );

class tcMillisTimer: public TC_PASTE2( tcTimerInterface, TC_TIMER_TO_USE_FOR_MILLIS )
{
public:
  __attribute__((always_inline)) static inline 
  void Initialize( void )
  {
    CoreInitialize( true, tcMillisTimer_Prescale_Index, false );
/* rmv
    CoreInitialize( 
        Fast_PWM_FF, 
        tcMillisTimer_Prescale_Index,
        true );
*/
    tc_MillisViaTimer_ForceReference();
  }

};

class TC_PASTE2( tcTimer, TC_TIMER_TO_USE_FOR_MILLIS ): public tcMillisTimer
{
};

#if TC_TIMER_TO_USE_FOR_MILLIS == 0
  #define TC_TIMER_0  1
#endif

#if TC_TIMER_TO_USE_FOR_MILLIS == 1
  #define TC_TIMER_1  1
#endif

#if TC_TIMER_TO_USE_FOR_MILLIS == 2
  #define TC_TIMER_2  1
#endif

#endif


/*=============================================================================
  tone timer interface
=============================================================================*/

#if defined( TC_TIMER_TO_USE_FOR_TONE )

class tcToneTimer: public TC_PASTE2( tcTimerInterface, TC_TIMER_TO_USE_FOR_TONE )
{
public:
  __attribute__((always_inline)) static inline 
  void Initialize( void )
  {
    if ( TC_INITIALIZE_SECONDARY_TIMERS )
    {
      CoreInitialize( false, TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE), true );
/* rmv
      CoreInitialize( 
          Phase_Correct_PWM_FF,
          TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE),
          false );
*/
    }
  }

};

class TC_PASTE2( tcTimer, TC_TIMER_TO_USE_FOR_TONE ): public tcToneTimer
{
};

#if TC_TIMER_TO_USE_FOR_TONE == 0
  #define TC_TIMER_0  1
#endif

#if TC_TIMER_TO_USE_FOR_TONE == 1
  #define TC_TIMER_1  1
#endif

#if TC_TIMER_TO_USE_FOR_TONE == 2
  #define TC_TIMER_2  1
#endif

#endif


/*=============================================================================
  Provide classes for the remaining timers
=============================================================================*/

#if TC_TIMER_COUNT >= 1
  #if ! TC_TIMER_0
    class tcTimer0: public TC_PASTE2( tcTimerInterface, 0 )
    {
    public:
      __attribute__((always_inline)) static inline 
      void Initialize( void )
      {
        if ( TC_INITIALIZE_SECONDARY_TIMERS )
        {
          CoreInitialize( false, TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE), true );
        }
      }
    };
    #define TC_TIMER_0  1
  #endif
#endif

#if TC_TIMER_COUNT >= 2
  #if ! TC_TIMER_1
    class tcTimer1: public TC_PASTE2( tcTimerInterface, 1 )
    {
    public:
      __attribute__((always_inline)) static inline 
      void Initialize( void )
      {
        if ( TC_INITIALIZE_SECONDARY_TIMERS )
        {
          CoreInitialize( false, TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE), true );
/* rmv
          CoreInitialize( 
              Phase_Correct_PWM_FF,
              TC_PASTE2(Prescale_Value_,TC_DEFAULT_TIMER_PRESCALE_VALUE),
              false );
*/
        }
      }
    };
    #define TC_TIMER_1  1
  #endif
#endif

#if TC_TIMER_COUNT >= 3
#if ! TC_TIMER_2
#endif
#endif


/*=============================================================================
  Macros to assist with pin defintions
=============================================================================*/

#define TC_DDR_Z(port,bit,pwm,didr)  TC_PASTE2(DDR,port)
// rmv? #define TC_DDR(pin)  TC_PASTE2(DDR,TC_DIO_PORT_Z(pin))

#define TC_PIN_Z(port,bit,pwm,didr)  TC_PASTE2(PIN,port)
#define TC_PIN(pin)  TC_PIN_Z(pin)

#define TC_PORT_Z(port,bit,pwm,didr)  TC_PASTE2(PORT,port)
// rmv? #define TC_PORT(pin)  TC_PASTE2(PORT,TC_DIO_PORT_Z(pin))

#define TC_DIDR_Z(port,bit,pwm,didr)  TC_PASTE2(DIDR,didr)
// rmv? #define TC_DIDR(pin)  TC_PASTE2(DIDR,TC_DIO_DIDR_Z(pin))

#define TC_PWM_TIMER_Z(timer,channel)  timer
#define TC_PWM_TIMER(pwm)  TC_PWM_TIMER_Z(pwm)

#define TC_PWM_CHANNEL_Z(timer,channel)  channel
#define TC_PWM_CHANNEL(pwm)  TC_PWM_CHANNEL_Z(pwm)

#define TC_DIO_BIT_Z(port,bit,pwm,didr)  bit
#define TC_DIO_BIT(pin)  TC_DIO_BIT_Z(pin)
#define TC_DIO_BITMASK(pin)  (1 << TC_DIO_BIT_Z(pin))

#define TC_DIO_PWM_Z(port,bit,pwm,didr)  pwm
// rmv? #define TC_DIO_PWM(pin)  TC_DIO_PWM_Z(pin)

#define TC_DIO_TIMER_Z(port,bit,pwm,didr)  TC_PWM_TIMER(TC_PASTE2(TC_PWM_,pwm))
// rmv? #define TC_DIO_TIMER(pin)  TC_PWM_TIMER(TC_PASTE2(TC_PWM_,TC_DIO_PWM_Z(pin)))

#define TC_DIO_CHANNEL_Z(port,bit,pwm,didr)  TC_PWM_CHANNEL(TC_PASTE2(TC_PWM_,pwm))
#define TC_DIO_CHANNEL(pin)  TC_PWM_CHANNEL(TC_PASTE2(TC_PWM_,TC_DIO_PWM_Z(pin)))

#define TC_NO_TIMER     (*(volatile uint8_t *)(0))
#define TC_NO_CHANNEL   (0)

#define TC_PWM_TC_NO_PWM  TC_NO_TIMER, TC_NO_CHANNEL

#define DIDRTC_NO_DIDR  (*(volatile uint8_t *)(0))

// fix: "& DIDR0"
#define TC_DEFINE_INLINE(pin) { & TC_DDR_Z( pin ), & TC_PIN_Z( pin ), & TC_PORT_Z( pin ), & TC_DIDR_Z( pin ), (1 << TC_DIO_BIT_Z(pin)), & TC_DIO_TIMER_Z( pin ), TC_DIO_CHANNEL_Z( pin ) }


/*=============================================================================
  Pin definitions used by the inline functions
=============================================================================*/

typedef struct
{
  uint8_t volatile * const    ddr;
  uint8_t volatile * const    pin;
  uint8_t volatile * const    port;
  uint8_t volatile * const    didr;  // WARNING: It is assumed that the bitmask is the same as for the registers above.
  uint8_t                     dio_bitmask;
  uint8_t volatile * const    pwm;
  uint8_t                     pwm_channel;
}
tc_inline_dio_t;

static tc_inline_dio_t const tc_inline_dio[] =
{
  TC_DEFINE_INLINE(TC_PIN_0),
#if defined( TC_PIN_1 )
  TC_DEFINE_INLINE(TC_PIN_1),
#endif
#if defined( TC_PIN_2 )
  TC_DEFINE_INLINE(TC_PIN_2),
#endif
#if defined( TC_PIN_3 )
  TC_DEFINE_INLINE(TC_PIN_3),
#endif
#if defined( TC_PIN_4 )
  TC_DEFINE_INLINE(TC_PIN_4),
#endif
#if defined( TC_PIN_5 )
  TC_DEFINE_INLINE(TC_PIN_5),
#endif
#if defined( TC_PIN_6 )
  TC_DEFINE_INLINE(TC_PIN_6),
#endif
#if defined( TC_PIN_7 )
  TC_DEFINE_INLINE(TC_PIN_7),
#endif
#if defined( TC_PIN_8 )
  TC_DEFINE_INLINE(TC_PIN_8),
#endif
#if defined( TC_PIN_9 )
  TC_DEFINE_INLINE(TC_PIN_9),
#endif
#if defined( TC_PIN_10 )
  TC_DEFINE_INLINE(TC_PIN_10),
#endif
#if defined( TC_PIN_11 )
  TC_DEFINE_INLINE(TC_PIN_11),
#endif
#if defined( TC_PIN_12 )
  TC_DEFINE_INLINE(TC_PIN_12),
#endif
#if defined( TC_PIN_13 )
  TC_DEFINE_INLINE(TC_PIN_13),
#endif
#if defined( TC_PIN_14 )
  TC_DEFINE_INLINE(TC_PIN_14),
#endif
#if defined( TC_PIN_15 )
  TC_DEFINE_INLINE(TC_PIN_15),
#endif
#if defined( TC_PIN_16 )
  TC_DEFINE_INLINE(TC_PIN_16),
#endif
#if defined( TC_PIN_17 )
  TC_DEFINE_INLINE(TC_PIN_17),
#endif
#if defined( TC_PIN_18 )
  TC_DEFINE_INLINE(TC_PIN_18),
#endif
#if defined( TC_PIN_19 )
  TC_DEFINE_INLINE(TC_PIN_19),
#endif
#if defined( TC_PIN_20 )
  TC_DEFINE_INLINE(TC_PIN_20),
#endif
#if defined( TC_PIN_21 )
  TC_DEFINE_INLINE(TC_PIN_21),
#endif
#if defined( TC_PIN_22 )
  TC_DEFINE_INLINE(TC_PIN_22),
#endif
#if defined( TC_PIN_23 )
  TC_DEFINE_INLINE(TC_PIN_23),
#endif
#if defined( TC_PIN_24 )
  TC_DEFINE_INLINE(TC_PIN_24),
#endif
#if defined( TC_PIN_25 )
  TC_DEFINE_INLINE(TC_PIN_25),
#endif
#if defined( TC_PIN_26 )
  TC_DEFINE_INLINE(TC_PIN_26),
#endif
#if defined( TC_PIN_27 )
  TC_DEFINE_INLINE(TC_PIN_27),
#endif
#if defined( TC_PIN_28 )
  #error Add more entries.
#endif
};

#if TC_ANALOG_COUNT > 0

static tc_inline_dio_t const tc_inline_adc[] =
{
  TC_DEFINE_INLINE(TC_ADC_0),
#if defined( TC_ADC_1 )
  TC_DEFINE_INLINE(TC_ADC_1),
#endif
#if defined( TC_ADC_2 )
  TC_DEFINE_INLINE(TC_ADC_2),
#endif
#if defined( TC_ADC_3 )
  TC_DEFINE_INLINE(TC_ADC_3),
#endif
#if defined( TC_ADC_4 )
  TC_DEFINE_INLINE(TC_ADC_4),
#endif
#if defined( TC_ADC_5 )
  TC_DEFINE_INLINE(TC_ADC_5),
#endif
#if defined( TC_ADC_6 )
  TC_DEFINE_INLINE(TC_ADC_6),
#endif
#if defined( TC_ADC_7 )
  TC_DEFINE_INLINE(TC_ADC_7),
#endif
#if defined( TC_ADC_8 )
  TC_DEFINE_INLINE(TC_ADC_8),
#endif
#if defined( TC_ADC_9 )
  TC_DEFINE_INLINE(TC_ADC_9),
#endif
#if defined( TC_ADC_10 )
  TC_DEFINE_INLINE(TC_ADC_10),
#endif
#if defined( TC_ADC_11 )
  TC_DEFINE_INLINE(TC_ADC_11),
#endif
#if defined( TC_ADC_12 )
  #error Add more entries.
#endif
};

#endif


/*=============================================================================
  AVR macros
=============================================================================*/

#define TC_SFR_IO_REG_P(sfr) ( (sfr) <= (volatile uint8_t*) &_SFR_IO8(0x20) )


/*=============================================================================
  "Called" when a pin number is out of range
=============================================================================*/

void tc_pin_out_of_range( void ) __attribute__((error("Pin number is out of range.")));


/*=============================================================================
  pinMode
=============================================================================*/

static const uint8_t INPUT              = 0;
static const uint8_t OUTPUT             = 1;
static const uint8_t INPUT_PULLUP       = 2;

void pinModeF( uint8_t const pin, uint8_t const mode );

__attribute__((always_inline, unused)) static inline 
void pinMode( uint8_t const pin, uint8_t const mode )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( pin ) )
  {
    if ( pin < TC_NUMBER_OF(tc_inline_dio) )
    {
      if ( mode == OUTPUT )
      {
        if ( TC_SFR_IO_REG_P( tc_inline_dio[pin].ddr ) )
        {
          *tc_inline_dio[pin].ddr |= tc_inline_dio[pin].dio_bitmask;
        }
        else
        {
          TC_ATOMIC_OPTION
          {
            *tc_inline_dio[pin].ddr |= tc_inline_dio[pin].dio_bitmask;
          }
        }
      } 
      else if ( mode == INPUT_PULLUP ) 
      { 
        TC_ATOMIC_OPTION
        {
          *tc_inline_dio[pin].ddr &= ~ tc_inline_dio[pin].dio_bitmask;
          *tc_inline_dio[pin].port |= tc_inline_dio[pin].dio_bitmask;
        }
      }
      else 
      { 
        TC_ATOMIC_OPTION
        {
          *tc_inline_dio[pin].ddr &= ~ tc_inline_dio[pin].dio_bitmask;
          *tc_inline_dio[pin].port &= ~ tc_inline_dio[pin].dio_bitmask;
        }
      } 
    }
    else
    {
      tc_pin_out_of_range();
    }
  }
  else
  {
    pinModeF( pin, mode );
  }
}


/*=============================================================================
  digitalWrite and digitalRead
=============================================================================*/

static const uint8_t LOW                = 0;
static const uint8_t HIGH               = 1;

void digitalWriteF( uint8_t const pin, uint8_t const val );

__attribute__((always_inline, unused)) static inline 
void digitalWrite( uint8_t const pin, uint8_t const val )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( pin ) )
  {
    if ( pin < TC_NUMBER_OF(tc_inline_dio) )
    {
      #if MAKE_DIGITAL_IO_ATOMIC
        uint8_t SaveSREG;

        if ( ! TC_SFR_IO_REG_P( tc_inline_dio[pin].port ) || (DIGITAL_TURNS_OFF_PWM && tc_inline_dio[pin].pwm) )
        {
          SaveSREG = SREG;
          cli();
        }
      #endif

      #if DIGITAL_TURNS_OFF_PWM
        if ( tc_inline_dio[pin].pwm )
        {
          *tc_inline_dio[pin].pwm &= ~ tc_inline_dio[pin].pwm_channel;
        }
      #endif

      if ( val == LOW )
      {
        *tc_inline_dio[pin].port &= ~ tc_inline_dio[pin].dio_bitmask;
      }
      else
      {
        *tc_inline_dio[pin].port |= tc_inline_dio[pin].dio_bitmask;
      }

      #if MAKE_DIGITAL_IO_ATOMIC
        if ( ! TC_SFR_IO_REG_P( tc_inline_dio[pin].port ) || (DIGITAL_TURNS_OFF_PWM && tc_inline_dio[pin].pwm) )
        {
          SREG = SaveSREG;
        }
      #endif
    }
    else
    {
      tc_pin_out_of_range();
    }
  }
  else
  {
    digitalWriteF( pin, val );
  }
}


uint8_t digitalReadF( uint8_t const pin );

__attribute__((always_inline, unused)) static inline 
uint8_t digitalRead( uint8_t const pin )
{
  uint8_t rv;

  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( pin ) )
  {
    if ( pin < TC_NUMBER_OF(tc_inline_dio) )
    {
      #if MAKE_DIGITAL_IO_ATOMIC
        uint8_t SaveSREG;

        if ( ! TC_SFR_IO_REG_P( tc_inline_dio[pin].pin ) || (DIGITAL_TURNS_OFF_PWM && tc_inline_dio[pin].pwm) )
        {
          SaveSREG = SREG;
          cli();
        }
      #endif

      #if DIGITAL_TURNS_OFF_PWM
        if ( tc_inline_dio[pin].pwm )
        {
          *tc_inline_dio[pin].pwm &= ~ tc_inline_dio[pin].pwm_channel;
        }
      #endif

      #if USE_DIRTY_DIGITAL_READ
        rv = *tc_inline_dio[pin].pin & tc_inline_dio[pin].dio_bitmask;
      #else
        rv = (*tc_inline_dio[pin].pin & tc_inline_dio[pin].dio_bitmask) ? HIGH : LOW;
      #endif

      #if MAKE_DIGITAL_IO_ATOMIC
        if ( ! TC_SFR_IO_REG_P( tc_inline_dio[pin].pin ) || (DIGITAL_TURNS_OFF_PWM && tc_inline_dio[pin].pwm) )
        {
          SREG = SaveSREG;
        }
      #endif
    }
    else
    {
      tc_pin_out_of_range();
      rv = LOW;
    }
  }
  else
  {
    rv = digitalReadF( pin );
  }
  return( rv );
}


/*=============================================================================
  digitalPinHasPWM
=============================================================================*/

bool digitalPinHasPWMF( uint8_t const pin );

__attribute__((always_inline, unused)) static inline 
bool digitalPinHasPWM( uint8_t const pin )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( pin ) )
  {
    if ( pin < TC_NUMBER_OF(tc_inline_dio) )
    {
      return( tc_inline_dio[pin].pwm );
    }
    else
    {
      tc_pin_out_of_range();
    }
  }
  else
  {
    return( digitalPinHasPWMF( pin ) );
  }
}


/*=============================================================================
  A* constants
=============================================================================*/

#if TC_ANALOG_COUNT >= 1
  const uint8_t A0 = TC_DIGITAL_COUNT + 0;
#endif
#if TC_ANALOG_COUNT >= 2
  const uint8_t A1 = TC_DIGITAL_COUNT + 1;
#endif
#if TC_ANALOG_COUNT >= 3
  const uint8_t A2 = TC_DIGITAL_COUNT + 2;
#endif
#if TC_ANALOG_COUNT >= 4
  const uint8_t A3 = TC_DIGITAL_COUNT + 3;
#endif
#if TC_ANALOG_COUNT >= 5
  const uint8_t A4 = TC_DIGITAL_COUNT + 4;
#endif
#if TC_ANALOG_COUNT >= 6
  const uint8_t A5 = TC_DIGITAL_COUNT + 5;
#endif
#if TC_ANALOG_COUNT >= 7
  const uint8_t A6 = TC_DIGITAL_COUNT + 6;
#endif
#if TC_ANALOG_COUNT >= 8
  const uint8_t A7 = TC_DIGITAL_COUNT + 7;
#endif


/*=============================================================================
  analogReference
=============================================================================*/

#if TC_ANALOG_COUNT > 0

extern uint8_t tc_analog_reference;

__attribute__((always_inline, unused)) static inline 
void analogReference( uint8_t mode )
{
  tc_analog_reference = mode;
}

#else

__attribute__((always_inline, unused)) static inline 
void analogReference( uint8_t mode )
{
}

#endif


/*=============================================================================
  analogRead
=============================================================================*/

#if TC_ANALOG_COUNT > 0

#if TC_SLEEP_DURING_ADC
#include <avr/sleep.h>
#endif

const uint8_t CURRENTCHANNEL = 255;

#if TC_SLEEP_DURING_ADC
  #if TC_ENABLE_ADC_WHEN_NEEDED
    const uint8_t TC_ADCClocksPerConversion = 25;
  #else
    const uint8_t TC_ADCClocksPerConversion = 13;
  #endif
  const uint8_t TC_TCNTsPerConversion = ((TC_ADCClocksPerConversion+2) * tcADC::DIVISOR) / tcMillisTimer_Prescale_Value;
  const uint8_t TC_StartConversionThreshold = ( (uint8_t)(-1) ) - TC_TCNTsPerConversion;
#endif

int analogReadF( uint8_t pin );

__attribute__((always_inline, unused)) static inline 
int analogRead( uint8_t pin )
{
#if TC_INLINE_ANALOG_READ

  int rv;

  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( pin ) )
  {
    pin = (pin >= A0) ? (pin - A0) : (pin);

    if ( (pin < TC_ANALOG_COUNT) )
    {
      #if TC_ANALOG_READ_DISABLES_DIGITAL_READ
        if ( pin < TC_NUMBER_OF(tc_inline_adc) )
        {
          if ( tc_inline_adc[pin].didr )
          {
            *tc_inline_adc[pin].didr |= tc_inline_adc[pin].dio_bitmask;
          }
        }
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
    }
    else
    {
      tc_pin_out_of_range();
      rv = 0;
    }
  }
  else
  {
    rv = analogReadF( pin );
  }
  return( rv );

#else // TC_INLINE_ANALOG_READ

  return( analogReadF( pin ) );

#endif
}

#else

__attribute__((always_inline, unused)) static inline 
int analogRead( uint8_t pin )
{
  return( 0 );
}

#endif


/*=============================================================================
  interrupts - globally enable interrupts
=============================================================================*/

__attribute__((always_inline, unused)) static inline 
void interrupts( void ) 
{ 
  sei(); 
}


/*=============================================================================
  noInterrupts - globally disable interrupts
=============================================================================*/

__attribute__((always_inline, unused)) static inline 
void noInterrupts( void ) 
{ 
  cli();
}


/*=============================================================================
  Random number generation
=============================================================================*/

__attribute__((always_inline, unused)) static inline 
unsigned long tc_RandomGenerate_Libc( void ) 
{ 
  return( random() ); 
}

__attribute__((always_inline, unused)) static inline 
void tc_RandomSeed_Libc( unsigned long newseed )
{
  srandom( newseed );
}

unsigned long tc_RandomGenerate_XorShift( void );
void tc_RandomSeed_XorShift( unsigned long newseed );

unsigned long tc_RandomGenerate_XorShift16( void );
void tc_RandomSeed_XorShift16( unsigned long newseed );

unsigned long tc_RandomGenerate_CRC32( void );
void tc_RandomSeed_CRC32( unsigned long newseed );

unsigned long tc_RandomGenerate_JKISS32( void );
void tc_RandomSeed_JKISS32( unsigned long newseed );


__attribute__((always_inline, unused)) static inline 
unsigned long tc_RandomGenerate( void )
{
#if TC_RANDOM_FUNCTION_IS == TC_RANDOM_PARK_MILLER
  return( tc_RandomGenerate_Libc() );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_XORSHIFT
  return( tc_RandomGenerate_XorShift() );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_JKISS32
  return( tc_RandomGenerate_JKISS32() );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_CRC32
  return( tc_RandomGenerate_CRC32() );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_XORSHIFT_16
  return( tc_RandomGenerate_XorShift16() );
#endif
}

__attribute__((always_inline, unused)) static inline 
void tc_RandomSeed( unsigned long newseed )
{
#if TC_RANDOM_FUNCTION_IS == TC_RANDOM_PARK_MILLER
  tc_RandomSeed_Libc( newseed );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_XORSHIFT
  tc_RandomSeed_XorShift( newseed );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_JKISS32
  tc_RandomSeed_JKISS32( newseed );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_CRC32
  tc_RandomSeed_CRC32( newseed );
#elif TC_RANDOM_FUNCTION_IS == TC_RANDOM_XORSHIFT_16
  tc_RandomSeed_XorShift16( newseed );
#endif
}

int16_t randomF( int16_t range );
/*
int32_t randomF( int32_t range );

int16_t randomF( int16_t lo, int16_t hiMinusOne );
int32_t randomF( int32_t lo, int32_t hiMinusOne );
*/


__attribute__((always_inline, unused)) static inline 
uint32_t MaskForValueI4( uint32_t v )
{
  --v;

  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;

  return( v );
}

template <class T>
__attribute__((always_inline, unused)) static inline 
T randomIT( T range )
{
  T mask;
  T rv;

  if ( range <= 1 )
  {
    return( 0 );
  }

  mask = MaskForValueI4( range );

  do
  {
    rv = (T) (tc_RandomGenerate() & mask);
  }
  while ( rv >= range );

  return( rv );
}

__attribute__((always_inline, unused)) static inline 
int32_t randomI( int32_t range )
{
  if ( range >= 0 )
  {
    if ( range <= ((int32_t)UINT8_MAX) )
    {
      return( randomIT<uint8_t>( (uint8_t)(range) ) );
    }
    else if ( range <= ((int32_t)UINT16_MAX) )
    {
      return( randomIT<uint16_t>( (uint16_t)(range) ) );
    }
    else
    {
      return( randomIT<uint32_t>( (uint32_t)(range) ) );
    }
  }
  else
  {
    if ( range >= -((int32_t)UINT8_MAX) )
    {
      return( -randomIT<uint8_t>( (uint8_t)(-range) ) );
    }
    else if ( range >= -((int32_t)UINT16_MAX) )
    {
      return( -randomIT<uint16_t>( (uint16_t)(-range) ) );
    }
    else
    {
      return( -randomIT<uint32_t>( (uint32_t)(-range) ) );
    }
  }
}

__attribute__((always_inline, unused)) static inline 
int16_t random( int16_t range )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( range ) )
  {
    return( randomI( ((int32_t)range) ) );
  }
  else
  {
    return( randomF( range ) );
  }
}

/*
__attribute__((always_inline, unused)) static inline 
int32_t random( int32_t range )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( range ) )
  {
    return( randomI( ((int32_t)range) ) );
  }
  else
  {
    return( randomF( range ) );
  }
}


template <class T>
__attribute__((always_inline, unused)) static inline 
T random( T lo, T hiPlusOne )
{
  if ( MAKE_IT_REALLY_TINY && __builtin_constant_p( lo ) && __builtin_constant_p( hiPlusOne ) )
  {
    return( randomI( hiPlusOne - lo ) + lo );
  }
  else
  {
    return( randomF( lo, hiPlusOne ) );
  }
}

template <class TL, class TR>
__attribute__((always_inline, unused)) static inline 
int32_t random( TL lo, TR hiPlusOne )
{
  return( random( (int32_t) lo, (int32_t) hiPlusOne ) );
}


__attribute__((always_inline, unused)) static inline 
void randomSeed( unsigned long seed )
{
  tc_RandomSeed( seed );
}
*/


/*=============================================================================
  Time management
=============================================================================*/

/* fix
void tc_ticks_constant( void ) __attribute__((error("The parameter must be a compile-time constant.")));

#if TC_USE_TICKS_INSTEAD_OF_MILLIS

unsigned long ticks( void );
unsigned long tocks( void );

// fix? rmv? const unsigned long ms2ticksF( unsigned long milliseconds );
// fix? rmv? const unsigned long ms2tocksF( unsigned long milliseconds );

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2ticks( unsigned long milliseconds )
{
  static const unsigned long long Divisor = 8ull * 1000000ull;  // fix: MillisTimer_Prescale_Value * 1000000ull;

  if ( __builtin_constant_p( milliseconds ) )
  {
    return( (unsigned long) (((milliseconds * 1000ull * F_CPU) + (Divisor / 2)) / Divisor) );
  }
  else
  {
    tc_ticks_constant();
    // fix? rmv? return( ms2ticksF( milliseconds ) );
  }
}

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2tocks( unsigned long milliseconds )
{
  static const unsigned long long Divisor = 8ull * 1000000ull * 256ull;  // fix: MillisTimer_Prescale_Value * 1000000ull * 256ull;

  if ( __builtin_constant_p( milliseconds ) )
  {
    return( (unsigned long) (((milliseconds * 1000ull * F_CPU) + (Divisor / 2)) / Divisor) );
  }
  else
  {
    tc_ticks_constant();
    // fix? rmv? return( ms2tocksF( milliseconds ) );
  }
}

#else // TC_USE_TICKS_INSTEAD_OF_MILLIS
*/

#if TC_USE_16_BIT_FOR_MILLIS
  typedef unsigned short tc_millis_t;
#else
  typedef unsigned long tc_millis_t;
#endif

tc_millis_t millis( void );

/*

#if ! TC_NO_MICROS
tc_millis_t micros( void );

__attribute__((always_inline, unused, const)) static inline 
unsigned long ticks( void )
{
  return( micros() );
}
#endif

__attribute__((always_inline, unused, const)) static inline 
unsigned long tocks( void )
{
  return( millis() );
}

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2ticks( unsigned long milliseconds )
{
  return( milliseconds * 1000ul );
}

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2tocks( unsigned long milliseconds )
{
  return( milliseconds );
}

#endif
*/

#if TC_USE_WATCHDOG_FOR_MILLIS

void MillisViaWatchdog_Start( void );
void MillisViaWatchdog_Stop( void );

#endif // TC_USE_WATCHDOG_FOR_MILLIS


/*=============================================================================
  tone function
=============================================================================*/

#if defined( TC_TIMER_TO_USE_FOR_TONE )

void toneF( uint8_t pin, long frequency, unsigned long duration );

__attribute__((always_inline, unused)) static inline 
void tone( uint8_t pin, long frequency, unsigned long duration = 0 )
{
  if ( MAKE_IT_REALLY_TINY 
      && __builtin_constant_p( pin ) && __builtin_constant_p( frequency ) && __builtin_constant_p( duration )
      && (duration == 0) )
  {
    if ( pin < TC_NUMBER_OF(tc_inline_dio) )
    {
      if ( tcToneTimer::GetPWM() == tc_inline_dio[pin].pwm )
      {
        tcToneTimer::SetToneFrequency( frequency, tc_inline_dio[pin].pwm_channel );
        pinMode( pin, OUTPUT );
      }
      else
      {
        toneF( pin, frequency, duration );
      }
    }
    else
    {
      tc_pin_out_of_range();
    }
  }
  else
  {
    toneF( pin, frequency, duration );
  }
}

#endif


/*=============================================================================
  noTone function
=============================================================================*/

#if defined( TC_TIMER_TO_USE_FOR_TONE )

void noToneF( uint8_t pin );

__attribute__((always_inline, unused)) static inline 
void noTone( uint8_t pin = 255 )
{
  if ( MAKE_IT_REALLY_TINY 
      && __builtin_constant_p( pin ) )
  {
    tcToneTimer::ClockSelect( tcToneTimer::Stopped );
    tcToneTimer::SetCompareOutputModeA( tcToneTimer::Disconnected );
    tcToneTimer::SetCompareOutputModeB( tcToneTimer::Disconnected );
  }
  else
  {
    noToneF( pin );
  }
}

#endif


/*=============================================================================
  Called from main to bring the application to life.
=============================================================================*/

void init( void );


/*=============================================================================
  The two functions that must be provided by a sketch.
=============================================================================*/

void setup( void );
void loop( void );


#endif  // __cplusplus


#endif  // Arduino_h
