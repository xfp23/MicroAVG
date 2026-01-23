/**
 * @file MicroAVG_conf.h
 * @author https://github.com/xfp23
 * @brief MicroAVG component configuration file
 * @version 0.1
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 * This file is used to configure MicroAVG behavior.
 * Users should modify this file instead of component source code.
 */

#ifndef __MICROAVG_CONF_H__
#define __MICROAVG_CONF_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* ================= Version ================= */

#define MICROAVG_VERSION            "0.0.1"

/* ================= Value Type Configuration ================= */
/*
 * Define MICROAVG_VALUE_T to override default value type.
 * If not defined, MicroAVG will use float by default.
 *
 * Examples:
 *   #define MICROAVG_VALUE_T float
 *   #define MICROAVG_VALUE_T int16_t   // Q15
 *   #define MICROAVG_VALUE_T int32_t   // Q31
 *   #define MICROAVG_VALUE_T uint16_t
 *   #define MICROAVG_VALUE_T uint32_t
 */
#define MICROAVG_VALUE_T uint32_t

/* ================= Window Configuration ================= */
/*
 * Sliding window depth (sample count)
 * Large value will increase RAM usage.
 */
#define MICROAVG_DEPTH              80

/* ================= Feature Switch ================= */
/*
 * Enable or disable runtime safety check.
 * When enabled, parameter validation will be performed.
 */
// #define MICROAVG_ENABLE_ASSERT

/* ================= Debug Configuration ================= */
/*
 * Enable debug interface for development only.
 */
// #define MICROAVG_DEBUG_ENABLE

/* ================= Accumulator Type ================= */
/*
 * Accumulator type for sliding average.
 * DO NOT change unless you know exactly what you are doing.
 */
// #define MICROAVG_ACC_T float

#ifdef __cplusplus
}
#endif

#endif /* __MICROAVG_CONF_H__ */
