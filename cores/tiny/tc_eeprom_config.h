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

#ifndef tc_eeprom_config_h
#define tc_eeprom_config_h

#include <Arduino.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <inttypes.h>


const uint8_t TC_EEPROM_CONFIG_OSCCAL_BASE            = (E2END & 0xFF) -  0;  /* 1 byte; uint8_t */
const uint8_t TC_EEPROM_CONFIG_OSCCAL_DIV8            = (E2END & 0xFF) -  1;  /* 1 byte; uint8_t */
const uint8_t TC_EEPROM_CONFIG_OSCCAL_MUL2            = (E2END & 0xFF) -  2;  /* 1 byte; uint8_t */

const uint8_t TC_EEPROM_CONFIG_NUMERATOR_OSCILLATOR   = (E2END & 0xFF) -  4;  /* 2 bytes; uint16_t */
const uint8_t TC_EEPROM_CONFIG_NUMERATOR_WATCHDOG     = (E2END & 0xFF) -  6;  /* 2 bytes; uint16_t */
const uint8_t TC_EEPROM_CONFIG_NUMERATOR_CRYSTAL      = (E2END & 0xFF) -  8;  /* 2 bytes; uint16_t */

const uint8_t TC_EEPROM_CONFIG_PROCESSOR_ID           = (E2END & 0xFF) - 10;  /* 2 bytes; uint16_t */

const uint8_t TC_EEPROM_CONFIG_1V1_REFERENCE          = (E2END & 0xFF) - 11;  /* 1 bytes; uint8_t; 1000+eev=reference */


const uint16_t TC_EEPROM_CONFIG_OSCCAL_BASE_O           = (E2END -  0);
const uint16_t TC_EEPROM_CONFIG_OSCCAL_DIV8_O           = (E2END -  1);
const uint16_t TC_EEPROM_CONFIG_OSCCAL_MUL2_O           = (E2END -  2);

const uint16_t TC_EEPROM_CONFIG_NUMERATOR_OSCILLATOR_O  = (E2END -  4);
const uint16_t TC_EEPROM_CONFIG_NUMERATOR_WATCHDOG_O    = (E2END -  6);
const uint16_t TC_EEPROM_CONFIG_NUMERATOR_CRYSTAL_O     = (E2END -  8);

const uint16_t TC_EEPROM_CONFIG_PROCESSOR_ID_O          = (E2END - 10);

const uint16_t TC_EEPROM_CONFIG_1V1_REFERENCE_O         = (E2END - 11);


static uint8_t tcReadEepromConfig1( uint8_t AddressLow )
{
  EEARL = AddressLow;
  EECR = _BV(EERE);
  return( EEDR );
}

static uint16_t tcReadEepromConfig2( uint8_t AddressLow )
{
  union
  {
    uint8_t  b[2];
    uint16_t v;
  }
  rv;
 
  rv.b[0] = tcReadEepromConfig1(AddressLow+0);
  rv.b[1] = tcReadEepromConfig1(AddressLow+1);
 
  return( rv.v );
}

static uint16_t tcReadEepromConfig2( uint16_t Address )
{
  #if defined( EEARH )
    EEARH = (E2END >> 8) & 0xFF;
  #endif

  return( tcReadEepromConfig2( (uint8_t)(Address & 0xFF) ) );
}


static void tcWriteEepromConfig1( uint8_t AddressLow, uint8_t Value )
{
  // Set programming mode.  0 0 - 3.4 ms - Erase and Write in one operation (Atomic Operation)
  EECR = (0 << EEPM1) | (0 << EEPM0);
  // Set the address and value
  EEARL = AddressLow;
  EEDR = Value;
  // No interruptions
  ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
  {
    // Start the write
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
  }
  // Wait for the write to complete
  while( EECR & (1 << EEPE) );
}

static void tcWriteEepromConfig1( uint16_t Address, uint8_t Value )
{
  #if defined( EEARH )
    EEARH = (E2END >> 8) & 0xFF;
  #endif

  tcWriteEepromConfig1( (uint8_t)(Address & 0xFF), Value );
}

static void tcWriteEepromConfig2( uint8_t AddressLow, uint16_t Value )
{
  union
  {
    uint8_t  b[2];
    uint16_t v;
  }
  rv;
 
  rv.v = Value;

  tcWriteEepromConfig1( (uint8_t)(AddressLow+0), rv.b[0] );
  tcWriteEepromConfig1( (uint8_t)(AddressLow+1), rv.b[1] );
}

static void tcWriteEepromConfig2( uint16_t Address, uint16_t Value )
{
  #if defined( EEARH )
    EEARH = (E2END >> 8) & 0xFF;
  #endif

  tcWriteEepromConfig2( (uint8_t)(Address & 0xFF), Value );
}


#endif
