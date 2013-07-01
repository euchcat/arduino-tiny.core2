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

#ifndef tc_hardware_mapping_t861_h
#define tc_hardware_mapping_t861_h

#include <tc_select_processor.h>


/*=============================================================================
  Hardware definitions for the ATtiny861
=============================================================================*/

#if defined( __AVR_ATtinyX61__ )

#define TC_A0           A, 0, TC_NO_PWM, 0
#define TC_A1           A, 1, TC_NO_PWM, 0
#define TC_A2           A, 2, TC_NO_PWM, 0
#define TC_A3           A, 3, TC_NO_PWM, 0
#define TC_A4           A, 4, TC_NO_PWM, 0
#define TC_A5           A, 5, TC_NO_PWM, 0
#define TC_A6           A, 6, TC_NO_PWM, 0
#define TC_A7           A, 7, TC_NO_PWM, 0
#define TC_B0           B, 0, TC_NO_PWM, TC_NO_DIDR
#define TC_B1           B, 1, TC_NO_PWM, TC_NO_DIDR
#define TC_B2           B, 2, TC_NO_PWM, TC_NO_DIDR
#define TC_B3           B, 3, TC_NO_PWM, TC_NO_DIDR
#define TC_B4           B, 4, TC_NO_PWM, 1
#define TC_B5           B, 5, TC_NO_PWM, 1
#define TC_B6           B, 6, TC_NO_PWM, 1
#define TC_B7           B, 7, TC_NO_PWM, 1

#define TC_PIN_0        TC_A0
#define TC_PIN_1        TC_A1
#define TC_PIN_2        TC_A2
#define TC_PIN_3        TC_A3
#define TC_PIN_4        TC_A4
#define TC_PIN_5        TC_A5
#define TC_PIN_6        TC_A6
#define TC_PIN_7        TC_A7
#define TC_PIN_8        TC_B0
#define TC_PIN_9        TC_B1
#define TC_PIN_10       TC_B2
#define TC_PIN_11       TC_B3
#define TC_PIN_12       TC_B4
#define TC_PIN_13       TC_B5
#define TC_PIN_14       TC_B6
#define TC_PIN_15       TC_B7

#define TC_PIN_16       TC_A0
#define TC_PIN_17       TC_A1
#define TC_PIN_18       TC_A2
#define TC_PIN_19       TC_A4
#define TC_PIN_20       TC_A5
#define TC_PIN_21       TC_A6
#define TC_PIN_22       TC_A7
#define TC_PIN_23       TC_B4
#define TC_PIN_24       TC_B5
#define TC_PIN_25       TC_B6
#define TC_PIN_26       TC_B7

#define TC_DEFAULT_DIGITAL_MAPPING  (1)

#define TC_DIGITAL_COUNT      (16)

#define TC_RESET_INCLUDED     (1)

#define TC_BASE_PORT      B
#define TC_BASE_REGISTER  PIN

#define TC_ADC_0        TC_A0
#define TC_ADC_1        TC_A1
#define TC_ADC_2        TC_A2
#define TC_ADC_3        TC_A4
#define TC_ADC_4        TC_A5
#define TC_ADC_5        TC_A6
#define TC_ADC_6        TC_A7
#define TC_ADC_7        TC_B4
#define TC_ADC_8        TC_B5
#define TC_ADC_9        TC_B6
#define TC_ADC_10       TC_B7

#define TC_ANALOG_COUNT       (11)

#define TC_TIMER_COUNT        (2)

#define TC_XTAL2        TC_B5

#include <tc_adc_types.h>

class tcADC : public tcADCBase
{
public:

  typedef enum
  {
    Reference_VCC           = 0b000,
    Reference_External      = 0b001,
    Reference_Internal_1p1  = 0b010,
    Reference_Reserved_1    = 0b011,
    Reference_Internal_2p56 = 0b110,
    Reference_Internal_2p56_Bypass_Capacitor  = 0b111
  }
  adc_vr_t;

  __attribute__((always_inline)) static inline 
  void SetVoltageReference( adc_vr_t vr )
  {
    ADMUX = (ADMUX & ~MASK2(REFS1,REFS0)) | (uint8_t)(((vr & 0b011) >> 0) << REFS0);
    ADCSRB = (ADCSRB & ~MASK1(REFS2)) | (uint8_t)(((vr & 0b100) >> 2) << REFS2);
  }

  typedef enum
  {
    Input_ADC0              = 0b000000,
    Input_ADC1              = 0b000001,
    Input_ADC2              = 0b000010,
    Input_ADC3              = 0b000011,
    Input_ADC4              = 0b000100,
    Input_ADC5              = 0b000101,
    Input_ADC6              = 0b000110,
    Input_ADC7              = 0b000111,
    Input_ADC8              = 0b001000,
    Input_ADC9              = 0b001001,
    Input_ADC10             = 0b001010,

    Input_Pos0_Neg1_20x     = 0b001011,
    Input_Pos0_Neg1_1x      = 0b001100,
    Input_Pos1_Neg1_20x     = 0b001101,
    Input_Pos2_Neg1_20x     = 0b001110,
    Input_Pos2_Neg1_1x      = 0b001111,
    Input_Pos2_Neg3_1x      = 0b010000,
    Input_Pos3_Neg3_20x     = 0b010001,
    Input_Pos4_Neg3_20x     = 0b010010,
    Input_Pos4_Neg3_1x      = 0b010011,
    Input_Pos4_Neg5_20x     = 0b010100,
    Input_Pos4_Neg5_1x      = 0b010101,
    Input_Pos5_Neg5_20x     = 0b010110,
    Input_Pos6_Neg5_20x     = 0b010111,
    Input_Pos6_Neg5_1x      = 0b011000,
    Input_Pos8_Neg9_20x     = 0b011001,
    Input_Pos8_Neg9_1x      = 0b011010,
    Input_Pos9_Neg9_20x     = 0b011011,
    Input_Pos10_Neg9_20x    = 0b011100,
    Input_Pos10_Neg9_1x     = 0b011101,

    Input_1p1               = 0b011110,  // 1.1V (I Ref)
    Input_GND               = 0b011111,  // 0V (AGND)

    Input_Pos0_Neg1_20x_32x = 0b100000,
    Input_Pos0_Neg1_1x_8x   = 0b100001,
    Input_Pos1_Neg0_20x_32x = 0b100010,
    Input_Pos1_Neg0_1x_8x   = 0b100011,
    Input_Pos1_Neg2_20x_32x = 0b100100,
    Input_Pos1_Neg2_1x_8x   = 0b100101,
    Input_Pos2_Neg1_20x_32x = 0b100110,
    Input_Pos2_Neg1_1x_8x   = 0b100111,
    Input_Pos2_Neg0_20x_32x = 0b101000,
    Input_Pos2_Neg0_1x_8x   = 0b101001,
    Input_Pos0_Neg2_20x_32x = 0b101010,
    Input_Pos0_Neg2_1x_8x   = 0b101011,
    Input_Pos4_Neg5_20x_32x = 0b101100,
    Input_Pos4_Neg5_1x_8x   = 0b101101,
    Input_Pos5_Neg4_20x_32x = 0b101110,
    Input_Pos5_Neg4_1x_8x   = 0b101111,
    Input_Pos5_Neg6_20x_32x = 0b110000,
    Input_Pos5_Neg6_1x_8x   = 0b110001,
    Input_Pos6_Neg5_20x_32x = 0b110010,
    Input_Pos6_Neg5_1x_8x   = 0b110011,
    Input_Pos6_Neg4_20x_32x = 0b110100,
    Input_Pos6_Neg4_1x_8x   = 0b110101,
    Input_Pos4_Neg6_20x_32x = 0b110110,
    Input_Pos4_Neg6_1x_8x   = 0b110111,
    Input_Pos0_Neg0_20x_32x = 0b111000,
    Input_Pos0_Neg0_1x_8x   = 0b111001,
    Input_Pos1_Neg1_20x_32x = 0b111010,
    Input_Pos2_Neg2_20x_32x = 0b111011,
    Input_Pos4_Neg4_20x_32x = 0b111100,
    Input_Pos5_Neg5_20x_32x = 0b111101,
    Input_Pos6_Neg6_20x_32x = 0b111110,

    Input_ADC11             = 0b111111   // For temperature sensor.
  }
  adc_ic_t;

  __attribute__((always_inline)) static inline 
  void SetInputChannel( adc_ic_t ic )
  {
    ADMUX = (ADMUX & ~MASK5(MUX4,MUX3,MUX2,MUX1,MUX0)) | (uint8_t)(((ic & 0b011111) >> 0) << MUX0);
    ADCSRB = (ADCSRB & ~MASK1(MUX5)) | (uint8_t)(((ic & 0b100000) >> 5) << MUX5);
  }

};

const uint8_t DEFAULT       = tcADC::Reference_VCC;
const uint8_t INTERNAL      = tcADC::Reference_Internal_1p1;
const uint8_t INTERNAL1V1   = tcADC::Reference_Internal_1p1;
const uint8_t EXTERNAL      = tcADC::Reference_External;
const uint8_t INTERNAL2V56  = tcADC::Reference_Internal_2p56_Bypass_Capacitor;

#define TC_HAVE_GENERIC_TIMER  (1)
#include <tc_timer_types.h>

#ifndef CTC0
#define CTC0  0
#endif

// rmv static const uint8_t TC_CTC0_8B   = CTC0;
// rmv static const uint8_t TC_CS2_8B    = CS02;
// rmv static const uint8_t TC_CS1_8B    = CS01;
// rmv static const uint8_t TC_CS0_8B    = CS00;
// rmv static const uint8_t TC_OCIEA_8B  = OCIE0A;
// rmv static const uint8_t TC_OCIEB_8B  = OCIE0B;
// rmv static const uint8_t TC_TOIE_8B   = TOIE0;
// rmv static const uint8_t TC_TICIE0_8B = TICIE0;

static const tc_timer_register_set_generic_8b_t tc_timer0_register_set[] = 
  {
    { &TCCR0A, &TCCR0B, &TCNT0L, &OCR0A, &OCR0B, &TIMSK, &TIFR }
  };

template <unsigned trsi>
class tcTimerInterface861_0 : public tcTimerInterfaceGenericTypes
{
public:

  enum { index = trsi };

/*
  __attribute__((always_inline)) static inline 
  uint8_t volatile * const GetPWM( void )
  {
    return( tc_timer0_register_set[index].pTCCRA );
  }

  __attribute__((always_inline)) static inline 
  void SetToPowerup( void )
  {
    // Stop the clock, set waveform generation to normal, and set output mode to normal
    *tc_timer0_register_set[index].pTCCRB = (0<<TC_FOCA_8B) | (0<<TC_FOCB_8B) | (0<<TC_WGM2_8B) | (0<<CS02) | (0<<CS01) | (0<<CS00);
    *tc_timer0_register_set[index].pTCCRA = (0<<TC_COMA1_8B) | (0<<TC_COMA0_8B) | (0<<TC_COMB1_8B) | (0<<TC_COMB0_8B) | (0<<TC_WGM1_8B) | (0<<TC_WGM0_8B);
    // Reset the count to zero
    *tc_timer0_register_set[index].pTCNT = 0;
    // Set the output compare registers to zero
    *tc_timer0_register_set[index].pOCRA = 0;
    *tc_timer0_register_set[index].pOCRB = 0;
    // Disable all interrupts
    *tc_timer0_register_set[index].pTIMSK &= ~ MASK3( OCIE0A, OCIE0B, TOIE0 );
    // Clear the interrupt flags
    *tc_timer0_register_set[index].pTIFR |= MASK3( TC_OCFA_8B, TC_OCFB_8B, TC_TOV_8B );
  }

  __attribute__((always_inline)) static inline 
  void InterruptsOff( void )
  {
    *tc_timer0_register_set[index].pTIMSK &= ~ MASK3( OCIE0A, OCIE0B, TOIE0 );
  }

  __attribute__((always_inline)) static inline 
  void ClockSelect( cs_t cs )
  {
    *tc_timer0_register_set[index].pTCCRB = 
        (*tc_timer0_register_set[index].pTCCRB & ~ MASK3( CS02, CS01, CS00 )) 
        | (cs << CS00);
  }
*/

  typedef enum
  {
    Normal                     = 0b0,
    CTC_OCR                    = 0b1,
    Fast_PWM_FF                = 0b0  // Timer does not support PWM; symbol only included to appease other code
  }
  wgm_t;

/*
  __attribute__((always_inline)) static inline 
  void SetWaveformGenerationMode( wgm_t wgm )
  {
    *tc_timer0_register_set[index].pTCCRA = 
        (*tc_timer0_register_set[index].pTCCRA & ~ MASK2( TC_WGM1_8B, TC_WGM0_8B )) 
        | (((wgm & 0b011) >> 0) << TC_WGM0_8B);

    *tc_timer0_register_set[index].pTCCRB = 
        (*tc_timer0_register_set[index].pTCCRB & ~ MASK1( TC_WGM2_8B ))
        | (((wgm & 0b100) >> 2) << TC_WGM2_8B);
  }

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeA( com_t com )
  {
    *tc_timer0_register_set[index].pTCCRA = 
        (*tc_timer0_register_set[index].pTCCRA & ~ MASK2( TC_COMA1_8B, TC_COMA0_8B )) 
        | (com << TC_COMA0_8B);
  }

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeB( com_t com )
  {
    *tc_timer0_register_set[index].pTCCRA = 
        (*tc_timer0_register_set[index].pTCCRA & ~ MASK2( TC_COMB1_8B, TC_COMB0_8B )) 
        | (com << TC_COMB0_8B);
  }

  __attribute__((always_inline)) static inline 
  void DisconnectOutputs( void )
  {
    *tc_timer0_register_set[index].pTCCRA &= ~ MASK4( TC_COMA1_8B, TC_COMA0_8B, TC_COMB1_8B, TC_COMB0_8B );
  }

  static const unsigned MAXIMUM_OCR = (255);
//rmv  static const uint8_t PRESCALE_SET = (1);

  typedef uint8_t ocr_t;
  typedef uint8_t tcnt_t;

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchAndClear( ocr_t oc )
  {
    *tc_timer0_register_set[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchA( ocr_t oc )
  {
    *tc_timer0_register_set[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchB( ocr_t oc )
  {
    *tc_timer0_register_set[index].pOCRB = oc;
  }

  __attribute__((always_inline)) static inline 
  void EnableOutputCompareInterruptA( void )
  {
    *tc_timer0_register_set[index].pTIMSK |= (1 << OCIE0A);
  }

  __attribute__((always_inline)) static inline 
  void EnableOverflowInterrupt( void )
  {
    *tc_timer0_register_set[index].pTIMSK |= (1 << TOIE0);
  } 

  __attribute__((always_inline)) static inline 
  tcnt_t GetCount( void )
  {
    return( *tc_timer0_register_set[index].pTCNT );
  }

  __attribute__((always_inline)) static inline 
  void SetCount( tcnt_t v )
  {
    *tc_timer0_register_set[index].pTCNT = v;
  }

  __attribute__((always_inline)) static inline 
  bool IsOverflowSet( void )
  {
    return( (*tc_timer0_register_set[index].pTIFR & (1 << TC_TOV_8B)) != 0 );
  }
*/

  __attribute__((always_inline)) static inline 
  void CoreInitializeHelper( wgm_t wgm, cs_t cs )
  {
    *tc_timer0_register_set[index].pTCCRA = (((wgm & 0b1) >> 0) << CTC0);
    *tc_timer0_register_set[index].pTCCRB = (((cs & 0b111) >> 0) << CS00);
  }

  __attribute__((always_inline)) static inline 
  void CoreInitialize( bool primary, cs_t cs, bool favorphasecorrect )
  {
    if ( primary )
    {
      CoreInitializeHelper( Normal, cs );
      *tc_timer0_register_set[index].pTIMSK = (1 << TOIE0);
    }
    else
    {
      if ( favorphasecorrect )
      {
        CoreInitializeHelper( Normal, cs );
      }
      else
      {
        CoreInitializeHelper( Normal, cs );
      }
    }
  }

/* rmv
  __attribute__((always_inline)) static inline 
  void CoreInitialize( wgm_t wgm, cs_t cs, bool ei )
  {
    *tc_timer0_register_set[index].pTCCRA = (((wgm & 0b1) >> 0) << CTC0);

    *tc_timer0_register_set[index].pTCCRB = (((cs & 0b111) >> 0) << CS00);

    if ( ei )
    {
      *tc_timer0_register_set[index].pTIMSK = (1 << TOIE0);
    }
  }
*/

/*
  __attribute__((always_inline)) static inline 
  void SetToneFrequency( long frequency, uint8_t channel )
  {
    uint8_t   cs;
    uint16_t  ps;
    uint8_t   ocr;

    GetToneCutoff( frequency, cs, ps ); 

    *tc_timer0_register_set[index].pTCCRB = 
        (0 << TC_FOCA_8B) | (0 << TC_FOCB_8B) | 
        (0 << TC_WGM2_8B) | 
        (0 << CS02) | (0 << CS01) | (0 << CS00);

    *tc_timer0_register_set[index].pTCNT = 0;

    *tc_timer0_register_set[index].pTCCRA = 
        (channel & ((Toggle << TC_COMA0_8B) | (Toggle << TC_COMB0_8B))) |
        (1 << TC_WGM1_8B) | (0 << TC_WGM0_8B);

    ocr = ( (2L * F_CPU) / (frequency * 2L * ps) + 1L ) / 2L - 1L;
    
    *tc_timer0_register_set[index].pOCRA = ocr;
    *tc_timer0_register_set[index].pOCRB = ocr;

    *tc_timer0_register_set[index].pTCCRB = 
        (0 << TC_FOCA_8B) | (0 << TC_FOCB_8B) | 
        (0 << TC_WGM2_8B) | 
        cs;
  }
*/

};

typedef tcTimerInterface861_0<0> tcTimerInterface0;

#if defined(TIMER0_OVF_vect) && ! defined(TIM0_OVF_vect)
#define TIM0_OVF_vect TIMER0_OVF_vect
#endif

class tcTimerInterface861_1
{
public:

  typedef enum
  {
    Stopped               = 0b0000,
    Prescale_Value_1      = 0b0001,
    Prescale_Value_2      = 0b0010,
    Prescale_Value_4      = 0b0011,
    Prescale_Value_8      = 0b0100,
    Prescale_Value_16     = 0b0101,
    Prescale_Value_32     = 0b0110,
    Prescale_Value_64     = 0b0111,
    Prescale_Value_128    = 0b1000,
    Prescale_Value_256    = 0b1001,
    Prescale_Value_512    = 0b1010,
    Prescale_Value_1024   = 0b1011,
    Prescale_Value_2048   = 0b1100,
    Prescale_Value_4096   = 0b1101,
    Prescale_Value_8192   = 0b1110,
    Prescale_Value_16384  = 0b1111,
    Prescale_Index_1      = 0b0001,
    Prescale_Index_2      = 0b0010,
    Prescale_Index_3      = 0b0011,
    Prescale_Index_4      = 0b0100,
    Prescale_Index_5      = 0b0101,
    Prescale_Index_6      = 0b0110,
    Prescale_Index_7      = 0b0111,
    Prescale_Index_8      = 0b1000,
    Prescale_Index_9      = 0b1001,
    Prescale_Index_10     = 0b1010,
    Prescale_Index_11     = 0b1011,
    Prescale_Index_12     = 0b1100,
    Prescale_Index_13     = 0b1101,
    Prescale_Index_14     = 0b1110,
    Prescale_Index_15     = 0b1111
  }
  cs_t;

  typedef enum
  {
    Normal                      = 0b000,
    Fast_PWM_OCR                = 0b100,
    Phase_Frequency_PWM_OCR     = 0b101,
    PWM6_Single_slope_PWM_OCR   = 0b110,
    PWM6_Dua_slope_PWM_OCR      = 0b111
  }
  wgm_t;

  __attribute__((always_inline)) static inline 
  void CoreInitializeHelper( wgm_t wgm, cs_t cs )
  {
    TCCR1D = (((wgm & 0b011) >> 0) << WGM10);
    TCCR1B = (((cs & 0b1111) >> 0) << CS10);
    if ( wgm == Normal )
    {
      TCCR1A = 0;
      TCCR1C = 0;
    }
    else
    {
      TCCR1A = (1 << PWM1A) | (1 << PWM1B);
      TCCR1C = (1 << PWM1D);
    }
/* fix
TCCR1A
COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B PWM1A PWM1B
TCCR1B
PWM1X PSR1 DTPS11 DTPS10 CS13 CS12 CS11 CS10
TCCR1C
COM1A1S COM1A0S COM1B1S COM1B0S COM1D1 COM1D0 FOC1D PWM1D
TCCR1D
FPIE1 FPEN1 FPNC1 FPES1 FPAC1 FPF1 WGM11 WGM10

    *tc_timer_register_set_generic_8b[index].pTCCRA = (((wgm & 0b011) >> 0) << TC_WGM0_8B);
    *tc_timer_register_set_generic_8b[index].pTCCRB = (((wgm & 0b100) >> 2) << TC_WGM2_8B) | (cs << TC_CS0_8B);
*/
  }

  __attribute__((always_inline)) static inline 
  void CoreInitialize( bool primary, cs_t cs, bool favorphasecorrect )
  {
    OCR1C = 0xFF;

    if ( primary )
    {
      CoreInitializeHelper( Fast_PWM_OCR, cs );
      TIMSK |= (1 << TOIE1);
    }
    else
    {
      if ( favorphasecorrect )
      {
        CoreInitializeHelper( Phase_Frequency_PWM_OCR, cs );
      }
      else
      {
        CoreInitializeHelper( Fast_PWM_OCR, cs );
      }
    }
/*
    *tc_timer0_register_set[index].pTCCRA = (((wgm & 0b1) >> 0) << CTC0);

    *tc_timer0_register_set[index].pTCCRB = (((cs & 0b111) >> 0) << CS00);

    if ( ei )
    {
      *tc_timer0_register_set[index].pTIMSK = (1 << TOIE0);
    }
*/
  }

};

typedef tcTimerInterface861_1 tcTimerInterface1;

#if defined(TIMER1_OVF_vect) && ! defined(TIM1_OVF_vect)
#define TIM1_OVF_vect TIMER1_OVF_vect
#endif

/*
Like this?


                    +-\/-+
       (D 8)  PB0  1|    |20 PA0  (D 0)
      *(D 9)  PB1  2|    |19 PA1  (D 1)
      (D 10)  PB2  3|    |18 PA2  (D 2)  INT1
     *(D 11)  PB3  4|    |17 PA3  (D 3)
              VCC  5|    |16 AGND
              GND  6|    |15 AVCC
      (D 12)  PB4  7|    |14 PA4  (D 4)
     *(D 13)  PB5  8|    |13 PA5  (D 5)
INT0  (D 14)  PB6  9|    |12 PA6  (D 6)
      (D 15)  PB7 10|    |11 PA7  (D 7)
                    +----+

*/

/*
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
*/

#endif


#endif  // tc_hardware_mapping_t861_h
