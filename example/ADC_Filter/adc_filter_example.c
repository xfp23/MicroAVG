/**
 * @file adc_filter_example.c
 * @author https://github.com/xfp23
 * @brief MicroAVG example: filter ADC raw value and convert to voltage
 * @version 0.1
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 */

#include "MicroAVG.h"
#include <stdint.h>

/* ---------- ADC & voltage configuration ---------- */
#define ADC_RESOLUTION     4096.0f     /* 12-bit ADC */
#define ADC_VREF_VOLTAGE   3.300f      /* Vref = 3.3V */

/* Convert ADC raw code to voltage */
static inline float ADC_RawToVoltage(float adc_raw)
{
    return (adc_raw / ADC_RESOLUTION) * ADC_VREF_VOLTAGE;
}

int main(void)
{
    MicroAVG_Obj_t adc_avg;

    /* Initialize MicroAVG */
    MicroAVG_Init(&adc_avg);

    while (1)
    {
        /* 1. Read ADC raw value (example) */
        uint16_t adc_raw = 2048;   /* replace with real ADC read */

        /* 2. Filter ADC raw value */
        float adc_raw_filtered;
        adc_raw_filtered = MicroAVG_Update(&adc_avg, (float)adc_raw);

        /* 3. Convert filtered raw value to voltage */
        float voltage;
        voltage = ADC_RawToVoltage(adc_raw_filtered);

        /* voltage can now be used for control / monitoring / reporting */
        (void)voltage;
    }
}
