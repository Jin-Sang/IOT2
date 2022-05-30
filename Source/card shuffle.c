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
int card_in[12]; //ī�� ������ ��� �迭 
int check_card[2]; // ������ ī�尡 ¦�� �´��� �ٸ��� Ȯ���ϱ� ���� �迭 
int check;//�÷��̾ ������ ī�� ��ȣ 
int card_select[2];//�÷��̾ ������ ī�� ��ȣ �ΰ� ��� �迭 
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
}//ī�� ������ ������ ���� ī�� �޸����� ����� '?' �迭 
 

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
} //12���� ī�忡 1~6�� ���ڸ� �ι��� �� 12�� �־� ī�带 ���� �ڵ�. srand() �Լ��� ���۸��� �ٸ��� ���̰� ��  

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
}//�÷��̾�� ī�峪���Ѱ� �����ִ� ��. ó�� ���۽ÿ��� ī�� �޸� '?'�� ������ 

void show_num(int a, int b){
		c1=card_in[a]+'0';
		c2=card_in[b]+'0';
		qmap[a]=c1;
		qmap[b]=c2;
}//�÷��̾ ī�� ¦�� ������ �� '?" �� ����� ī�� ������ ������ 

void reset_check (void) {
		check_card[0]=0;
		check_card[1]=0;
		card_select[0]=0;
		card_select[1]=0;
} //¦�� ����ų� Ʋ������� ������ ī�带 �ʱ�ȭ�ϴ� �Լ� 

void print_please(void) {
	if(ordernum==1){
		printf("\n");
		printf("�ι�° ī�带 ����ּ���:  "); 
	}
	else{
		printf("\n");
		printf("ù��° ī�带 ����ּ���: "); 
	}//타겟시스템으로 옮길때 수정해야되는 코드 
}

void print_waiting(void) {
	printf("----------------\n");
	printf("  shuffling...\n");
	printf("----------------\n");
}//타겟시스템으로 옮길때 수정해야되는 코드 

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
	}//타겟시스템으로 옮길때 수정해야되는 코드 
}

void checkcard(int a, int b) {
	a=a-1;
	b=b-1;
	if(card_in[a]==card_in[b]) {
		num1++;
		answer++;
		count++;
		printf("\n");
		printf("¦�� ������ϴ�!\n");
		printf("\n");
		printf("�õ�Ƚ��: %d ����Ƚ��: %d",count,answer);
		show_num(a,b);
		reset_check();
		card_in[a]=0;
		card_in[b]=0;
		show_map();
	}
	else {
		count++;
		printf("\n");
		printf("Ʋ�Ƚ��ϴ� ���ʰ� �Ѿ�ϴ�.\n");
		printf("\n");
		change_player();
		reset_check();
		printf("�÷��̾�%d�� �����Դϴ�.\n",player+1);
		printf("�õ� Ƚ��: %d",count);
		
	}
}//타겟시스템으로 옮길때 수정해야되는 코드 

void sum_score(void) {
	if(player1_score>player2_score){
		printf("\n");
		printf("�÷��̾�1�� �¸��Ͽ����ϴ�!");
		printf("\n");
	}
	else if(player1_score==player2_score){
		printf("\n");
		printf("�ƽ����ϴ� �����ϴ�...");
		printf("\n");
	}
	else {
		printf("\n");
		printf("�÷��̾�2�� �¸��Ͽ����ϴ�!");
		printf("\n");
	}

}//타겟시스템으로 옮길때 수정해야되는 코드 

void put_num(int check) { 
	if(card_in[check-1]==0){
		printf("\n");
		printf("�̹� ���� ī���Դϴ�.\n");
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
			printf("ù��° ī�� ����: %d",check_card[0]);
			printf("\n");
			ordernum=1; 
		}
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("�̹� ���� ī���Դϴ�.\n");
			}
			else{
				check_card[1]=card_in[check-1];
				card_select[1]=check;
				printf("\n");
				printf("�ι�° ī�� ����: %d",check_card[1]);
				printf("\n");
		
				if(card_select[0]==card_select[1]){
					printf("\n");
					printf("�ߺ��� ī�带 ������ϴ� �ٽ� ������.\n");
					printf("\n");
					check_card[1]=0;
					card_select[1]=0;
					}			
						}			
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("ī�� �ΰ��� ������ϴ�");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}
		}		
	}		
}//타겟시스템으로 옮길때 수정해야되는 코드 


int main(void){
	print_waiting();
	card_shuffle();
	map1();
	show_map();
	printf("\n");
	printf("�÷��̾�%d�� �����Դϴ�.",player+1);
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



















