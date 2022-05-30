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
int card_in[12]; //Ä«µå ³»¿ëÀ» ´ã´Â ¹è¿­ 
int check_card[2]; // ¼±ÅÃÇÑ Ä«µå°¡ Â¦ÀÌ ¸Â´ÂÁö ´Ù¸¥Áö È®ÀÎÇÏ±â À§ÇÑ ¹è¿­ 
int check;//ÇÃ·¹ÀÌ¾î°¡ ¼±ÅÃÇÑ Ä«µå ¹øÈ£ 
int card_select[2];//ÇÃ·¹ÀÌ¾î°¡ ¼±ÅÃÇÑ Ä«µå ¹øÈ£ µÎ°³ ´ã´Â ¹è¿­ 
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
}//Ä«µå ³»¿ëÀ» °¡¸®±â À§ÇØ Ä«µå µŞ¸éÀ¸·Î »ç¿ëÇÒ '?' ¹è¿­ 
 

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
} //12°³ÀÇ Ä«µå¿¡ 1~6ÀÇ ¼ıÀÚ¸¦ µÎ¹ø¾¿ ÃÑ 12¹ø ³Ö¾î Ä«µå¸¦ ¼¯´Â ÄÚµå. srand() ÇÔ¼ö·Î ½ÃÀÛ¸¶´Ù ´Ù¸£°Ô ¼¯ÀÌ°Ô ÇÔ  

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
}//ÇÃ·¹ÀÌ¾î¿¡°Ô Ä«µå³ª¿­ÇÑ°É º¸¿©ÁÖ´Â ¸Ê. Ã³À½ ½ÃÀÛ½Ã¿¡´Â Ä«µå µŞ¸é '?'¸¦ º¸¿©ÁÜ 

void show_num(int a, int b){
		c1=card_in[a]+'0';
		c2=card_in[b]+'0';
		qmap[a]=c1;
		qmap[b]=c2;
}//ÇÃ·¹ÀÌ¾î°¡ Ä«µå Â¦À» ¸ÂÃèÀ» ½Ã '?" ¸¦ Áö¿ì°í Ä«µå ³»¿ëÀ» º¸¿©ÁÜ 

void reset_check (void) {
		check_card[0]=0;
		check_card[1]=0;
		card_select[0]=0;
		card_select[1]=0;
} //Â¦À» ¸ÂÃè°Å³ª Æ²·ÈÀ»°æ¿ì ¼±ÅÃÇÑ Ä«µå¸¦ ÃÊ±âÈ­ÇÏ´Â ÇÔ¼ö 

void print_please(void) {
	if(ordernum==1){
		printf("\n");
		printf("µÎ¹øÂ° Ä«µå¸¦ °ñ¶óÁÖ¼¼¿ä:  "); 
	}
	else{
		printf("\n");
		printf("Ã¹¹øÂ° Ä«µå¸¦ °ñ¶óÁÖ¼¼¿ä: "); 
	}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 
}

void print_waiting(void) {
	printf("----------------\n");
	printf("  shuffling...\n");
	printf("----------------\n");
}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 

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
	}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 
}

void checkcard(int a, int b) {
	a=a-1;
	b=b-1;
	if(card_in[a]==card_in[b]) {
		num1++;
		answer++;
		count++;
		printf("\n");
		printf("Â¦À» ¸ÂÃè½À´Ï´Ù!\n");
		printf("\n");
		printf("½ÃµµÈ½¼ö: %d ¸ÂÃáÈ½¼ö: %d",count,answer);
		show_num(a,b);
		reset_check();
		card_in[a]=0;
		card_in[b]=0;
		show_map();
	}
	else {
		count++;
		printf("\n");
		printf("Æ²·È½À´Ï´Ù Â÷·Ê°¡ ³Ñ¾î°©´Ï´Ù.\n");
		printf("\n");
		change_player();
		reset_check();
		printf("ÇÃ·¹ÀÌ¾î%dÀÇ Â÷·ÊÀÔ´Ï´Ù.\n",player+1);
		printf("½Ãµµ È½¼ö: %d",count);
		
	}
}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 

void sum_score(void) {
	if(player1_score>player2_score){
		printf("\n");
		printf("ÇÃ·¹ÀÌ¾î1ÀÌ ½Â¸®ÇÏ¿´½À´Ï´Ù!");
		printf("\n");
	}
	else if(player1_score==player2_score){
		printf("\n");
		printf("¾Æ½±½À´Ï´Ù ºñ°å½À´Ï´Ù...");
		printf("\n");
	}
	else {
		printf("\n");
		printf("ÇÃ·¹ÀÌ¾î2°¡ ½Â¸®ÇÏ¿´½À´Ï´Ù!");
		printf("\n");
	}

}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 

void put_num(int check) { 
	if(card_in[check-1]==0){
		printf("\n");
		printf("ÀÌ¹Ì ¸ÂÃá Ä«µåÀÔ´Ï´Ù.\n");
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
			printf("Ã¹¹øÂ° Ä«µå ³»¿ë: %d",check_card[0]);
			printf("\n");
			ordernum=1; 
		}
		else{
			if(card_in[check-1]==0){
				ordernum=1;
				printf("\n");
				printf("ÀÌ¹Ì ¸ÂÃá Ä«µåÀÔ´Ï´Ù.\n");
			}
			else{
				check_card[1]=card_in[check-1];
				card_select[1]=check;
				printf("\n");
				printf("µÎ¹øÂ° Ä«µå ³»¿ë: %d",check_card[1]);
				printf("\n");
		
				if(card_select[0]==card_select[1]){
					printf("\n");
					printf("Áßº¹µÈ Ä«µå¸¦ °ñ¶ú½À´Ï´Ù ´Ù½Ã °í¸£¼¼¿ä.\n");
					printf("\n");
					check_card[1]=0;
					card_select[1]=0;
					}			
						}			
			if(card_select[0]!=0&&card_select[1]!=0){
				printf("\n");
				printf("Ä«µå µÎ°³¸¦ °ñ¶ú½À´Ï´Ù");
				printf("\n");
				ordernum=0;
				checkcard(card_select[0],card_select[1]);
			}
		}		
	}		
}//íƒ€ê²Ÿì‹œìŠ¤í…œìœ¼ë¡œ ì˜®ê¸¸ë•Œ ìˆ˜ì •í•´ì•¼ë˜ëŠ” ì½”ë“œ 


int main(void){
	print_waiting();
	card_shuffle();
	map1();
	show_map();
	printf("\n");
	printf("ÇÃ·¹ÀÌ¾î%dÀÇ Â÷·ÊÀÔ´Ï´Ù.",player+1);
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



















