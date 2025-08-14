void cb_clear(cbuffer_t *cb){
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
}