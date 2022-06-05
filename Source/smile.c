#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define dot "/dev/dot"
int main(){
  int dot_d, i;
  unsigned char c[2][8] = {{0x00,0x66,0x66,0x00,0x00,0x22,0x1c,0x00},
                            {0x00,0x66,0x66,0x00,0x00,0x1c,0x22,0x00}};
  if((dot_d = open(dot, O_RDWR)) < 0) {
    printf("Can't Open\n");
    exit(0);    
    } 
  for(i=0;i<4;i++)    {  
  write(dot_d,&c[i%2],sizeof(c[i%2]));
  sleep(2);    } 
  close(dot_d);
  return 0;
}
