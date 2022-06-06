#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define dot_path "/dev/dot"

int main(){
int dot, i, j, k=0, cnt=0, flag=0;
unsigned char alph[28][8] = {{0x00, 0x7e, 0x02, 0x12, 0x12, 0x13, 0x7e, 0x00}, // 고
                             {0x00, 0xf4, 0x94, 0x96, 0x94, 0x94, 0xf4, 0x00}, // 마
			  				 {0x00, 0x72, 0x8a, 0x72, 0x0e, 0xfa, 0x22, 0x22}, // 워
                             {0x00, 0x38, 0x44, 0x44, 0x38, 0x28, 0xfe, 0x00}, // 요
			   				 {0x24, 0x5a, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18} // 하트
			 };

unsigned char p[8];
int idx[12] = {4,4,4,4,0,1,2,3,4,4,4,4};
if((dot = open(dot_path, O_RDWR)) < 0){
  printf("Can't Open\n");
  exit(0);
  }
  while(k<12){
  cnt = idx[k];
  for(i=0;i<16;i++){
     for(j=0;j<8;j++){
          if(flag == 0)
          p[j] = (alph[cnt][j] >> (7-i));
          if(flag == 1)
          p[j] = (alph[cnt][j] << (i-7));}
          write(dot,&p,sizeof(p));
          usleep(50000);
          if(i == 7)
          flag = 1; 
          }
          flag=0;
          k++;}
          close(dot);
          return 0;
          }
