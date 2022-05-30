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
//#include <string.h>
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
int ordernum;
int count;
int answer;
int num1;
int player1_score;
int player2_score; 
int player;

char c1,c2;
char qmap[12];
bool bools=true;

void map1(void) {
	int i;
	for (i=0; i<12; i++){
		qmap[i]='?';
	}
}//카드 내용을 가리기 위해 카드 뒷면으로 사용할 '?' 배열 
 

void card_shuffle(void) {
	srand(time(NULL));
	int i,j,x;
	memset(card_in,0,sizeof(card_in));
	for(i=1; i<7; i++)
	{
		for(j=0; j<2; j++)
		{
			do
			{
				x=rand()%12;
			} while (card_in[x] != 0);
			
			card_in[x]=i;

		}
	}
} //12개의 카드에 1~6의 숫자를 두번씩 총 12번 넣어 카드를 섞는 코드. srand() 함수로 시작마다 다르게 섞이게 함  

void show_map(void) {
	printf("\n");
	int i;
	for (i=0; i<12; i++){
		if(i%4==0){
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
	}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 
}

void print_waiting(void) {
	printf("----------------\n");
	printf("  shuffling...\n");
	printf("----------------\n");
}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 

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
	}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 
}

void checkcard(int a, int b) {
	a=a-1;
	b=b-1;
	if(card_in[a]==card_in[b]) {
		num1++;
		answer++;
		count++;
		printf("\n");
		printf("짝을 맞췄습니다!\n");
		printf("\n");
		printf("시도횟수: %d 맞춘횟수: %d",count,answer);
		show_num(a,b);
		reset_check();
		card_in[a]=0;
		card_in[b]=0;
		show_map();
	}
	else {
		count++;
		printf("\n");
		printf("틀렸습니다 차례가 넘어갑니다.\n");
		printf("\n");
		change_player();
		reset_check();
		printf("플레이어%d의 차례입니다.\n",player+1);
		printf("시도 횟수: %d",count);
		
	}
}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 

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

}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 

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

	}
	else{
		if(card_select[0]==0){
			check_card[0]=card_in[check-1];
			card_select[0]=check;
			printf("\n");
			printf("첫번째 카드 내용: %d",check_card[0]);
			printf("\n");
			ordernum=1; 
		}
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("이미 맞춘 카드입니다.\n");
			}
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
						}			
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("카드 두개를 골랐습니다");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}
		}		
	}		
}//���寃잛떆�뒪�뀥�쑝濡� �삷湲몃븣 �닔�젙�빐�빞�릺�뒗 肄붾뱶 


int main(void){
	print_waiting();
	card_shuffle();
	map1();
	show_map();
	printf("\n");
	printf("플레이어%d의 차례입니다.",player+1);
	printf("\n");
	while(bools)
	{
		
		int c;
		print_please();
		scanf("%d",&c);
		switch(c){
			case(1):{
				put_num(1);
				break;
			}
			case(2):{
				put_num(2);
				break;
			}
			case(3):{
				put_num(3);
				break;
			}
			case(4):{
				put_num(4);
				break;
			}
			case(5):{
				put_num(5);
				break;
			}	
			case(6):{
				put_num(6);
				break;
			}
			case(7):{
				put_num(7);
				break;
			}
			case(8):{
				put_num(8);
				break;
			}
			case(9):{
				put_num(9);
				break;
			}
			case(10):{
				put_num(10);
				break;
			}
			case(11):{
				put_num(11);
				break;
			}	
			case(12):{
				put_num(12);
				break;
			}
		}
		if(num1==6){
			bools=false;
		}
		sleep(1);
	}
	sum_score();

	return 0;
}



















