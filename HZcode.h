
void showHZcode(uint8_t *code,uint8_t *imagedata,uint16_t x,uint16_t y)
{
    uint8_t i,j,k;
    uint8_t buf[32];
    uint64_t offset;
    memset(buf,0,32);
    offset = (94*(*code-0xa0-1)+(*(code+1)-0xa0-1))*32;

    FILE *hzfp = fopen("HZK1616.dat","rb");
    if(!hzfp) {
        printf("open file failed!\n");
    }

    fseek(hzfp,offset,SEEK_SET);
    fread(buf,1,32,hzfp);

    for(i=x ; i<x+16 ; i++)
        for(j=y ; j<y+2 ; j++)
            for(k=0; k<8 ; k++) {
                if((buf[(j-y)+(i-x)*2] >> k) & 0x01) {   
                    *(imagedata+(7-k+(j-y)*8+(i-x)*800+y*800+x)*3+2) = 255;
                    *(imagedata+(7-k+(j-y)*8+(i-x)*800+y*800+x)*3) = 0;
                }
                else {   
                    *(imagedata+(7-k+(j-y)*8+(i-x)*800+y*800+x)*3) = 255;
                    *(imagedata+(7-k+(j-y)*8+(i-x)*800+y*800+x)*3+2) = 0;
                }
                *(imagedata+(7-k+(j-y)*8+(i-x)*800+y*800+x)*3+1) = 0;
            }
}


void showASC(uint8_t *code,uint8_t *imagedata,uint16_t x,uint16_t y)
{
    uint8_t i,j,k;
    uint8_t buf[14];
    uint64_t offset;
    memset(buf,0,14);
    offset = (*code)*14;

    FILE *ascfp = fopen("ASC0814.dat","rb");
    if(!ascfp) {
        printf("open file failed!\n");
    }
    
    fseek(ascfp,offset,SEEK_SET);
    fread(buf,1,14,ascfp);

    for(i=x ; i<x+14 ; i++)
        for(j=y ; j<y+1 ; j++)
            for(k=0; k<8 ; k++) {
                if((buf[i-x] >> k) & 0x01) { 
                    *(imagedata+(7-k+y*800+x+(i-x)*800)*3+2) = 255;
                    *(imagedata+(7-k+y*800+x+(i-x)*800)*3) = 0;
                }
                else {
                    *(imagedata+(7-k+y*800+x+(i-x)*800)*3) = 255;
                    *(imagedata+(7-k+y*800+x+(i-x)*800)*3+2) = 0;
                }
                *(imagedata+(7-k+y*800+x+(i-x)*800)*3+1) = 0;
            }

}
/*
    printf("offset = %d\n",offset);
    printf("code[0] = %x,code[1] = %x\n",code[0],code[1]);
    for(int i=0 ; i<32 ; i++) {
            printf("buf[%d] = %x\n",i,buf[i]);
    }
    uint8_t i,j,k;
    for(i=x ; i<16+x ; i++)
        for(j=y; j<2+y ; j++)  
            for(k=0; k<8 ; k++) {
                if((buf[j+2*i]>>k) & 0x01)  imagedata[i][j*8+(7-k)].r = 255;
                else    imagedata[i][j*8+(7-k)].b = 255;
            }

        for(i=x ; i<x+16 ; i++)
        for(j=y ; j<y+2 ; j++)
            for(k=0; k<8 ; k++) {
                if((buf[(j-y)+(i-x)*2] >> k) & 0x01)    *(imagedata+(7-k+j*8+i*800)*3+2) = 255;
                else    *(imagedata+(7-k+j*8+i*800)*3) = 255;
            }
*/