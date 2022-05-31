# IoT 프로그래밍 프로젝트 3주차 보고서

IoT 프로그래밍 프로젝트 2조 3주차 보고서

팀장: 김진상<br>팀원: 김동현 

발표일 : 2022년 5월 30일<br>발표자: 김진상

## 2주차 활동 내용

2주차 활동 결과는 다음과 같다.

- ##### 타겟 시스템에서 작동하도록 예시 실행 프로그램을 컴파일 하여 실행 시켜보기

- ##### 카드 뒤집기 게임으로 전환

- ##### Smart4412 장치의 입출력장치에 기본 작동 방법 학습


## 1. 알고리즘 순서도 작성

![알고리즘 순서도](https://user-images.githubusercontent.com/80252681/171007720-70311687-6b1d-4270-8f1a-05c5568c8702.jpg)

## 2. 논리에 맞게 프로그램 작성

먼저, 카드 뒤집기 게임의 논리에 맞게 PC에서 작동하는 프로그램을 작성하였습니다.

```C
void map1(void) {
	int i;
	for (i = 0; i < 12; i++) {
		qmap[i] = '?';
	}
}//카드 내용을 가리기 위해 카드 뒷면으로 사용할 '?' 배열 


void card_shuffle(void) {
	srand(time(NULL));//게임을 시작할때마다 다르게 섞이도록 하기 위한 srand()함수 
	int i, j, x;
	memset(card_in, 0, sizeof(card_in));
	for (i = 1; i < 7; i++) //1~6 숫자를  
	{
		for (j = 0; j < 2; j++)//두 개의 카드에 집어 넣음 
		{
			do
			{
				x = rand() % 12;
			} while (card_in[x] != 0);

			card_in[x] = i;

		}
	}
} //12개의 카드에 1~6의 숫자를 두번씩 총 12번 넣어 카드를 섞는 코드

void show_map(void) {
	printf("\n");
	int i;
	for (i = 0; i < 12; i++) {
		if (i % 4 == 0) {
			printf("\n");
		}
		printf("%c ", qmap[i]);
	}
	printf("\n");
}//플레이어에게 카드나열한걸 보여주는 맵. 처음 시작시에는 카드 뒷면 '?'를 보여줌 
```


![1](https://user-images.githubusercontent.com/80252681/171071214-ba0fe04d-b057-4ef0-b44f-1a1707cbe9fe.png)

4x3 카드를 랜덤으로 배치하고 뒷면으로 돌립니다.



```C
void show_num(int a, int b) {
	c1 = card_in[a] + '0';
	c2 = card_in[b] + '0';
	qmap[a] = c1;
	qmap[b] = c2;
}//플레이어가 카드 짝을 맞췄을 시 '?" 를 지우고 카드 내용을 보여줌 

void reset_check(void) {
	check_card[0] = 0;
	check_card[1] = 0;
	card_select[0] = 0;
	card_select[1] = 0;
} //짝을 맞췄거나 틀렸을경우 선택한 카드를 초기화하는 함수 

void change_player(void) {
	if (player == 0) {
		player1_score = answer;
		answer = player2_score;
		player = 1;
	}
	else {
		player2_score = answer;
		answer = player1_score;
		player = 0;
	}//플레이어가 짝이 맞는 카드를 고르지 못했을 경우 다른 플레이어에게 차례를 넘기는 함수 
}
```

![2](https://user-images.githubusercontent.com/80252681/171071686-945f3e66-16de-42d3-a63b-64e62f0fcc62.png)

짝을 못 찾은 경우

![3](https://user-images.githubusercontent.com/80252681/171071877-c7910154-836a-4e66-ab0b-218e3901eb15.png)

짝을 찾은 경우

짝을 못 찾는다면 차례가 다음 플레이어로 넘어갑니다.
짝을 찾는다면 찾은 카드는 앞면으로 뒤집고 차례는 유지됩니다.

```C
void sum_score(void) {
	if (player1_score > player2_score) {
		printf("\n");
		printf("플레이어1이 승리하였습니다!");
		printf("\n");
	}
	else if (player1_score == player2_score) {
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
```

![4](https://user-images.githubusercontent.com/80252681/171071992-a7aadbb8-7cfc-4377-a69c-9a05f6881265.png)

카드를 모두 뒤집었다면 점수를 합산하여 승자를 결정합니다.

card su


## 3. DOT MATRIX START 화면 조작

카드가 4x3로 깔려 있는 모습을 연출하여 보았습니다. (ready.c)

https://user-images.githubusercontent.com/80252681/171009302-d55f3833-0401-425c-b9ad-178cbfd29168.mp4

## 4. 다음 주 계획

- 구현한 카드 뒤집기 프로그램을 타겟 시스템의 입출력 장치를 이용하여 구현해보기.
- 다른 추가할 기능을 생각해 보기 
- 다양한 기능들을 입출력장치와 연결시켜 추가할 계획.
- 

