uint32_t cb_space_count(cbuffer_t *cb){
    return cb->size - cb_data_count(cb) - 1;
}