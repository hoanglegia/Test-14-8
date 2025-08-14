#include<cbuffer.h>

void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    cb->data = buf;
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
    if(a <  b){
        return a;
    }
}

