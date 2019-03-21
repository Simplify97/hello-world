#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "HZcode.h"

#define Width  800
#define Height 480

int main(void)
{
    uint16_t i,j,k;
    //uint8_t buf[32];    //c7 b6 c8 eb ca bd 20 20  20 20 bf aa b7 a2 0a
    uint8_t code[16] = {0xC7,0xB6,0xC8,0xEB,0xCA,0xBD,0x20,0x20,0x20,0x20,0x20,0x20,0xBF,0xAA,0xB7,0xA2};
    uint8_t ascii[5] = {'L','i','n','u','x'};
#if 1 
    struct {
        char b;
        char g;
        char r;
    } imagedata[Height][Width];
    memset(imagedata,200,Width*Height*3);

    //显示汉字
    for(i=0 ; i<8 ; i++)
        showHZcode(&code[i*2],(char *)imagedata,100+16*i,100);
    //显示英文
    for(i=0 ; i<5 ; i++)
        showASC(&ascii[i],(char *)imagedata,148+8*i,100);
#else 
    char * imagedata;
    imagedata = (char *)malloc(Width*Height*3);
    memset(imagedata,0,Width*Height*3);
    for(j=0 ; j<Height ; j++)
        for(i=0 ; i<Width ; i++) {
            *(imagedata + j*Width + i*3)     = 255;      //b
            *(imagedata + j*Width + i*3 + 1) = 0;        //g
            *(imagedata + j*Width + i*3 + 2) = 0;        //r
        }
#endif
    MakeBmpFile ((char *)imagedata,Width,Height,"red.bmp");
    //free(imagedata);
    return 0;
}
