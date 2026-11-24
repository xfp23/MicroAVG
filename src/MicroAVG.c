#include "MicroAVG.h"
#include "string.h"

#if MICROAVG_USE_MEM
MicroAVG_Status_t MicroAVG_Init(MicroAVG_Handle_t *handle, MicroAVG_Conf_t *conf)
{
    if (handle != NULL || conf == NULL)
    {
        return MICROAVG_ERR;
    }

    *handle = (MicroAVG_Obj_t *)MicroMem_Alloc(1, sizeof(MicroAVG_Obj_t));

    (*handle)->buffer = (MicroAVG_Value_t *)MicroMem_Alloc(conf->depth, sizeof(MicroAVG_Value_t));

    if ((*handle) == NULL)
    {
        // MicroMem_Free(1, sizeof(MicroAVG_Obj_t));
        return MICROAVG_MEM_ERR;
    }

    if ((*handle)->buffer == NULL)
    {
        // MicroMem_Free(conf->depth, sizeof(MicroAVG_Value_t));
        // MicroMem_Free(1, sizeof(MicroAVG_Obj_t));
        (*handle) = NULL;

        return MICROAVG_MEM_ERR;
    }

    (*handle)->conf = *conf;

    memset((*handle)->buffer, 0, sizeof(MicroAVG_Value_t) * (*handle)->conf.depth);
    return MICROAVG_OK;
}

MicroAVG_Status_t MicroAVG_Update(MicroAVG_Handle_t handle, MicroAVG_Value_t input)
{
    if (handle == NULL)
    {
        return MICROAVG_ERR;
    }

    MicroAVG_Value_t old;

    old = handle->buffer[handle->index];
    handle->buffer[handle->index] = input;

    handle->index++;
    if (handle->index >= handle->conf.depth)
    {
        handle->index = 0;
    }

    if (handle->count < handle->conf.depth)
    {
        handle->sum += input;
        handle->count++;
    }
    else
    {
        handle->sum += input;
        handle->sum -= old;
    }

    return MICROAVG_OK;
}

MicroAVG_Status_t MicroAVG_Reset(MicroAVG_Handle_t handle)
{
    if (!handle)
    {
        return MICROAVG_ERR;
    }

    handle->index = 0;
    handle->count = 0;
    handle->sum = 0;

    return MICROAVG_OK;
}

MicroAVG_Value_t MicroAVG_GetResult(MicroAVG_Handle_t handle)
{
    if (handle == NULL)
    {
        return (MicroAVG_Value_t)0;
    }

    if (handle->count == 0)
    {
        return (MicroAVG_Value_t)0;
        // return MICROAVG_DIVZERO_ERR;
    }

    handle->result = (MicroAVG_Value_t)(handle->sum / handle->count);
    return handle->result;
}
#else 
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

MicroAVG_Value_t MicroAVG_GetResult(MicroAVG_Obj_t *obj)
{
    if (obj == NULL)
    {
        return (MicroAVG_Value_t)0;
    }

    if (obj->count == 0)
    {
        return (MicroAVG_Value_t)0;
        // return MICROAVG_DIVZERO_ERR;
    }

    obj->result = (MicroAVG_Value_t)(obj->sum / obj->count);
    return obj->result;
}
#endif