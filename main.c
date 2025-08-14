#include "cbuffer.h"
cbuffer_t cb;
uint8_t cb_buff[6];
uint8_t a;
void main(void)
{
    cb_init(&cb, cb_buff, 100);
    cb_clear(&cb);
    char a[] = {0, 1, 2, 3, 4}; 
    int c = 5;
    cb_write(&cb, a, 5);
    char b[5];
    cb_read(&cb, b, 5);
    for(int i=0;i<5;i++){
        printf("%d ",b[i]);
    }
}