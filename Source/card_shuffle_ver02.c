//#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/signal.h>
//#include <sys/types.h>
//#include <sys/ioctl.h>
//#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
//#include <asm/ioctls.h>


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
bool bools=true;// while 함수 종료하기 위한 논리값 

unsigned char rps[1][8] = {	// dot matrix
	{ 0x00,0x54,0x00,0x54,0x00,0x54,0x00,0x54 }, // 초기값 

};
unsigned char card_led[1][3] = {
	{0x40,0x10,0x04},
};

void card_off(int a) {
	int a1=a;
	int back1,back2,back3;
	if (a1<4){
		back1=rps[0][1];
		printf("%#x\n",back1);
	}
	else if(a1<7){
		back1=rps[0][3];
		printf("%#x \n",back1);
	}
	else if(a1<10){
		back1=rps[0][5];
		printf("%#x \n",back1);
	}
	else {
		back1=rps[0][7];
		printf("%#x \n",back1);
	}
	switch(a1){
		case(1):{
			back2=card_led[0][0];
			back3=back1-back2;
			rps[0][1]=back3;
			break;
			}
		case(2):{
			back2=card_led[0][1];
			back3=back1-back2;
			rps[0][1]=back3;
			break;
			}
		case(3):{
			back2=card_led[0][2];
			back3=back1-back2;
			rps[0][1]=back3;
			break;
			}
		case(4):{
			back2=card_led[0][0];
			back3=back1-back2;
			rps[0][3]=back3;
			break;
			}
		case(5):{
			back2=card_led[0][1];
			back3=back1-back2;
			rps[0][3]=back3;
			break;
			}
		case(6):{
			back2=card_led[0][2];
			back3=back1-back2;
			rps[0][3]=back3;
			break;
			}
		case(7):{
			back2=card_led[0][0];
			back3=back1-back2;
			rps[0][5]=back3;
			break;
			}
		case(8):{
			back2=card_led[0][1];
			back3=back1-back2;
			rps[0][5]=back3;
			break;
			}
		case(9):{
			back2=card_led[0][2];
			back3=back1-back2;
			rps[0][5]=back3;
			break;
			}
		case(10):{
			back2=card_led[0][0];
			back3=back1-back2;
			rps[0][7]=back3;
			break;
			}
		case(11):{
			back2=card_led[0][1];
			back3=back1-back2;
			rps[0][7]=back3;
			break;
			}
		case(12):{
			back2=card_led[0][2];
			back3=back1-back2;
			rps[0][7]=back3;
			break;
			}			
	}
}
void map1(void) {
	int i;
	for (i=0; i<12; i++){
		qmap[i]='?';
	}
}//카드 내용을 가리기 위해 카드 뒷면으로 사용할 '?' 배열 
 

void card_shuffle(void) {
	srand(time(NULL));//게임을 시작할때마다 다르게 섞이도록 하기 위한 srand()함수 
	int i,j,x;
	memset(card_in,0,sizeof(card_in));
	for(i=1; i<7; i++) //1~6 숫자를  
	{
		for(j=0; j<2; j++)//두 개의 카드에 집어 넣음 
		{
			do
			{
				x=rand()%12;
			} while (card_in[x] != 0);
			
			card_in[x]=i;

		}
	}
} //12개의 카드에 1~6의 숫자를 두번씩 총 12번 넣어 카드를 섞는 코드

void show_map(void) {
	printf("\n");
	int i;
	for (i=0; i<12; i++){
		if(i%3==0){
			printf("\n");
		}
		printf("%c ", qmap[i]);
		}
	printf("\n");
}//플레이어에게 카드나열한걸 보여주는 맵. 처음 시작시에는 카드 뒷면 '?'를 보여줌 

void show_num(int a, int b){
		c1=card_in[a]+'0';
		c2=card_in[b]+'0';
		qmap[a]=c1;
		qmap[b]=c2;
}//플레이어가 카드 짝을 맞췄을 시 '?" 를 지우고 카드 내용을 보여줌 

void reset_check (void) {
		check_card[0]=0;
		check_card[1]=0;
		card_select[0]=0;
		card_select[1]=0;
} //짝을 맞췄거나 틀렸을경우 선택한 카드를 초기화하는 함수 

void print_please(void) {
	if(ordernum==1){
		printf("\n");
		printf("두번째 카드를 골라주세요:  "); 
	}
	else{
		printf("\n");
		printf("첫번째 카드를 골라주세요: "); 
	}//지금 고르는 게 몇번째인지 보여주기 위한 함수 
}

void print_waiting(void) {
	printf("----------------\n");
	printf("  shuffling...\n");
	printf("----------------\n");
}//게임 시작시 카드 섞는것처럼 보여줌 

void change_player(void) {
	if(player==0){
		player1_score=answer;
		answer=player2_score;
		player=1;
	}
	else{
		player2_score=answer;
		answer=player1_score;
		player=0;
	}//플레이어가 짝이 맞는 카드를 고르지 못했을 경우 다른 플레이어에게 차례를 넘기는 함수 
}

void checkcard(int a, int b) {
	a=a-1;//첫번째 카드 
	b=b-1;//두번째 카드  
	if(card_in[a]==card_in[b]) {
		num1++;
		answer++;
		count++;
		printf("\n");
		printf("짝을 맞췄습니다!\n");
		printf("\n");
		printf("시도횟수: %d 맞춘횟수: %d",count, answer);
		show_num(a,b);
		reset_check();//check_card[],card_select[] 초기화 
		card_in[a]=0;//이미 맞춘 카드를 고르지 못하도록 카드내용을 0으로 설정 
		card_in[b]=0;//이미 맞춘 카드를 고르지 못하도록 카드내용을 0으로 설정 
		show_map();//현재 남은 카드 배치를 보여줌 
	}//짝이 맞을경우 카드를 뒤집어 숫자를 보여주고 check_card[],card_select[] 초기화  
	else {
		count++;
		printf("\n");
		printf("틀렸습니다 차례가 넘어갑니다.\n");
		printf("\n");
		change_player();//상대방에게 순서를 넘겨줌 
		reset_check();//check_card[],card_select[] 초기화
		printf("플레이어%d의 차례입니다.\n",player+1);
		printf("시도 횟수: %d",count);
		
	}
}//고른 두 개의 카드가 짝이 맞는지 체크하는 함수 

void sum_score(void) {
	if(player1_score>player2_score){
		printf("\n");
		printf("플레이어1이 승리하였습니다!");
		printf("\n");
	}
	else if(player1_score==player2_score){
		printf("\n");
		printf("아쉽습니다 비겼습니다...");
		printf("\n");
	}
	else {
		printf("\n");
		printf("플레이어2가 승리하였습니다!");
		printf("\n");
	}

}//다 맞춘 후 점수 계산하는 함수 

void put_num(int check) { 
	if(card_in[check-1]==0){
		printf("\n");
		printf("이미 맞춘 카드입니다.\n");
		if(card_select[0]==0){	
			ordernum=0;		
		}
		else{
			ordernum=1;
		}
	}//고른 카드가 이미 짝을 맞춘 카드인지를 체크하는 조건 문 
	else{
		if(card_select[0]==0){
			check_card[0]=card_in[check-1];
			card_select[0]=check;
			printf("\n");
			printf("첫번째 카드 내용: %d",check_card[0]);
			printf("\n");
			ordernum=1; 
		}//첫번째 카드를 고르지 않았을 경우 첫번째 카드를  card_select[0]에 카드번호를, check_card[0]에 카드 앞면을 저장 
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("이미 맞춘 카드입니다.\n");
			}//고른 카드가 이미 짝을 맞춘 카드인지를 체크하는 조건 문
			else{
				check_card[1]=card_in[check-1];
				card_select[1]=check;
				printf("\n");
				printf("두번째 카드 내용: %d",check_card[1]);
				printf("\n");
		
				if(card_select[0]==card_select[1]){
					printf("\n");
					printf("중복된 카드를 골랐습니다 다시 고르세요.\n");
					printf("\n");
					check_card[1]=0;
					card_select[1]=0;
					}			
						}//첫번째와 두번째 카드를 같은 카드를 골랐을 경우 두번째 카드 정보를 담은 check_card[1],card_select[1]을 초기화후 다시 고르도록 함 
								
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("카드 두개를 골랐습니다");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}//서로 다른 카드 두개를 골랐으면 두 카드를 비교 
		}		
	}		
}//카드를 고르는 함수 


int main(void){
	int i;
	for(i=0; i<3; i++){
		int a=rand()%12+1;
		card_off(a);
	}

	return 0;
}



















