#include "cbuffer.h"
using namespace std;

void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    cb->data = (uint8_t *)buf;
    cb->size = size;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    cb->active = true;
}

void cb_clear(cbuffer_t *cb){
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
}

uint32_t cb_data_count(cbuffer_t *cb){
    if(cb->reader <= cb->writer){
        return cb->writer - cb->reader;
    }else{
        return cb->writer + cb->size - cb->reader;
    }
}

uint32_t cb_space_count(cbuffer_t *cb){
    return cb->size - cb_data_count(cb) - 1;
}

uint32_t min(uint32_t a, uint32_t b){
    if(a < b){
        return a;
    } else{
        return b;
    }
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (cb == NULL || buf == NULL || !cb->active) {
        return 0;
    }
    uint32_t available = cb_data_count(cb);
    if (available == 0) {
        return 0;
    }
    uint32_t to_read = min(nbytes, available);
    uint8_t *pbuf = (uint8_t *)buf;

    for (uint32_t i = 0; i < to_read; i++) {
        pbuf[i] = cb->data[cb->reader];
        cb->reader = (cb->reader + 1) % cb->size;
    }
    return to_read;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (cb == NULL || buf == NULL || !cb->active) {
        return 0;
    }
    uint32_t space = cb_space_count(cb);
    if (space == 0) {
        cb->overflow += nbytes; // tất cả data mất
        return 0;
    }
    uint32_t to_write = min(nbytes, space);
    uint8_t *pbuf = (uint8_t *)buf;

    for (uint32_t i = 0; i < to_write; i++) {
        cb->data[cb->writer] = pbuf[i];
        cb->writer = (cb->writer + 1) % cb->size;
    }
    if (to_write < nbytes) {
        cb->overflow += (nbytes - to_write);
    }
    return to_write;
}

