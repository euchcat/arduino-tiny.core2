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

#ifndef tc_hardware_mapping_t84_h
#define tc_hardware_mapping_t84_h

#include <tc_select_processor.h>


/*=============================================================================
  Hardware definitions for the ATtiny84 family
=============================================================================*/

#if defined( __AVR_ATtinyX4__ )

#define TC_PWM_0        TCCR0A, COM0A
#define TC_PWM_1        TCCR0A, COM0B
#define TC_PWM_2        TCCR1A, COM1A
#define TC_PWM_3        TCCR1A, COM1B

#define TC_PWM_COUNT          (4)

#define TC_B0           B, 0, TC_NO_PWM, TC_NO_DIDR
#define TC_B1           B, 1, TC_NO_PWM, TC_NO_DIDR
#define TC_B2           B, 2, 0,         TC_NO_DIDR
#define TC_A7           A, 7, 1,         0
#define TC_A6           A, 6, 2,         0
#define TC_A5           A, 5, 3,         0
#define TC_A4           A, 4, TC_NO_PWM, 0
#define TC_A3           A, 3, TC_NO_PWM, 0
#define TC_A2           A, 2, TC_NO_PWM, 0
#define TC_A1           A, 1, TC_NO_PWM, 0
#define TC_A0           A, 0, TC_NO_PWM, 0
#define TC_B3           B, 3, TC_NO_PWM, TC_NO_DIDR

#define TC_PIN_0        TC_B0
#define TC_PIN_1        TC_B1
#define TC_PIN_2        TC_B2
#define TC_PIN_3        TC_A7
#define TC_PIN_4        TC_A6
#define TC_PIN_5        TC_A5
#define TC_PIN_6        TC_A4
#define TC_PIN_7        TC_A3
#define TC_PIN_8        TC_A2
#define TC_PIN_9        TC_A1
#define TC_PIN_10       TC_A0
#define TC_PIN_11       TC_B3

#define TC_PIN_12       TC_A0
#define TC_PIN_13       TC_A1
#define TC_PIN_14       TC_A2
#define TC_PIN_15       TC_A3
#define TC_PIN_16       TC_A4
#define TC_PIN_17       TC_A5
#define TC_PIN_18       TC_A6
#define TC_PIN_19       TC_A7

#define TC_DEFAULT_DIGITAL_MAPPING  (1)

#define TC_DIGITAL_COUNT      (12)

#define TC_RESET_INCLUDED     (1)

#define TC_ANALOG_COUNT       (8)

#define TC_TIMER_COUNT        (2)

#define TC_TIMER_0_IS_GENERIC_8_BIT   (1)
#define TC_TIMER_1_IS_GENERIC_16_BIT  (1)

#include <tc_adc_types.h>

class tcADC : public tcADCBase
{
public:

  typedef enum
  {
    Reference_VCC           = 0b00,
    Reference_External      = 0b01,
    Reference_Internal_1p1  = 0b10,
    Reference_Reserved_1    = 0b11
  }
  adc_vr_t;

  __attribute__((always_inline)) static inline 
  void SetVoltageReference( adc_vr_t vr )
  {
    ADMUX = (ADMUX & ~MASK2(REFS1,REFS0)) | (((vr & 0b11) >> 0) << REFS0);
  }

  typedef enum
  {
    Input_ADC0            = 0b000000,
    Input_ADC1            = 0b000001,
    Input_ADC2            = 0b000010,
    Input_ADC3            = 0b000011,
    Input_ADC4            = 0b000100,
    Input_ADC5            = 0b000101,
    Input_ADC6            = 0b000110,
    Input_ADC7            = 0b000111,

    Input_GND             = 0b100000,  // 0V (AGND)
    Input_1p1             = 0b100001,  // 1.1V (I Ref)
    Input_ADC8            = 0b100010,  // For temperature sensor.

    Input_Pos0_Neg0_20x   = 0b100011,  // For offset calibration, only.
    Input_Pos0_Neg1_1x    = 0b001000,
    Input_Pos0_Neg1_20x   = 0b001001,
    Input_Pos0_Neg3_1x    = 0b001010,
    Input_Pos0_Neg3_20x   = 0b001011,
    Input_Pos1_Neg0_1x    = 0b101000,
    Input_Pos1_Neg0_20x   = 0b101001,
    Input_Pos1_Neg2_1x    = 0b001100,
    Input_Pos1_Neg2_20x   = 0b001101,
    Input_Pos1_Neg3_1x    = 0b001110,
    Input_Pos1_Neg3_20x   = 0b001111,
    Input_Pos2_Neg1_1x    = 0b101100,
    Input_Pos2_Neg1_20x   = 0b101101,
    Input_Pos2_Neg3_1x    = 0b010000,
    Input_Pos2_Neg3_20x   = 0b010001,
    Input_Pos3_Neg0_1x    = 0b101010,
    Input_Pos3_Neg0_20x   = 0b101011,
    Input_Pos3_Neg1_1x    = 0b101110,
    Input_Pos3_Neg1_20x   = 0b101111,
    Input_Pos3_Neg2_1x    = 0b110000,
    Input_Pos3_Neg2_20x   = 0b110001,
    Input_Pos3_Neg3_1x    = 0b100100,  // For offset calibration, only.
    Input_Pos3_Neg3_20x   = 0b100101,  // For offset calibration, only.
    Input_Pos3_Neg4_1x    = 0b010010,
    Input_Pos3_Neg4_20x   = 0b010011,
    Input_Pos3_Neg5_1x    = 0b010100,
    Input_Pos3_Neg5_20x   = 0b010101,
    Input_Pos3_Neg6_1x    = 0b010110,
    Input_Pos3_Neg6_20x   = 0b010111,
    Input_Pos3_Neg7_1x    = 0b011000,
    Input_Pos3_Neg7_20x   = 0b011001,
    Input_Pos4_Neg3_1x    = 0b110010,
    Input_Pos4_Neg3_20x   = 0b110011,
    Input_Pos4_Neg5_1x    = 0b011010,
    Input_Pos4_Neg5_20x   = 0b011011,
    Input_Pos5_Neg3_1x    = 0b110100,
    Input_Pos5_Neg3_20x   = 0b110101,
    Input_Pos5_Neg4_1x    = 0b111010,
    Input_Pos5_Neg4_20x   = 0b111011,
    Input_Pos5_Neg6_1x    = 0b011100,
    Input_Pos5_Neg6_20x   = 0b011101,
    Input_Pos6_Neg3_1x    = 0b110110,
    Input_Pos6_Neg3_20x   = 0b110111,
    Input_Pos6_Neg5_1x    = 0b111100,
    Input_Pos6_Neg5_20x   = 0b111101,
    Input_Pos6_Neg7_1x    = 0b011110,
    Input_Pos6_Neg7_20x   = 0b011111,
    Input_Pos7_Neg3_1x    = 0b111000,
    Input_Pos7_Neg3_20x   = 0b111001,
    Input_Pos7_Neg6_1x    = 0b111110,
    Input_Pos7_Neg6_20x   = 0b111111,
    Input_Pos7_Neg7_1x    = 0b100110,  // For offset calibration, only.
    Input_Pos7_Neg7_20x   = 0b100111   // For offset calibration, only.
  }
  adc_ic_t;

  __attribute__((always_inline)) static inline 
  void SetInputChannel( adc_ic_t ic )
  {
    ADMUX = (ADMUX & ~MASK6(MUX5,MUX4,MUX3,MUX2,MUX1,MUX0)) | (ic << MUX0);
  }

};

const uint8_t DEFAULT       = tcADC::Reference_VCC;
const uint8_t INTERNAL      = tcADC::Reference_Internal_1p1;
const uint8_t INTERNAL1V1   = tcADC::Reference_Internal_1p1;
const uint8_t EXTERNAL      = tcADC::Reference_External;

#endif


#endif  // tc_hardware_mapping_t84
