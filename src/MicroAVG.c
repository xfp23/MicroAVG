#include "MicroAVG.h"
#include "string.h"

MicroAVG_Status_t MicroAVG_Init(MicroAVG_Obj_t *obj)
{
    if (obj == NULL)
    {
        return MICROAVG_ERR;
    }

    memset(obj, 0, sizeof(MicroAVG_Obj_t));
    return MICROAVG_OK;
}

MicroAVG_Status_t MicroAVG_Update(MicroAVG_Obj_t *obj, MicroAVG_Value_t input)
{
    MicroAVG_Value_t old;

    if (obj == NULL)
    {
        return MICROAVG_ERR;
    }

    old = obj->buffer[obj->index];
    obj->buffer[obj->index] = input;

    obj->index++;
    if (obj->index >= MICROAVG_DEPTH)
    {
        obj->index = 0;
    }

    if (obj->count < MICROAVG_DEPTH)
    {
        obj->sum += input;
        obj->count++;
    }
    else
    {
        obj->sum += input;
        obj->sum -= old;
    }

    // return (MicroAVG_Value_t)(obj->sum / obj->count);
    return MICROAVG_OK;
}

MicroAVG_Status_t MicroAVG_Reset(MicroAVG_Obj_t *obj)
{
    if (!obj)
    {
        return MICROAVG_ERR;
    }

    obj->index = 0;
    obj->count = 0;
    obj->sum = 0;

    return MICROAVG_OK;
}

MicroAVG_Status_t MicroAVG_GetResult(MicroAVG_Obj_t *obj, MicroAVG_Value_t *output)
{
    if (obj == NULL || output == NULL)
    {
        return MICROAVG_ERR;
    }

    if (obj->count == 0)
    {
        *output = (MicroAVG_Value_t)0;
        return MICROAVG_DIVZERO_ERR;
    }

    obj->result = (MicroAVG_Value_t)(obj->sum / obj->count);
    *output = obj->result;
    return MICROAVG_OK;
}