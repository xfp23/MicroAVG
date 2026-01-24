/**
 * @file adc_filter_example.c
 * @author https://github.com/xfp23
 * @brief MicroAVG 示例：对物理域电压进行滑动平均滤波
 * @version 0.2 (适配最新 API)
 * @date 2026-01-24
 *
 * @copyright Copyright (c) 2026
 */

#include "MicroAVG.h"
#include <stdint.h>
#include <stdio.h>

/* ---------- ADC 硬件参数配置 ---------- */
#define ADC_RESOLUTION     4096.0f      /* 12位 ADC */
#define ADC_VREF_VOLTAGE   3.300f       /* 参考电压 3.3V */

/**
 * @brief 将 ADC 原始采样值转换为电压（物理域转换）
 */
static inline float ADC_RawToVoltage(uint16_t adc_raw)
{
    return ((float)adc_raw / ADC_RESOLUTION) * ADC_VREF_VOLTAGE;
}

int main(void)
{
    /* 1. 声明并初始化 MicroAVG 对象 */
    MicroAVG_Obj_t voltage_avg;
    MicroAVG_Init(&voltage_avg);

    while (1)
    {
        /* --- 模拟采样路径 (通常在定时器中断中) --- */
        
        // 读取原始值
        uint16_t raw_code = 2048; // 实际开发中替换为 HAL_ADC_GetValue() 等
        
        // 转换为物理值（电压）
        float current_voltage = ADC_RawToVoltage(raw_code);
        
        // 更新滤波器：将当前物理值推入滑动窗口 (O(1) 复杂度，ISR 安全)
        if (MicroAVG_Update(&voltage_avg, current_voltage) != MICROAVG_OK) {
            // 错误处理：对象指针无效
        }


        /* --- 模拟处理路径 (通常在主循环或低优先级任务中) --- */

        float avg_voltage = 0.0f;
        MicroAVG_Status_t status;

        // 获取平滑后的结果 (执行除法运算)
        status = MicroAVG_GetResult(&voltage_avg, &avg_voltage);

        if (status == MICROAVG_OK) {
            // 滤波结果有效
            // printf("Average Voltage: %.3f V\n", avg_voltage);
        } 
        else if (status == MICROAVG_DIVZERO_ERR) {
            // 缓冲区尚无数据
        }

        /* 模拟延时 */
        // Delay_ms(10);
        (void)avg_voltage;
    }
}