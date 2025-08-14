/**
 * @file       cbuffer.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Group 5
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       None
 */
/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"

/* Public function ---------------------------------------------------- */
void cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
    if (cb == NULL || buf == NULL)
        return;
    cb->data = (uint8_t*)buf;
    cb->size = size;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    cb->active = true;
    return;
}

void cb_clear(cbuffer_t *cb)
{
    if (cb == NULL)
        return;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    return;
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    while (cb->reader != nbytes)
    {
        if ((cb->writer - cb->reader) == READER_BEFORE_WRITER_IS_FULL ||
            (cb->writer + cb->size - cb->reader == WRITER_BEFORE_READER_IS_FULL))
            return cb->reader;
        else
        {
            if (buf != NULL)
            {
                ((uint8_t*)buf)[cb->reader] = cb->data[cb->reader];
                cb->reader = (cb->reader + 1) % cb->size;
            }
        }    
    }
    return cb->reader;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    while (cb->writer != nbytes)
    {
        if (cb_space_count(cb) == NO_SPACE_AVAILABLE)
            return cb->writer;
        else
        {
            if (buf != NULL)
            {
                cb->data[cb->writer] = ((uint8_t*)buf)[cb->writer];
                cb->writer = (cb->writer + 1) % cb->size;
            }
        }    
    }
    return cb->writer;
}

uint32_t cb_data_count(cbuffer_t *cb) 
{
    if (cb == NULL) 
        return ERROR_CB_DATA_COUNT;
    if (cb->reader <= cb->writer)
        return cb->writer - cb->reader;
    else
        return cb->writer + cb->size - cb->reader;
}

uint32_t cb_space_count(cbuffer_t *cb) 
{
    if (cb == NULL)
        return ERROR_CB_SPACE_COUNT;
    return cb->size - cb_data_count(cb) - 1;
}