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
int card_in[12]; //ī�� ������ ��� �迭 
int check_card[2]; // ������ ī�尡 ¦�� �´��� �ٸ��� Ȯ���ϱ� ���� �迭 
int check;//�÷��̾ ������ ī�� ��ȣ 
int card_select[2];//�÷��̾ ������ ī�� ��ȣ �ΰ� ��� �迭 
int ordernum; //���� ������ ī�尡 ù��° ���� �ι�°���� Ȯ��
int count; //�õ�Ƚ��  
int answer;//����Ƚ��  
int num1;//ī�� 12�� �ٸ����� �� ������ �����ϵ��� �� 
int player1_score;//�÷��̾�1 ���� 
int player2_score; //�÷��̾�2 ���� 
int player;//�� �÷��̾� ���� �ϱ� ���� ���� 

char c1,c2; //������ �� ȭ�鿡 ī�� ������ �����ֱ� ���� ���� 
char qmap[12];//ī�� �޸� 
bool bools=true;// while �Լ� �����ϱ� ���� ������ 

unsigned char rps[1][8] = {	// dot matrix
	{ 0x00,0x54,0x00,0x54,0x00,0x54,0x00,0x54 }, // �ʱⰪ 

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
}//ī�� ������ ������ ���� ī�� �޸����� ����� '?' �迭 
 

void card_shuffle(void) {
	srand(time(NULL));//������ �����Ҷ����� �ٸ��� ���̵��� �ϱ� ���� srand()�Լ� 
	int i,j,x;
	memset(card_in,0,sizeof(card_in));
	for(i=1; i<7; i++) //1~6 ���ڸ�  
	{
		for(j=0; j<2; j++)//�� ���� ī�忡 ���� ���� 
		{
			do
			{
				x=rand()%12;
			} while (card_in[x] != 0);
			
			card_in[x]=i;

		}
	}
} //12���� ī�忡 1~6�� ���ڸ� �ι��� �� 12�� �־� ī�带 ���� �ڵ�

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
	}//���� ������ �� ���°���� �����ֱ� ���� �Լ� 
}

void print_waiting(void) {
	printf("----------------\n");
	printf("  shuffling...\n");
	printf("----------------\n");
}//���� ���۽� ī�� ���°�ó�� ������ 

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
	}//�÷��̾ ¦�� �´� ī�带 ������ ������ ��� �ٸ� �÷��̾�� ���ʸ� �ѱ�� �Լ� 
}

void checkcard(int a, int b) {
	a=a-1;//ù��° ī�� 
	b=b-1;//�ι�° ī��  
	if(card_in[a]==card_in[b]) {
		num1++;
		answer++;
		count++;
		printf("\n");
		printf("¦�� ������ϴ�!\n");
		printf("\n");
		printf("�õ�Ƚ��: %d ����Ƚ��: %d",count, answer);
		show_num(a,b);
		reset_check();//check_card[],card_select[] �ʱ�ȭ 
		card_in[a]=0;//�̹� ���� ī�带 ������ ���ϵ��� ī�峻���� 0���� ���� 
		card_in[b]=0;//�̹� ���� ī�带 ������ ���ϵ��� ī�峻���� 0���� ���� 
		show_map();//���� ���� ī�� ��ġ�� ������ 
	}//¦�� ������� ī�带 ������ ���ڸ� �����ְ� check_card[],card_select[] �ʱ�ȭ  
	else {
		count++;
		printf("\n");
		printf("Ʋ�Ƚ��ϴ� ���ʰ� �Ѿ�ϴ�.\n");
		printf("\n");
		change_player();//���濡�� ������ �Ѱ��� 
		reset_check();//check_card[],card_select[] �ʱ�ȭ
		printf("�÷��̾�%d�� �����Դϴ�.\n",player+1);
		printf("�õ� Ƚ��: %d",count);
		
	}
}//���� �� ���� ī�尡 ¦�� �´��� üũ�ϴ� �Լ� 

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

}//�� ���� �� ���� ����ϴ� �Լ� 

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
	}//���� ī�尡 �̹� ¦�� ���� ī�������� üũ�ϴ� ���� �� 
	else{
		if(card_select[0]==0){
			check_card[0]=card_in[check-1];
			card_select[0]=check;
			printf("\n");
			printf("ù��° ī�� ����: %d",check_card[0]);
			printf("\n");
			ordernum=1; 
		}//ù��° ī�带 ������ �ʾ��� ��� ù��° ī�带  card_select[0]�� ī���ȣ��, check_card[0]�� ī�� �ո��� ���� 
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("�̹� ���� ī���Դϴ�.\n");
			}//���� ī�尡 �̹� ¦�� ���� ī�������� üũ�ϴ� ���� ��
			else{
				check_card[1]=card_in[check-1];
				card_select[1]=check;
				printf("\n");
				printf("�ι�° ī�� ����: %d",check_card[1]);
				printf("\n");
		
				if(card_select[0]==card_select[1]){
					printf("\n");
					printf("�ߺ��� ī�带 ������ϴ� �ٽ� ��������.\n");
					printf("\n");
					check_card[1]=0;
					card_select[1]=0;
					}			
						}//ù��°�� �ι�° ī�带 ���� ī�带 ����� ��� �ι�° ī�� ������ ���� check_card[1],card_select[1]�� �ʱ�ȭ�� �ٽ� �������� �� 
								
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("ī�� �ΰ��� ������ϴ�");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}//���� �ٸ� ī�� �ΰ��� ������� �� ī�带 �� 
		}		
	}		
}//ī�带 ������ �Լ� 


int main(void){
	int i;
	for(i=0; i<3; i++){
		int a=rand()%12+1;
		card_off(a);
	}

	return 0;
}


















