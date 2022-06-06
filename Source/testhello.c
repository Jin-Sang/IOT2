#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define dot_path "/dev/dot"
int main(){
int dot, i, j, k=0, cnt=0, flag=0; 
unsigned char c[9][8] = {{0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x42},  //H
                          {0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20, 0x3E},   //E
                          {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E},   //L
                          {0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C},   //O
                          {0x81, 0x99, 0x99, 0x99, 0x99, 0x99, 0x5A, 0x24},   //W
                          {0x7C, 0x42, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42},   //R
                          {0x38, 0x44, 0x42, 0x42, 0x42, 0x42, 0x44, 0x38},   //D
                          {0x00, 0x00, 0x00, 0x33, 0xcc, 0x00, 0x00, 0x00},   //~
                          {0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18}    //!                 };
unsigned char p[8];
int idx[12] = {0,1,2,2,3,4,3,5,2,6,7,8};
if((dot = open(dot_path, O_RDWR)) < 0) {
  printf("Can't Open\n");
  exit(0);
  }    
  while(k<12) {
  cnt = idx[k];
  for(i=0;i<16;i++)  {  
     for(j=0;j<8;j++)  {
          if(flag == 0)
          p[j] = (c[cnt][j] >> (7-i));
          if(flag == 1)
          p[j] = (c[cnt][j] << (i-7));            }
          write(dot,&p,sizeof(p));
          usleep(50000);
          if(i == 7)
          flag = 1;   
          }
          flag=0;        
          k++;    }
          close(dot);
          return 0;
          }
