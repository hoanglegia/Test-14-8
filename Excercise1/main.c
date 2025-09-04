#include "cbuffer.h"
cbuffer_t cb;
uint8_t cb_buff[5];
uint8_t a;
void main(void)
{
    cb_init(&cb, cb_buff, 5);
    cb_clear(&cb);
    char a[] = {0, 1, 2, 3}; 
    cb_write(&cb, a, 4);

    char b[6] = {0};
    cb_read(&cb, b, 3);
    for(int i=0;i<5;i++){
        printf("%d ",b[i]);
    }
    printf("\n");
    
    char c[] = {4, 5, 6}; 
    cb_write(&cb, c, 3);

    char d[6] = {0};
    cb_read(&cb, d, 3);
    for(int j=0;j<6;j++){
        printf("%d ",d[j]);
    }
}