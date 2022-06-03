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
int ordernum; //���� ���� ī�尡 ù��° ���� �ι�°���� Ȯ��
int count; //�õ�Ƚ��  
int answer;//����Ƚ��  
int num1;//ī�� 12�� �ٸ����� �� ������ �����ϵ��� �� 
int player1_score;//�÷��̾�1 ���� 
int player2_score; //�÷��̾�2 ���� 
int player;//�� �÷��̾� ���� �ϱ� ���� ���� 
int dot_d;
char c1,c2; //������ �� ȭ�鿡 ī�� ������ �����ֱ� ���� ���� 
char qmap[12];//ī�� �޸� 
bool bools=true;// while �Լ� �����ϱ� ���� ���� 
static char tactswDev[] = "/dev/tactsw";
static int  tactswFd = (-1);
static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

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
	}
	else if(a1<7){
		back1=rps[0][3];
	}
	else if(a1<10){
		back1=rps[0][5];
	}
	else {
		back1=rps[0][7];
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

int FND_Out(int a, int b, int c, int d) {

	unsigned char FND_DATA_TBL[] = {
			0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,
			0x83,0xC6,0xA1,0x86,0x8E,0xC0,0xF9,0xA4,0xB0,0x99,0x89
	};

	int fnd_fd = 0;

	unsigned char fnd_num[4];

	fnd_num[0] = FND_DATA_TBL[a];
	fnd_num[1] = FND_DATA_TBL[b];
	fnd_num[2] = FND_DATA_TBL[c];
	fnd_num[3] = FND_DATA_TBL[d];

	fnd_fd = open(fnd_dev, O_RDWR);

	if (fnd_fd < 0) {
		printf("Can't Open Device\n");
	}
	write(fnd_fd, &fnd_num, sizeof(fnd_num));
	sleep(1);
	close(fnd_fd);
}

void DOT_control(int rps_col, int time_sleep) {

	dot_d = open(dot, O_RDWR);
	if (dot_d < 0) { printf("dot Error\n"); } // ���� 

	write(dot_d, &rps[rps_col], sizeof(rps)); // �Է� 

}

void print_lcd(char* av) {

	int n;
	char        buf[MAXCHR];

	lcdFd = open(lcdDev, O_RDWR);
	if (lcdFd < 0) {
		fprintf(stderr, "cannot open LCD (%d)", lcdFd);
		exit(2);
	}

	memset(buf, 0, sizeof(buf));

	n = strlen(av);

	memcpy(buf, av, n);

	write(lcdFd, buf, MAXCHR);

	close(lcdFd);

}

unsigned char tactsw_get(int tmo)
{
	unsigned char b;

	if (tmo) {
		if (tmo < 0)
			tmo = ~tmo * 1000;
		else
			tmo *= 1000000;

		while (tmo > 0) {
			usleep(10000);
			read(tactswFd, &b, sizeof(b));
			if (b) return(b);
			tmo -= 10000;
		}
		return(-1);
	}
	else {

		read(tactswFd, &b, sizeof(b));
		return(b);
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
	}//���� ���� �� ���°���� �����ֱ� ���� �Լ� 
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
	}//�÷��̾ ¦�� �´� ī�带 ���� ������ ��� �ٸ� �÷��̾�� ���ʸ� �ѱ�� �Լ� 
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
		card_off(a+1);
		card_off(b+1);
		show_num(a,b);
		reset_check();//check_card[],card_select[] �ʱ�ȭ 
		card_in[a]=0;//�̹� ���� ī�带 ���� ���ϵ��� ī�峻���� 0���� ���� 
		card_in[b]=0;//�̹� ���� ī�带 ���� ���ϵ��� ī�峻���� 0���� ���� 
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
}//�� �� ���� ī�尡 ¦�� �´��� üũ�ϴ� �Լ� 

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
	}//�� ī�尡 �̹� ¦�� ���� ī�������� üũ�ϴ� ���� �� 
	else{
		if(card_select[0]==0){
			check_card[0]=card_in[check-1];
			card_select[0]=check;
			printf("\n");
			printf("ù��° ī�� ����: %d", check_card[0]);
			printf("\n");
			print_lcd("First card: ");
			ordernum=1; 
		}//ù��° ī�带 ���� �ʾ��� ��� ù��° ī�带  card_select[0]�� ī���ȣ��, check_card[0]�� ī�� �ո��� ���� 
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("�̹� ���� ī���Դϴ�.\n");
			}//�� ī�尡 �̹� ¦�� ���� ī�������� üũ�ϴ� ���� ��
			else{
				check_card[1]=card_in[check-1];
				card_select[1]=check;
				printf("\n");
				printf("�ι�° ī�� ����: %d",check_card[1]);
				printf("\n");
				print_lcd("Second card: ");
		
				if(card_select[0]==card_select[1]){
					printf("\n");
					printf("�ߺ��� ī�带 ������ϴ� �ٽ� ������.\n");
					printf("\n");
					check_card[1]=0;
					card_select[1]=0;
					}			
						}//ù��°�� �ι�° ī�带 ���� ī�带 ����� ��� �ι�° ī�� ������ ���� check_card[1],card_select[1]�� �ʱ�ȭ�� �ٽ� ������ �� 
								
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("ī�� �ΰ��� ������ϴ�");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}//���� �ٸ� ī�� �ΰ��� ������� �� ī�带 �� 
		}		
	}		
}//ī�带 ���� �Լ� 

void dot_num(int choice) {
	unsigned char c[10][8] = { {0x3c,0x42,0x42,0x42,0x42,0x42,0x3c,0x00},
								{0x18,0x28,0x08,0x08,0x08,0x08,0x3c,0x00},
								{0x18,0x24,0x24,0x04,0x08,0x10,0x3c,0x00},
								{0x18,0x24,0x04,0x18,0x04,0x24,0x18,0x00},
								{0x08,0x18,0x28,0x48,0xfc,0x08,0x08,0x00},
								{0x2c,0x20,0x20,0x18,0x04,0x24,0x18,0x00},
								{0x18,0x24,0x20,0x38,0x24,0x24,0x18,0x00},
								{0x3c,0x04,0x04,0x08,0x10,0x10,0x10,0x00},
								{0x18,0x24,0x24,0x18,0x24,0x24,0x18,0x00},
								{0x18,0x24,0x24,0x1c,0x04,0x04,0x18,0x00}, };
	if ((dot_d = open(dot, O_RDWR)) < 0){
		printf("Can't Open\n");
		exit(0);
	}
	write(dot_d, &c[choice], sizeof(c[choice]));
	sleep(1);
	close(dot_d);


}

int main(void){
	unsigned char c;
	unsigned char d;
	int dev;
	
	if ((tactswFd = open(tactswDev, O_RDONLY)) < 0) {         // KEY open
		perror("open faile /dev/key");
		exit(-1);
	}
	printf("tact opend");

	dev = open(led_dev, O_RDWR);
	if (dev < 0) {
		fprintf(stderr, "cannot open LED Device (%d)", dev);
		exit(2);
	}

	print_waiting();
	card_shuffle();
	map1();
	show_map();
	
	printf("\n");
	printf("�÷��̾�%d�� �����Դϴ�.",player+1);
	printf("\n");
	DOT_control(0, 2);	
	while(bools)
	{	
		DOT_control(0,2);
		print_please();	
		d = tactsw_get(10);
		switch(d){
			case KEY_NUM1:
				printf("%d",1);
				put_num(1);
				dot_num(1);
				break;
			case KEY_NUM2:
				printf("%d",2);
				put_num(2);
				dot_num(2);
				break;
			case KEY_NUM3:
				printf("%d",3);
				put_num(3);
				dot_num(3);
				break;
			case KEY_NUM4:
				printf("%d",4);
				put_num(4);
				dot_num(4);
				break;
			case KEY_NUM5:
				printf("%d",5);
				put_num(5);
				dot_num(5);
				break;	
			case KEY_NUM6:
				printf("%d",6);
				put_num(6);
				dot_num(6);
				break;
			case KEY_NUM7:
				printf("%d",7);
				put_num(7);
				dot_num(7);
				break;
			case KEY_NUM8:
				printf("%d",8);
				put_num(8);
				dot_num(8);
				break;
			case KEY_NUM9:
				printf("%d",9);
				put_num(9);
				dot_num(9);
				break;
			case KEY_NUM10:
				printf("%d",10);
				put_num(10);
				dot_num(0);
				break;
			case KEY_NUM11:
				printf("%d",11);
				put_num(11);
				dot_num(0);
				break;
			case KEY_NUM12:
				printf("%d",12);
				put_num(12);
				dot_num(0);
				break;
			}
		if(num1==6){
			bools=false;
		}
		sleep(1);
	}
	sum_score();

	return 0;
}
