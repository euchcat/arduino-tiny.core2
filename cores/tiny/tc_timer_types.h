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

#ifndef tc_timer_types_h
#define tc_timer_types_h

#include <avr/io.h>

#include <tc_hardware_mapping.h>
#include <tc_macros.h>


#if TC_TIMER_0_IS_GENERIC_8_BIT
#define TC_HAVE_GENERIC_8_BIT_TIMER  (1)
#endif

#if TC_TIMER_1_IS_GENERIC_16_BIT
#define TC_HAVE_GENERIC_16_BIT_TIMER  (1)
#endif

#if TC_HAVE_GENERIC_8_BIT_TIMER || TC_HAVE_GENERIC_16_BIT_TIMER
#define TC_HAVE_GENERIC_TIMER  (1)
#endif


typedef struct
{
  uint8_t volatile * const pTCCRA;
  uint8_t volatile * const pTCCRB;
  uint8_t volatile * const pTCNT;
  uint8_t volatile * const pOCRA;
  uint8_t volatile * const pOCRB;
  uint8_t volatile * const pTIMSK;
  uint8_t volatile * const pTIFR;
}
tc_timer_register_set_generic_8b_t;


#if TC_HAVE_GENERIC_8_BIT_TIMER

#if TC_TIMER_0_IS_GENERIC_8_BIT

static const uint8_t TC_COMA1_8B  = COM0A1;
static const uint8_t TC_COMA0_8B  = COM0A0;
static const uint8_t TC_COMB1_8B  = COM0B1;
static const uint8_t TC_COMB0_8B  = COM0B0;
static const uint8_t TC_WGM1_8B   = WGM01;
static const uint8_t TC_WGM0_8B   = WGM00;
static const uint8_t TC_FOCA_8B   = FOC0A;
static const uint8_t TC_FOCB_8B   = FOC0B;
static const uint8_t TC_WGM2_8B   = WGM02;
static const uint8_t TC_CS2_8B    = CS02;
static const uint8_t TC_CS1_8B    = CS01;
static const uint8_t TC_CS0_8B    = CS00;
static const uint8_t TC_OCIEB_8B  = OCIE0B;
static const uint8_t TC_OCIEA_8B  = OCIE0A;
static const uint8_t TC_TOIE_8B   = TOIE0;
static const uint8_t TC_OCFB_8B   = OCF0B;
static const uint8_t TC_OCFA_8B   = OCF0A;
static const uint8_t TC_TOV_8B    = TOV0;
#define TC_SANITY_CHECK_CS2_8B    (CS02)
#define TC_SANITY_CHECK_CS1_8B    (CS01)
#define TC_SANITY_CHECK_CS0_8B    (CS00)

#else

#error Add bit definitions for the 8 bit generic timer or expand the condition above.

#endif // TC_TIMER_0_IS_GENERIC_8_BIT

#endif // TC_HAVE_GENERIC_8_BIT_TIMER


#if TC_HAVE_GENERIC_16_BIT_TIMER

typedef struct
{
  uint8_t volatile * const pTCCRA;
  uint8_t volatile * const pTCCRB;
  uint8_t volatile * const TCCRC;
  uint16_t volatile * const pTCNT;
  uint16_t volatile * const pOCRA;
  uint16_t volatile * const pOCRB;
  uint16_t volatile * const ICR;
  uint8_t volatile * const pTIMSK;
  uint8_t volatile * const pTIFR;
}
tc_timer_register_set_generic_16b_t;

#if TC_TIMER_1_IS_GENERIC_16_BIT

static const uint8_t TC_COMA1_16B  = COM1A1;
static const uint8_t TC_COMA0_16B  = COM1A0;
static const uint8_t TC_COMB1_16B  = COM1B1;
static const uint8_t TC_COMB0_16B  = COM1B0;
static const uint8_t TC_WGM1_16B   = WGM11;
static const uint8_t TC_WGM0_16B   = WGM10;
static const uint8_t TC_ICNC_16B   = ICNC1;
static const uint8_t TC_ICES_16B   = ICES1;
static const uint8_t TC_WGM3_16B   = WGM13;
static const uint8_t TC_WGM2_16B   = WGM12;
static const uint8_t TC_CS2_16B    = CS12;
static const uint8_t TC_CS1_16B    = CS11;
static const uint8_t TC_CS0_16B    = CS10;
static const uint8_t TC_FOCA_16B   = FOC1A;
static const uint8_t TC_FOCB_16B   = FOC1B;
static const uint8_t TC_ICIE_16B   = ICIE1;
static const uint8_t TC_OCIEB_16B  = OCIE1B;
static const uint8_t TC_OCIEA_16B  = OCIE1A;
static const uint8_t TC_TOIE_16B   = TOIE1;
static const uint8_t TC_ICF_16B    = ICF1;
static const uint8_t TC_OCFB_16B   = OCF1B;
static const uint8_t TC_OCFA_16B   = OCF1A;
static const uint8_t TC_TOV_16B    = TOV1;
#define TC_SANITY_CHECK_CS2_16B    (CS12)
#define TC_SANITY_CHECK_CS1_16B    (CS11)
#define TC_SANITY_CHECK_CS0_16B    (CS10)

#else

#error Add bit definitions for the 16 bit generic timer or expand the condition above.

#endif // TC_TIMER_1_IS_GENERIC_16_BIT

#endif // TC_HAVE_GENERIC_16_BIT_TIMER


#if TC_HAVE_GENERIC_TIMER

typedef struct
{
  long      cutoff;
  uint16_t  prescaler;
  uint8_t   clockselect;
}
tc_tone_cutoff_t;

static const tc_tone_cutoff_t tc_tone_cutoffs_1[] =
{
  { ((F_CPU+((2*1UL*256)-1))/(2*1UL*256)), 1, (0 << CS02) | (0 << CS01) | (1 << CS00) },
  { ((F_CPU+((2*8UL*256)-1))/(2*8UL*256)), 8, (0 << CS02) | (1 << CS01) | (0 << CS00) },
  { ((F_CPU+((2*64UL*256)-1))/(2*64UL*256)), 64, (0 << CS02) | (1 << CS01) | (1 << CS00) },
  { ((F_CPU+((2*256UL*256)-1))/(2*256UL*256)), 256, (1 << CS02) | (0 << CS01) | (0 << CS00) },
  { ((F_CPU+((2*1024UL*256)-1))/(2*1024UL*256)), 1024, (1 << CS02) | (0 << CS01) | (1 << CS00) }
};

static const uint8_t tc_tone_cutoff_1_count = sizeof(tc_tone_cutoffs_1) / sizeof(tc_tone_cutoffs_1[0]);

#if TC_HAVE_GENERIC_8_BIT_TIMER && TC_HAVE_GENERIC_16_BIT_TIMER
#if (TC_SANITY_CHECK_CS2_16B != TC_SANITY_CHECK_CS2_8B) || (TC_SANITY_CHECK_CS1_16B != TC_SANITY_CHECK_CS1_8B) || (TC_SANITY_CHECK_CS0_16B != TC_SANITY_CHECK_CS0_8B)
#error tone cutoffs for the 16 bit generic timer are assumed to be the same as the tone cutoffs for the 8 bit generic timer.  This assumption is not true for the selected processor.
#endif
#endif


void tc_frequency_out_of_range( void ) __attribute__((error("Frequency is too low.")));


class tcTimerInterfaceGenericTypes
{
public:

  typedef uint16_t prescale_value_t;

  typedef enum
  {
    Stopped               = 0b000,
    Prescale_Value_1      = 0b001,
    Prescale_Value_8      = 0b010,
    Prescale_Value_64     = 0b011,
    Prescale_Value_256    = 0b100,
    Prescale_Value_1024   = 0b101,
    T0_Falling            = 0b110,
    T0_Rising             = 0b111,
    Prescale_Index_1      = 0b001,
    Prescale_Index_2      = 0b010,
    Prescale_Index_3      = 0b011,
    Prescale_Index_4      = 0b100,
    Prescale_Index_5      = 0b101
  }
  cs_t;

  typedef enum
  {
    Disconnected = 0,
    Toggle = 0b01,
    Clear  = 0b10,
    Set    = 0b11
  }
  com_t;

  static const uint8_t PRESCALE_SET = (1);

  __attribute__((always_inline)) static inline 
  void GetToneCutoff( long frequency, uint8_t & cs, uint16_t & ps )
  {
    if ( (tc_tone_cutoff_1_count >= 1) && (frequency >= tc_tone_cutoffs_1[0].cutoff) )
    {
      cs = tc_tone_cutoffs_1[0].clockselect;
      ps = tc_tone_cutoffs_1[0].prescaler;
    }
    else if ( (tc_tone_cutoff_1_count >= 2) && (frequency >= tc_tone_cutoffs_1[1].cutoff) )
    {
      cs = tc_tone_cutoffs_1[1].clockselect;
      ps = tc_tone_cutoffs_1[1].prescaler;
    }
    else if ( (tc_tone_cutoff_1_count >= 3) && (frequency >= tc_tone_cutoffs_1[2].cutoff) )
    {
      cs = tc_tone_cutoffs_1[2].clockselect;
      ps = tc_tone_cutoffs_1[2].prescaler;
    }
    else if ( (tc_tone_cutoff_1_count >= 4) && (frequency >= tc_tone_cutoffs_1[3].cutoff) )
    {
      cs = tc_tone_cutoffs_1[3].clockselect;
      ps = tc_tone_cutoffs_1[3].prescaler;
    }
    else if ( (tc_tone_cutoff_1_count >= 5) && (frequency >= tc_tone_cutoffs_1[4].cutoff) )
    {
      cs = tc_tone_cutoffs_1[4].clockselect;
      ps = tc_tone_cutoffs_1[4].prescaler;
    }
    else if ( (tc_tone_cutoff_1_count >= 6) && (frequency >= tc_tone_cutoffs_1[5].cutoff) )
    {
      cs = tc_tone_cutoffs_1[5].clockselect;
      ps = tc_tone_cutoffs_1[5].prescaler;
    }
    else
    {
      tc_frequency_out_of_range();
      return;
    }
  }
};

#endif // TC_HAVE_GENERIC_TIMER


#if TC_HAVE_GENERIC_8_BIT_TIMER

static const tc_timer_register_set_generic_8b_t tc_timer_register_set_generic_8b[] = 
  {
#if TC_TIMER_0_IS_GENERIC_8_BIT
    { &TCCR0A, &TCCR0B, &TCNT0, &OCR0A, &OCR0B, &TIMSK0, &TIFR0 }
#endif
  };

template <unsigned trsi>
class tcTimerInterfaceGeneric8 : public tcTimerInterfaceGenericTypes
{
public:

  enum { index = trsi };

/* fix? rmv?
#define Timer0_OutputComparePinA  CORE_OC0A_PIN
#define Timer0_OutputComparePinB  CORE_OC0B_PIN

#define TIMER0_SUPPORTS_PHASE_CORRECT_PWM  (1)
*/

  // rmv typedef uint16_t prescale_value_t;

  __attribute__((always_inline)) static inline 
  uint8_t volatile * const GetPWM( void )
  {
    return( tc_timer_register_set_generic_8b[index].pTCCRA );
  }

  __attribute__((always_inline)) static inline 
  void SetToPowerup( void )
  {
    // Stop the clock, set waveform generation to normal, and set output mode to normal
    *tc_timer_register_set_generic_8b[index].pTCCRB = (0<<TC_FOCA_8B) | (0<<TC_FOCB_8B) | (0<<TC_WGM2_8B) | (0<<TC_CS2_8B) | (0<<TC_CS1_8B) | (0<<TC_CS0_8B);
    *tc_timer_register_set_generic_8b[index].pTCCRA = (0<<TC_COMA1_8B) | (0<<TC_COMA0_8B) | (0<<TC_COMB1_8B) | (0<<TC_COMB0_8B) | (0<<TC_WGM1_8B) | (0<<TC_WGM0_8B);
    // Reset the count to zero
    *tc_timer_register_set_generic_8b[index].pTCNT = 0;
    // Set the output compare registers to zero
    *tc_timer_register_set_generic_8b[index].pOCRA = 0;
    *tc_timer_register_set_generic_8b[index].pOCRB = 0;
    // Disable all interrupts
    *tc_timer_register_set_generic_8b[index].pTIMSK &= ~ MASK3( TC_OCIEA_8B, TC_OCIEB_8B, TC_TOIE_8B );
    // Clear the interrupt flags
    *tc_timer_register_set_generic_8b[index].pTIFR |= MASK3( TC_OCFA_8B, TC_OCFB_8B, TC_TOV_8B );
  }

  __attribute__((always_inline)) static inline 
  void InterruptsOff( void )
  {
    *tc_timer_register_set_generic_8b[index].pTIMSK &= ~ MASK3( TC_OCIEA_8B, TC_OCIEB_8B, TC_TOIE_8B );
  }

/* fix? rmv?
#define TIMER0_NUMBER_PRESCALERS  (5)

#define TIMER0_PRESCALER_VALUE_1  (1)
#define TIMER0_PRESCALER_VALUE_2  (8)
#define TIMER0_PRESCALER_VALUE_3  (64)
#define TIMER0_PRESCALER_VALUE_4  (256)
#define TIMER0_PRESCALER_VALUE_5  (1024)
*/

/* rmv
  typedef enum
  {
    Stopped               = 0b000,
    Prescale_Value_1      = 0b001,
    Prescale_Value_8      = 0b010,
    Prescale_Value_64     = 0b011,
    Prescale_Value_256    = 0b100,
    Prescale_Value_1024   = 0b101,
    T0_Falling            = 0b110,
    T0_Rising             = 0b111,
    Prescale_Index_1      = 0b001,
    Prescale_Index_2      = 0b010,
    Prescale_Index_3      = 0b011,
    Prescale_Index_4      = 0b100,
    Prescale_Index_5      = 0b101
  }
  cs_t;
*/

  __attribute__((always_inline)) static inline 
  void ClockSelect( cs_t cs )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRB = 
        (*tc_timer_register_set_generic_8b[index].pTCCRB & ~ MASK3( TC_CS2_8B, TC_CS1_8B, TC_CS0_8B )) 
        | (cs << TC_CS0_8B);
  }

  typedef enum
  {
    Normal                     = 0b000,
    Phase_Correct_PWM_FF       = 0b001,
    CTC_OCR                    = 0b010,
    Fast_PWM_FF                = 0b011,
    Reserved_1                 = 0b100,
    Phase_Correct_PWM_OCR      = 0b101,
    Reserved_2                 = 0b110,
    Fast_PWM_OCR               = 0b111
  }
  wgm_t;

  __attribute__((always_inline)) static inline 
  void SetWaveformGenerationMode( wgm_t wgm )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA = 
        (*tc_timer_register_set_generic_8b[index].pTCCRA & ~ MASK2( TC_WGM1_8B, TC_WGM0_8B )) 
        | (((wgm & 0b011) >> 0) << TC_WGM0_8B);

    *tc_timer_register_set_generic_8b[index].pTCCRB = 
        (*tc_timer_register_set_generic_8b[index].pTCCRB & ~ MASK1( TC_WGM2_8B ))
        | (((wgm & 0b100) >> 2) << TC_WGM2_8B);
  }

/* rmv
  typedef enum
  {
    Disconnected = 0,
    Toggle = 0b01,
    Clear  = 0b10,
    Set    = 0b11
  }
  com_t;
*/

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeA( com_t com )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA = 
        (*tc_timer_register_set_generic_8b[index].pTCCRA & ~ MASK2( TC_COMA1_8B, TC_COMA0_8B )) 
        | (com << TC_COMA0_8B);
  }

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeB( com_t com )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA = 
        (*tc_timer_register_set_generic_8b[index].pTCCRA & ~ MASK2( TC_COMB1_8B, TC_COMB0_8B )) 
        | (com << TC_COMB0_8B);
  }

  __attribute__((always_inline)) static inline 
  void DisconnectOutputs( void )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA &= ~ MASK4( TC_COMA1_8B, TC_COMA0_8B, TC_COMB1_8B, TC_COMB0_8B );
  }

  static const unsigned MAXIMUM_OCR = (255);
//rmv  static const uint8_t PRESCALE_SET = (1);

  typedef uint8_t ocr_t;
  typedef uint8_t tcnt_t;

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchAndClear( ocr_t oc )
  {
    *tc_timer_register_set_generic_8b[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchA( ocr_t oc )
  {
    *tc_timer_register_set_generic_8b[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchB( ocr_t oc )
  {
    *tc_timer_register_set_generic_8b[index].pOCRB = oc;
  }

  __attribute__((always_inline)) static inline 
  void EnableOutputCompareInterruptA( void )
  {
    *tc_timer_register_set_generic_8b[index].pTIMSK |= (1 << TC_OCIEA_8B);
  }

  __attribute__((always_inline)) static inline 
  void EnableOverflowInterrupt( void )
  {
    *tc_timer_register_set_generic_8b[index].pTIMSK |= (1 << TC_TOIE_8B);
  } 

  __attribute__((always_inline)) static inline 
  tcnt_t GetCount( void )
  {
    return( *tc_timer_register_set_generic_8b[index].pTCNT );
  }

  __attribute__((always_inline)) static inline 
  void SetCount( tcnt_t v )
  {
    *tc_timer_register_set_generic_8b[index].pTCNT = v;
  }

  __attribute__((always_inline)) static inline 
  bool IsOverflowSet( void )
  {
    return( (*tc_timer_register_set_generic_8b[index].pTIFR & (1 << TC_TOV_8B)) != 0 );
  }

  __attribute__((always_inline)) static inline 
  void CoreInitializeHelper( wgm_t wgm, cs_t cs )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA = (((wgm & 0b011) >> 0) << TC_WGM0_8B);
    *tc_timer_register_set_generic_8b[index].pTCCRB = (((wgm & 0b100) >> 2) << TC_WGM2_8B) | (cs << TC_CS0_8B);
  }

  __attribute__((always_inline)) static inline 
  void CoreInitialize( bool primary, cs_t cs, bool favorphasecorrect )
  {
    if ( primary )
    {
      CoreInitializeHelper( Fast_PWM_FF, cs );
      *tc_timer_register_set_generic_8b[index].pTIMSK = (1 << TC_TOIE_8B);      
    }
    else
    {
      if ( favorphasecorrect )
      {
        CoreInitializeHelper( Phase_Correct_PWM_FF, cs );
      }
      else
      {
        CoreInitializeHelper( Fast_PWM_FF, cs );
      }
    }
  }

  __attribute__((always_inline)) static inline 
  void CoreInitializeRmv( wgm_t wgm, cs_t cs, bool ei )
  {
    *tc_timer_register_set_generic_8b[index].pTCCRA = (((wgm & 0b011) >> 0) << TC_WGM0_8B);

    *tc_timer_register_set_generic_8b[index].pTCCRB = (((wgm & 0b100) >> 2) << TC_WGM2_8B) | (cs << TC_CS0_8B);

    if ( ei )
    {
      *tc_timer_register_set_generic_8b[index].pTIMSK = (1 << TC_TOIE_8B);
    }
  }

/* rmv
  typedef enum
  {
    ChannelAToggle = Toggle << TC_COMA0_8B,
    ChannelBToggle = Toggle << TC_COMB0_8B
  }
  channel_toggle_t;
*/

  __attribute__((always_inline)) static inline 
  void SetToneFrequency( long frequency, uint8_t channel )
  {
    uint8_t   cs;
    uint16_t  ps;
    uint8_t   ocr;

    GetToneCutoff( frequency, cs, ps ); 

    *tc_timer_register_set_generic_8b[index].pTCCRB = 
        (0 << TC_FOCA_8B) | (0 << TC_FOCB_8B) | 
        (0 << TC_WGM2_8B) | 
        (0 << TC_CS2_8B) | (0 << TC_CS1_8B) | (0 << TC_CS0_8B);

    *tc_timer_register_set_generic_8b[index].pTCNT = 0;

    *tc_timer_register_set_generic_8b[index].pTCCRA = 
        (channel & ((Toggle << TC_COMA0_8B) | (Toggle << TC_COMB0_8B))) |
        (1 << TC_WGM1_8B) | (0 << TC_WGM0_8B);

    ocr = ( (2L * F_CPU) / (frequency * 2L * ps) + 1L ) / 2L - 1L;
    
    *tc_timer_register_set_generic_8b[index].pOCRA = ocr;
    *tc_timer_register_set_generic_8b[index].pOCRB = ocr;

    *tc_timer_register_set_generic_8b[index].pTCCRB = 
        (0 << TC_FOCA_8B) | (0 << TC_FOCB_8B) | 
        (0 << TC_WGM2_8B) | 
        cs;
  }
};

#endif // #if TC_HAVE_GENERIC_8_BIT_TIMER


#if TC_HAVE_GENERIC_16_BIT_TIMER

static const tc_timer_register_set_generic_16b_t tc_timer_register_set_generic_16b[] = 
  {
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#if TC_TIMER_1_IS_GENERIC_16_BIT
    { &TCCR1A, &TCCR1B, &TCCR1C, &TCNT1, &OCR1A, &OCR1B, &ICR1, &TIMSK1, &TIFR1 }
#endif
  };

template <unsigned trsi>
class tcTimerInterfaceGeneric16 : public tcTimerInterfaceGenericTypes
{
public:

  enum { index = trsi };

  typedef uint16_t prescale_value_t;

  __attribute__((always_inline)) static inline 
  uint8_t volatile * const GetPWM( void )
  {
    return( tc_timer_register_set_generic_16b[index].pTCCRA );
  }

  __attribute__((always_inline)) static inline 
  void SetToPowerup( void )
  {
    // Stop the clock, set waveform generation to normal, and set output mode to normal
    *tc_timer_register_set_generic_16b[index].pTCCRB = (0<<TC_ICNC_16B) | (0<<TC_ICES_16B) | (0<<TC_WGM3_16B) | (0<<TC_WGM2_16B) | (0<<TC_CS2_16B) | (0<<TC_CS1_16B) | (0<<TC_CS0_16B);
    *tc_timer_register_set_generic_16b[index].pTCCRA = (0<<TC_COMA1_16B) | (0<<TC_COMA0_16B) | (0<<TC_COMB1_16B) | (0<<TC_COMB0_16B) | (0<<TC_WGM1_16B) | (0<<TC_WGM0_16B);
    // Don't need to do anything with TCCRC
    // Reset the count to zero
    *tc_timer_register_set_generic_16b[index].pTCNT = 0;
    // Set the output compare registers to zero
    *tc_timer_register_set_generic_16b[index].pOCRA = 0;
    *tc_timer_register_set_generic_16b[index].pOCRB = 0;
    // Don't need to do anything with ICR
    // Disable all interrupts
    *tc_timer_register_set_generic_16b[index].pTIMSK &= ~ MASK4( TC_ICIE_16B, TC_OCIEB_16B, TC_OCIEA_16B, TC_TOIE_16B );
    // Clear the interrupt flags
    *tc_timer_register_set_generic_16b[index].pTIFR |= MASK4( TC_ICF_16B, TC_OCFB_16B, TC_OCFA_16B, TC_TOV_16B );
  }

  __attribute__((always_inline)) static inline 
  void InterruptsOff( void )
  {
    *tc_timer_register_set_generic_16b[index].pTIMSK &= ~ MASK4( TC_ICIE_16B, TC_OCIEB_16B, TC_OCIEA_16B, TC_TOIE_16B );
  }

  __attribute__((always_inline)) static inline 
  void ClockSelect( cs_t cs )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRB = 
        (*tc_timer_register_set_generic_16b[index].pTCCRB & ~ MASK3( TC_CS2_16B, TC_CS1_16B, TC_CS0_16B )) 
        | (cs << TC_CS0_16B);
  }

  typedef enum
  {
    Normal                   = 0b0000,
    Phase_Correct_PWM_FF     = 0b0001,
    Phase_Correct_PWM_1FF    = 0b0010,
    Phase_Correct_PWM_3FF    = 0b0011,
    CTC_OCR                  = 0b0100,
    Fast_PWM_FF              = 0b0101,
    Fast_PWM_1FF             = 0b0110,
    Fast_PWM_3FF             = 0b0111,
    Phase_Frequency_PWM_ICR  = 0b1000,
    Phase_Frequency_PWM_OCR  = 0b1001,
    Phase_Correct_PWM_ICR    = 0b1010,
    Phase_Correct_PWM_OCR    = 0b1011,
    CTC_ICR                  = 0b1100,
    Reserved_1               = 0b1101,
    Fast_PWM_ICR             = 0b1110,
    Fast_PWM_OCR             = 0b1111
  }
  wgm_t;

  __attribute__((always_inline)) static inline 
  void SetWaveformGenerationMode( wgm_t wgm )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA = 
        (*tc_timer_register_set_generic_16b[index].pTCCRA & ~ MASK2( TC_WGM1_16B, TC_WGM0_16B )) 
        | (((wgm & 0b0011) >> 0) << TC_WGM0_16B);

    *tc_timer_register_set_generic_16b[index].pTCCRB = 
        (*tc_timer_register_set_generic_16b[index].pTCCRB & ~ MASK2( TC_WGM3_16B, TC_WGM2_16B ))
        | (((wgm & 0b1100) >> 2) << TC_WGM2_16B);
  }

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeA( com_t com )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA = 
        (*tc_timer_register_set_generic_16b[index].pTCCRA & ~ MASK2( TC_COMA1_16B, TC_COMA0_16B )) 
        | (com << TC_COMA0_16B);
  }

  __attribute__((always_inline)) static inline 
  void SetCompareOutputModeB( com_t com )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA = 
        (*tc_timer_register_set_generic_16b[index].pTCCRA & ~ MASK2( TC_COMB1_16B, TC_COMB0_16B )) 
        | (com << TC_COMB0_16B);
  }

  __attribute__((always_inline)) static inline 
  void DisconnectOutputs( void )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA &= ~ MASK4( TC_COMA1_16B, TC_COMA0_16B, TC_COMB1_16B, TC_COMB0_16B );
  }

  static const unsigned MAXIMUM_OCR = (65535);

  typedef uint16_t ocr_t;
  typedef uint16_t tcnt_t;

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchAndClear( ocr_t oc )
  {
    *tc_timer_register_set_generic_16b[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchA( ocr_t oc )
  {
    *tc_timer_register_set_generic_16b[index].pOCRA = oc;
  }

  __attribute__((always_inline)) static inline 
  void SetOutputCompareMatchB( ocr_t oc )
  {
    *tc_timer_register_set_generic_16b[index].pOCRB = oc;
  }

  __attribute__((always_inline)) static inline 
  void EnableOutputCompareInterruptA( void )
  {
    *tc_timer_register_set_generic_16b[index].pTIMSK |= (1 << TC_OCIEA_16B);
  }

  __attribute__((always_inline)) static inline 
  void EnableOverflowInterrupt( void )
  {
    *tc_timer_register_set_generic_16b[index].pTIMSK |= (1 << TC_TOIE_16B);
  } 

  __attribute__((always_inline)) static inline 
  tcnt_t GetCount( void )
  {
    return( *tc_timer_register_set_generic_16b[index].pTCNT );
  }

  __attribute__((always_inline)) static inline 
  void SetCount( tcnt_t v )
  {
    *tc_timer_register_set_generic_16b[index].pTCNT = v;
  }

  __attribute__((always_inline)) static inline 
  bool IsOverflowSet( void )
  {
    return( (*tc_timer_register_set_generic_16b[index].pTIFR & (1 << TC_TOV_16B)) != 0 );
  }

  __attribute__((always_inline)) static inline 
  void CoreInitializeHelper( wgm_t wgm, cs_t cs )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA = (((wgm & 0b0011) >> 0) << TC_WGM0_16B);
    *tc_timer_register_set_generic_16b[index].pTCCRB = (((wgm & 0b1100) >> 2) << TC_WGM2_16B) | (cs << TC_CS0_16B);
  }

  __attribute__((always_inline)) static inline 
  void CoreInitialize( bool primary, cs_t cs, bool favorphasecorrect )
  {
    if ( primary )
    {
      CoreInitializeHelper( Fast_PWM_FF, cs );
      *tc_timer_register_set_generic_16b[index].pTIMSK = (1 << TC_TOIE_16B);
    }
    else
    {
      if ( favorphasecorrect )
      {
        CoreInitializeHelper( Phase_Correct_PWM_FF, cs );
      }
      else
      {
        CoreInitializeHelper( Fast_PWM_FF, cs );
      }
    }
  }

  __attribute__((always_inline)) static inline 
  void CoreInitializeRmv( wgm_t wgm, cs_t cs, bool ei )
  {
    *tc_timer_register_set_generic_16b[index].pTCCRA = (((wgm & 0b0011) >> 0) << TC_WGM0_16B);

    *tc_timer_register_set_generic_16b[index].pTCCRB = (((wgm & 0b1100) >> 2) << TC_WGM2_16B) | (cs << TC_CS0_16B);

    if ( ei )
    {
      *tc_timer_register_set_generic_16b[index].pTIMSK = (1 << TC_TOIE_16B);
    }
  }

  __attribute__((always_inline)) static inline 
  void SetToneFrequency( long frequency, uint8_t channel )
  {
    uint8_t   cs;
    uint16_t  ps;
    uint8_t   ocr;

    GetToneCutoff( frequency, cs, ps ); 

    *tc_timer_register_set_generic_16b[index].pTCCRB = 
        (0 << TC_ICNC_16B) | (0 << TC_ICES_16B) | 
        (0 << TC_WGM3_16B) | (0 << TC_WGM2_16B) | 
        (0 << TC_CS2_16B) | (0 << TC_CS1_16B) | (0 << TC_CS0_16B);

    *tc_timer_register_set_generic_16b[index].pTCNT = 0;

    *tc_timer_register_set_generic_16b[index].pTCCRA = 
        (channel & ((Toggle << TC_COMA0_16B) | (Toggle << TC_COMB0_16B))) |
        (0 << TC_WGM1_16B) | (0 << TC_WGM0_16B);

    ocr = ( (2L * F_CPU) / (frequency * 2L * ps) + 1L ) / 2L - 1L;
    
    *tc_timer_register_set_generic_16b[index].pOCRA = ocr;
    *tc_timer_register_set_generic_16b[index].pOCRB = ocr;

    *tc_timer_register_set_generic_16b[index].pTCCRB = 
        (0 << TC_ICNC_16B) | (0 << TC_ICES_16B) | 
        (0 << TC_WGM3_16B) | (1 << TC_WGM2_16B) | 
        cs;
  }
};

#endif // TC_HAVE_GENERIC_16_BIT_TIMER


#endif
