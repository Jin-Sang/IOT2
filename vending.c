#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <string.h>
#include <asm/ioctls.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#define clcd "/dev/clcd"
#define led "/dev/led"
#define dot "/dev/dot"
#define fnd_dev	"/dev/fnd"

unsigned char rps[1][8] = {	// dot matrix에 출력을 할 옵션
	{ 0x00,0x38,0x38,0x38,0x38,0x00,0x00,0x00 }, // 초기 화면 

};


void DOT_control(int rps_col, int time_sleep) {
	int dot_d;

	dot_d = open(dot, O_RDWR);
	if (dot_d < 0) { printf("dot Error\n"); } // 예외처리

	write(dot_d, &rps[rps_col], sizeof(rps)); // 출력
	sleep(time_sleep); // 몇초동안 점등할지

	close(dot_d);
}
