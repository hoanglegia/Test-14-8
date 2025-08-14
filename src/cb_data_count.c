uint32_t cb_data_count(cbuffer_t *cb){
    if(cb->reader <= cb->writer){
        return cb->writer - cb->reader;
    }else{
        return cb->writer + cb->size - cb->reader;
    }
}
