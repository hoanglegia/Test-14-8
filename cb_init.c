void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    cb->data = (uint8_t *)buf;
    cb->size = size;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    cb->active = true;
}