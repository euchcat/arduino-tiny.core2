#include <Arduino.h>
#include <tc_eeprom_config.h>

#include <avr/wdt.h>
#include <util/atomic.h>


#if TC_USE_WATCHDOG_FOR_MILLIS

/*----------------------------------------------------------------------------*/

#if defined( WDTIF )
  #define _WD_TIMEOUT_INTERRUPT_FLAG_BIT WDTIF
#elif defined( WDIF )
  #define _WD_TIMEOUT_INTERRUPT_FLAG_BIT WDIF
#endif

#if defined( WDTIE )
  #define _WD_TIMEOUT_INTERRUPT_ENABLE_BIT WDTIE
#elif defined( WDIE )
  #define _WD_TIMEOUT_INTERRUPT_ENABLE_BIT WDIE
#endif

/*----------------------------------------------------------------------------*/

/* 
  For the ATtiny13A...

    Frequency is estimated to be 110241 Hertz at 5 volts and 25 °C (77 °F)
    1000/(110241/2048)*256 = 4755.83494344  (18.577480248 ms)

    Frequency is estimated to be 110579 Hertz at 5 volts and 20 °C (68 °F)
    1000/(110579/2048)*256 = 4741.29807649  (18.520695611 ms)
*/

static volatile tc_millis_t     millis_timer_millis;
static          unsigned short  millis_timer_accumulator;
static          unsigned short  millis_timer_increment = 4741;

/*----------------------------------------------------------------------------*/

ISR( WDT_vect )
{
/* 
  unsigned short A;
  
  A = millis_timer_accumulator + 4852; // 4857; // 
  millis_timer_millis = millis_timer_millis + (A >> 8);
  millis_timer_accumulator = A & 0x00FF;
*/
/* */
  unsigned short A;
  
  A = millis_timer_accumulator + millis_timer_increment;
  millis_timer_millis = millis_timer_millis + (A >> 8);
  millis_timer_accumulator = A & 0x00FF;
/* */
}

/*----------------------------------------------------------------------------*/

tc_millis_t millis()
{
  unsigned long m;
  
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    m = millis_timer_millis;
  }

  return m;
}

/*----------------------------------------------------------------------------*/

void MillisViaWatchdog_Start( void )
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    wdt_reset();
    
    // Clear WDRF in MCUSR
    MCUSR &= ~(1<<WDRF);

    // Start timed sequence
    _WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);

    // Configure the watchdog to generate an interrupt roughly every 16 ms
    _WD_CONTROL_REG = 
        (1 << _WD_TIMEOUT_INTERRUPT_FLAG_BIT) | 
        (1 << _WD_TIMEOUT_INTERRUPT_ENABLE_BIT) | 
        (0 << _WD_CHANGE_BIT) |
        (0 << WDE) |
        (0 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
  }
}

/*----------------------------------------------------------------------------*/

void MillisViaWatchdog_Stop( void )
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    wdt_reset();

    // Clear WDRF in MCUSR
    MCUSR &= ~(1<<WDRF);

    // Start timed sequence
    _WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);

    // Stop the watchdog
    _WD_CONTROL_REG = 
        (1 << _WD_TIMEOUT_INTERRUPT_FLAG_BIT) | 
        (0 << _WD_TIMEOUT_INTERRUPT_ENABLE_BIT) | 
        (0 << _WD_CHANGE_BIT) |
        (0 << WDE) |
        (0 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
  }
}

/*----------------------------------------------------------------------------*/

void tc_MillisViaWatchdog_Init( void )
{
//millis_timer_increment = 4852;
//millis_timer_increment = 4760;

//millis_timer_increment = 4267;
  //millis_timer_increment = 4275;

  uint16_t Numerator;
  Numerator = tcReadEepromConfig2( TC_EEPROM_CONFIG_NUMERATOR_WATCHDOG );
  if ( Numerator != 0xFFFF )
  {
    millis_timer_increment = Numerator;
  }

  MillisViaWatchdog_Start();
}

/*----------------------------------------------------------------------------*/

#endif // TC_USE_WATCHDOG_FOR_MILLIS
