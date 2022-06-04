#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <asm/ioctls.h>
#include <math.h>
#include <sys/time.h>

#define KEY_NUM1	1
#define KEY_NUM2    2
#define KEY_NUM3    3
#define KEY_NUM4    4
#define KEY_NUM5    5
#define KEY_NUM6    6
#define KEY_NUM7    7
#define KEY_NUM8    8
#define KEY_NUM9    9
#define KEY_NUM10   10
#define KEY_NUM11   11
#define KEY_NUM12   12

#define MAXCHR	32
#define led_dev	"/dev/led"
#define dot "/dev/dot"
#define fnd_dev	"/dev/fnd"
#define tact_d "/dev/tactsw"

#define dbg(x...)       printf(x)

#define CARDSIZE 12
int card_in[12]; //카드 내용을 담는 배열 
int check_card[2]; // 선택한 카드가 짝이 맞는지 다른지 확인하기 위한 배열 
int check;//플레이어가 선택한 카드 번호 
int card_select[2];//플레이어가 선택한 카드 번호 두개 담는 배열 
int ordernum; //지금 고르는 카드가 첫번째 인지 두번째인지 확인
int count; //시도횟수  
int answer;//맞춘횟수  
int num1;//카드 12개 다맞췄을 시 게임을 종료하도록 함 
int player1_score;//플레이어1 점수 
int player2_score; //플레이어2 점수 
int player;//두 플레이어 구분 하기 위한 변수 
char c1, c2; //맞췄을 시 화면에 카드 내용을 보여주기 위한 변수 
char qmap[12];//카드 뒷면 
int dot_d = 0;
bool bools = true;// while 함수 종료하기 위한 논리값 
static char tactswDev[] = "/dev/tactsw";
static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

void match_up() {
	int dot_d = 0;
    int tact = 0;
    int fnd_d = 0;
    unsigned char t = 0;
    unsigned char c;
    unsigned char d;
	struct timeval dotst1, dotend1, tactst1, tactend1;
	int i = 0;
	
	char n1[1];
	char n2[1];
	char pla1[3]=" ";
	char alphP[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	unsigned char alph[26][8] = { {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42},	// A
								{0x3c, 0x22, 0x22, 0x3c, 0x22, 0x22, 0x22, 0x3c},	//B?
								{0x1C, 0x22, 0x20, 0x20, 0x20, 0x20, 0x22, 0x1C},	//C?
								{0x38, 0x44, 0x42, 0x42, 0x42, 0x42, 0x44, 0x38},	//D?
								{0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20, 0x3E},	//E?
								{0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20, 0x20},	//F?
								{0x1C, 0x22, 0x42, 0x40, 0x40, 0x47, 0x42, 0x3C},	//G?
								{0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x42},	//H??
								{0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C},	//I?
								{0x1C, 0x08, 0x08, 0x08, 0x08, 0x48, 0x48, 0x30},	//J?
								{0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44, 0x44},	//K?
								{0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E},	//L?
								{0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81},	//M??
								{0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x42},	//N
								{0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C},	//O
								{0x7C, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40},	//P
								{0x38, 0x44, 0x82, 0x82, 0x82, 0x8A, 0x44, 0x3A},	//Q
								{0x7C, 0x42, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42},	//R
								{0x3C, 0x42, 0x40, 0x3C, 0x02, 0x02, 0x42, 0x3C},	//S?
								{0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},	//T?
								{0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C},	//U
								{0x81, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18},	//V
								{0x81, 0x99, 0x99, 0x99, 0x99, 0x99, 0x5A, 0x24},	//W
								{0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},	//X
								{0x81, 0x81, 0x42, 0x42, 0x3C, 0x18, 0x18, 0x18},	//Y
								{0xFF, 0x03, 0x02, 0x04, 0x08, 0x10, 0x60, 0xFF},	//Z?
	};

	gettimeofday(&dotst1, NULL);

	while (1)
	{
		if (dot_d == 0) {
			dot_d = open(dot, O_RDWR);
		}
		gettimeofday(&dotend1, NULL);

		write(dot_d, &alph[i], sizeof(alph[i]));

		if ((dotend1.tv_usec - dotst1.tv_usec > 200000) || (dotend1.tv_sec > dotst1.tv_sec && (dotend1.tv_usec + 1000000 - dotst1.tv_usec > 200000)))
		{
			dot_d = close(dot_d);
			if (tact == 0)     //tact switch에 접근하지 않은 경우만 open
			{
				tact = open(tact_d, O_RDWR);
			}
			gettimeofday(&tactst1, NULL);
			while (1) {
				gettimeofday(&tactend1, NULL);
				read(tact, &t, sizeof(t));
				switch (t) {

				case KEY_NUM4:
					i = i - 1;
					break;

				case KEY_NUM5:{	
					strncpy(n1, alphP+i,1);
					strcat(pla1,n1);					
					printf("%s\n",pla1);					
					break;
				}


				case KEY_NUM6:
					i = i + 1;
					break;
				}
				if ((tactend1.tv_usec - tactst1.tv_usec > 200000) || (tactend1.tv_sec > tactst1.tv_sec && (tactend1.tv_usec + 1000000 - tactst1.tv_usec > 200000)) || t)
				{
					tact = close(tact);
					break;
				}
			}
			gettimeofday(&dotst1, NULL);
		}

	}
	
}

int main(void){
	match_up();
	return 0;
}
