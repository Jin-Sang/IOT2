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


#define MAXCHR	32
#define led_dev	"/dev/led"
#define dot "/dev/dot"
#define fnd_dev	"/dev/fnd"
#define tact_d "/dev/tactsw"
#define clcd "/dev/clcd"

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
char c1,c2; //맞췄을 시 화면에 카드 내용을 보여주기 위한 변수 
char qmap[12];//카드 뒷면 
int dot_d = 0;
bool bools=true;// while 함수 종료하기 위한 논리값 
static char tactswDev[] = "/dev/tactsw";
static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);
char pla1[3] = " ";
char pla2[3] = " ";
char playervs[20] ="  ";
char vs[5] =" vs ";






void print_lcd(char clcd_text[]) {
	int clcd_d;

	clcd_d = open(clcd, O_RDWR);
	if (clcd_d < 0){
		printf("clcd error\n");
	}

	write(clcd_d, clcd_text, strlen(clcd_text));
  
  
	close(clcd_d);

}

int main(){
    char a = "   Cross Game   ";
    char b = "   Press Start  ";
    print_lcd(a + b);
    return 0;
}
