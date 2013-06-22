#include <Arduino.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
// fix #include <tc_millis_timer.h>
#include <tc_select_build_options.h>
#include <tc_timer_types.h>  // rmv


#if defined( TC_USE_TIMER_FOR_MILLIS )

/*----------------------------------------------------------------------------*/

#if (F_CPU == 9600000L) || (F_CPU == 1200000L)

#define MILLIS_INC  (1)

#define FRACT_INC  (53)
#define FRACT_MAX  (75)

typedef uint8_t tc_timer0_fract_t;

#elif (F_CPU == 16000000L) || (F_CPU == 8000000L) || (F_CPU == 4000000L) || (F_CPU == 2000000L) || (F_CPU == 1000000L)

#define MICROSECONDS_PER_MILLIS_OVERFLOW  (clockCyclesToMicroseconds(tcMillisTimer_Prescale_Value * 256))

#define MILLIS_INC  (MICROSECONDS_PER_MILLIS_OVERFLOW / 1000)

#define FRACT_INC  ((MICROSECONDS_PER_MILLIS_OVERFLOW % 1000) >> 3)
#define FRACT_MAX  (1000 >> 3)

typedef uint8_t tc_timer0_fract_t;

#else

/**
#define MILLIS_INC (1)

//#define FRACT_INC (22998)
//#define FRACT_INC (23004)
//#define FRACT_INC (23035)
//#define FRACT_INC (23017)
#define FRACT_INC (23083)
#define FRACT_MAX (32768)

typedef uint16_t tc_timer0_fract_t;
**/

#endif

/*----------------------------------------------------------------------------*/

#if ! TC_NO_MICROS
volatile tc_millis_t millis_timer_overflow_count;
#endif

volatile tc_millis_t millis_timer_millis;

static tc_timer0_fract_t millis_timer_fract;

/*----------------------------------------------------------------------------*/

ISR(MILLISTIMER_OVF_vect)
{
  tc_millis_t m = millis_timer_millis;
  tc_timer0_fract_t f = millis_timer_fract;

  f += FRACT_INC;

  if ( f >= FRACT_MAX ) 
  {
    f -= FRACT_MAX;
    m = m + MILLIS_INC + 1;
  }
  else
  {
    #if MILLIS_INC != 0
    m += MILLIS_INC;
    #endif
  }

  millis_timer_fract = f;
  millis_timer_millis = m;
#if ! TC_NO_MICROS
  millis_timer_overflow_count++;
#endif
}

/*----------------------------------------------------------------------------*/

tc_millis_t millis( void )
{
  tc_millis_t m;

  ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
  {
    m = millis_timer_millis;
  }

  return( m );
}

/*----------------------------------------------------------------------------*/

void tc_MillisViaTimer_ForceReference( void )
{
}

/*----------------------------------------------------------------------------*/

#endif // TC_USE_TIMER_FOR_MILLIS
