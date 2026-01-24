/**
 * @file MicroAVG.h
 * @author https://github.com/xfp23
 * @brief MicroAVG - Lightweight sliding average filter component
 * @version 0.1
 * @date 2026-01-23
 *
 * MicroAVG is a simple, deterministic sliding average component designed for
 * embedded systems.
 *
 * Design principles:
 *  - No dynamic memory allocation
 *  - Fixed window size defined at compile time
 *  - User-configurable sample type
 *  - Platform and signal-source independent
 *
 * Typical usage:
 *  1. Declare a MicroAVG_Obj_t object
 *  2. Call MicroAVG_Init() once during system initialization
 *  3. Call MicroAVG_Update() for each new sample
 *  4. Call MicroAVG_Reset() when filter state needs to be cleared
 *
 * Note:
 *  - MicroAVG operates on physical-domain values, not raw ADC codes.
 *  - The returned value represents the current averaged result.
 *
 * @copyright Copyright (c) 2026
 */

#ifndef __MICROAVG_H__
#define __MICROAVG_H__

#include "MicroAVG_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initialize a MicroAVG object.
 *
 * This function initializes the internal state of the sliding average filter.
 * It should be called once before the object is used.
 *
 * @param obj Pointer to MicroAVG object
 * @return MICROAVG_OK on success, MICROAVG_ERR on invalid parameter
 */
extern MicroAVG_Status_t MicroAVG_Init(MicroAVG_Obj_t *obj);

/**
 * @brief Update sliding average with a new input sample.
 *
 * This function pushes a new sample into the sliding window, updates the
 * internal state, and returns the current averaged value.
 *
 * @param obj   Pointer to MicroAVG object
 * @param input New input sample
 * @return MICROAVG_OK on success, MICROAVG_ERR on invalid parameter
 */
extern MicroAVG_Status_t MicroAVG_Update(MicroAVG_Obj_t *obj, MicroAVG_Value_t input);

/**
 * @brief Reset internal state of the MicroAVG object.
 *
 * This function clears the filter history and accumulator while keeping
 * the configuration unchanged. It is typically used when system state,
 * operating mode, or signal validity changes during runtime.
 *
 * @param obj Pointer to MicroAVG object
 * @return MICROAVG_OK on success, MICROAVG_ERR on invalid parameter
 */
extern MicroAVG_Status_t MicroAVG_Reset(MicroAVG_Obj_t *obj);

/**
 * @brief Get avg result of the MicroAVG object.
 * 
 * @param obj Pointer to MicroAVG object
 * @param output Pointer to result buffer
 * @return MicroAVG_Status_t MICROAVG_OK on success, MICROAVG_ERR on invalid parameter
 */
extern MicroAVG_Status_t MicroAVG_GetResult(MicroAVG_Obj_t *obj,MicroAVG_Value_t *output);

#ifdef __cplusplus
}
#endif

#endif /* __MICROAVG_H__ */
