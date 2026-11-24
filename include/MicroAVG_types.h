/**
 * @file MicroAVG_types.h
 * @author https://xfp23.github.io
 * @brief MicroAVG type definitions
 * @version 0.1
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 */

#ifndef __MICROAVG_TYPES_H__
#define __MICROAVG_TYPES_H__

#include "MicroAVG_conf.h"
#include <stdint.h>
#if MICROAVG_USE_MEM
#include "MicroMem.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* ================= Status Definition ================= */

typedef enum
{
    MICROAVG_OK = 0,
    MICROAVG_ERR,
    MICROAVG_DIVZERO_ERR,
    MICROAVG_MEM_ERR,
} MicroAVG_Status_t;

/* ================= Value Type Definition ================= */

#ifndef MICROAVG_VALUE_T
typedef float MicroAVG_Value_t;
#else
typedef MICROAVG_VALUE_T MicroAVG_Value_t;
#endif

/* ================= Index Type Auto Selection ================= */

#if (MICROAVG_DEPTH > 0U) && (MICROAVG_DEPTH <= 0xFFU)
typedef uint8_t  MicroAVG_Idx_t;
#elif (MICROAVG_DEPTH <= 0xFFFFU)
typedef uint16_t MicroAVG_Idx_t;
#else
#error "MICROAVG_DEPTH too large"
#endif

/* ================= ACC Type Auto Selection ================= */
#ifndef MICROAVG_ACC_T
typedef float MicroAVG_Acc_t;
#else
typedef MICROAVG_ACC_T MicroAVG_Acc_t;
#endif

typedef struct 
{
    uint32_t depth; // 滤波深度
} MicroAVG_Conf_t;

/* ================= Object Definition ================= */

typedef struct
{
#if MICROAVG_USE_MEM
    MicroAVG_Value_t *buffer;
    MicroAVG_Conf_t conf; 
#else
    volatile MicroAVG_Value_t buffer[MICROAVG_DEPTH];
#endif
    volatile MicroAVG_Idx_t index;
    volatile MicroAVG_Idx_t count;
    volatile MicroAVG_Idx_t depth;
    volatile MicroAVG_Acc_t sum;
    volatile MicroAVG_Value_t result; // debug use
} MicroAVG_Obj_t;

typedef MicroAVG_Obj_t *MicroAVG_Handle_t;

#ifdef __cplusplus
}
#endif

#endif /* __MICROAVG_TYPES_H__ */
