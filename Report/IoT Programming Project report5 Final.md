# IOT 프로그래밍 2조 - 최종 발표 보고서

팀장: 김진상<br>팀원: 김동현 

발표일 : 2022년 6월 08일<br>발표자: 김진상

주제 : 1 VS 1 카드 뒤집기 게임

# 1. 진행 일정 및 주요 내용

- ## 1주차 활동 내용
  - 기존의 프로젝트 조사 : 리듬게임, 폭탄 해체 게임
  - 주제 선정 : 전체적인 진행 방식과 기능
  - 기존의 프로젝트와 차별성 제시 


- ## 2주차 활동 내용
  - 주제 변경 : 카드 뒤집기 게임으로 변경 (리듬 게임의 핵심인 부저가 없음)
  - 기존 프로젝트를 타겟시스템으로 이동하는 방법 학습 및 정상 작동 확인
  - 타겟 시스템의 입출력 장치 조작 방법 학습  



- ## 3주차 활동 내용
  - 알고리즘 순서도 작성 : 
  
  ![알고리즘 순서도](https://user-images.githubusercontent.com/80252681/171007720-70311687-6b1d-4270-8f1a-05c5568c8702.jpg)
  
  - PC에서 작동하는 프로그램 작성
  - 입출력 장치와 상호작용이 필요한 부분 계획
  - 추가적으로 구현할 기능 



- ## 4주차 활동 내용
  - 타겟 시스템에서 입출력장치와 상호작용하도록 프로그램 작성
  - 추가적으로 필요한 기능들 구현 작업
  - 타겟 시스템으로 프로그램을 설치하여 최종 작동 확인

- ## 최종 발표 전 활동 내용
  - 추가 기능 구상 및 구현
  - 안정적 작동 확인 및 정리



# 2. 구현된 기능 및 실제 작동

  ## 2.1 작동 순서
  1) Tact Switch를 이용하여 플레이어1과 플레이어2의 이름을 순서대로 입력 받습니다.
  2) 랜덤으로 카드 섞어 Dot matrix에 4x3 모양으로 배치합니다.
  3) player1부터 2개의 카드를 선택합니다.
  4) 맞추면 1점을 획득하고 턴은 유지됩니다.
  5) 틀리면 상대방에게 턴을 넘겨줍니다.
  6) 제한된 시간을 초과한 경우도 턴을 넘겨 줍니다.
  7) 6쌍의 카드가 모두 맞춰 질 때 까지 4,5,6을 반복합니다.
  8) 6쌍이 맞춰지면 각 플레이어가 획득한 점수에 따라 승자가 출력됩니다.

  ## 2.2 입출력 장치와 함께 구현된 기능
  
  - ### 누구의 이름을 입력하는지 알 수 있는 clcd 기능
  
  Tact Swich의 입력 순서에 따라 누구의 이름을 입력해야하는지를 표시 해줍니다.
  
  ![1](https://user-images.githubusercontent.com/80252681/172615594-f32a0951-d14e-4526-9f9d-5b61c94253bc.jpg)
  ![1](https://user-images.githubusercontent.com/80252681/172616486-b2975aef-7991-483b-9912-fba602d75697.jpg)

  - ### dot matrix, clcd와 tact swich를 이용하여 player들의 이름을 입력받는 기능
  
  Tact Swich의 입력에 따라 Dot Matrix에서 원하는 알파벳을 선택할 수 있습니다.
  
  ![a1](https://user-images.githubusercontent.com/80252681/172620831-e6323cd4-e622-4043-8295-84cb75b5453c.jpg)
  ![b1](https://user-images.githubusercontent.com/80252681/172620836-c8967472-977b-487c-8930-2a0447dc2560.jpg)
  ![c1](https://user-images.githubusercontent.com/80252681/172620837-a35f986d-e19d-401c-97ec-476f6517100c.jpg)
  ![d1](https://user-images.githubusercontent.com/80252681/172620842-317b70eb-1b1b-4b58-b205-670c3b7965ca.jpg)
  ![e1](https://user-images.githubusercontent.com/80252681/172620846-1f704626-c07e-4754-aa84-b42eae72d6c4.jpg)
  
  <img src="../img/dotm_A.gif" width="150" height="200"/><img src="../img/dotm_B.gif" width="150" height="200"/><img src="../img/dotm_C.gif" width="150" height="200"/><img src="../img/dotm_D.gif" width="150" height="200"/><img src="../img/dotm_E.gif" width="150" height="200"/>
  
  https://user-images.githubusercontent.com/80252681/172630403-81b4945e-0c5e-4f45-bb4a-dc4af297bd71.mp4
  
  Tact Swich : <br>
  4번키 : 이전 알파벳<br>
  5번키 : 알파벳 선택<br>
  6번키 : 다음 알파벳 <br>
  
  - ### 실시간 현재 점수 상황을 보여주는 clcd 기능
    
    점수를 획득하면 실시간으로 점수가 clcd에 반영됩니다.
    
    <img src="../img/scoreupload.gif" width="500" height="300"/>
    
    <img src="../img/scoreupload2.gif" width="500" height="300"/>

    
    
  - ### 이름 입력의 진행 단계를 알 수 있는 led 기능
  - ### dot matrix에 4x3 카드 랜덤 배치 기능
  - ### tact switch를 이용하여 원하는 카드를 선택할 수 있는 기능
  - ### 카드를 고르면 고른 카드의 숫자를 dot matrix에서 확인 가능한 기능
  - ### dot matrix에서 고른 2개의 카드가 맞는지 아닌지 출력되는 기능( 표정 출력) 
  - ### 해당 턴의 타이머가 나타나는 FND 기능
  - ### 현재 누구의 턴인지를 알 수 있는 led 기능
  - ### 짝이 맞춰진 카드 쌍은 실시간으로 dot matrix에서 사라지는 기능 
  - ### 6쌍이 맞춰지면 승자가 lcd에 출력되는 기능
  - ### dot matrix에 전광판 출력되는 기능


  ## 2. 3 작동 실행 영상


# 3. 독창성, 창의성, 독창성
  - ### 동시에 4개의 장치에 접근하는 기능 
  ```C
  gettimeofday(&dotst, NULL);
	gettimeofday(&timest, NULL);
		
	while (num1 < 6) // 카드쌍이 6개가 맞처질 때까지 반복
	{

		if (dot_d == 0) {
			dot_d = open(dot, O_RDWR);
		}
		gettimeofday(&dotend, NULL);

		write(dot_d, &rps, sizeof(rps));

		if ((dotend.tv_usec - dotst.tv_usec > 100000) || (dotend.tv_sec > dotst.tv_sec && (dotend.tv_usec + 1000000 - dotst.tv_usec > 100000)))
		{
			dot_d = close(dot_d);
			if (tact == 0)     //tact switch에 접근하지 않았을 때 open
			{
				tact = open(tact_d, O_RDWR);
			}
			gettimeofday(&tactst, NULL);
			while (1) {
				gettimeofday(&tactend, NULL);
				read(tact, &t, sizeof(t));
				switch (t) {
				case KEY_NUM1:
					printf("%d", 1);
					put_num(1);
					break;
				case KEY_NUM2:
					printf("%d", 2);
					put_num(2);
					break;
				case KEY_NUM3:
					printf("%d", 3);
					put_num(3);
					break;
				case KEY_NUM4:
					printf("%d", 4);
					put_num(4);
					break;
				case KEY_NUM5:
					printf("%d", 5);
					put_num(5);
					break;
				case KEY_NUM6:
					printf("%d", 6);
					put_num(6);
					break;
				case KEY_NUM7:
					printf("%d", 7);
					put_num(7);
					break;
				case KEY_NUM8:
					printf("%d", 8);
					put_num(8);
					break;
				case KEY_NUM9:
					printf("%d", 9);
					put_num(9);
					break;
				case KEY_NUM10:
					printf("%d", 10);
					put_num(10);
					break;
				case KEY_NUM11:
					printf("%d", 11);
					put_num(11);
					break;
				case KEY_NUM12:
					printf("%d", 12);
					put_num(12);
					break;
				}
				if ((tactend.tv_usec - tactst.tv_usec > 100000) || (tactend.tv_sec > tactst.tv_sec && (tactend.tv_usec + 1000000 - tactst.tv_usec > 100000)) || t)
				{
					tact = close(tact);
					
					gettimeofday(&ledst, NULL);
					if(dev==0){
						dev = open(led_dev, O_RDWR);
					}
					while(1){
						led_player(player);
					gettimeofday(&ledend, NULL);
					
					if ((ledend.tv_usec - ledst.tv_usec > 100000) || (ledend.tv_sec > ledst.tv_sec && (ledend.tv_usec + 1000000 - ledst.tv_usec > 100000))){
						dev=close(dev);
						gettimeofday(&fndst, NULL);
						fnd_fd = open(fnd_dev, O_RDWR);
						gettimeofday(&timeend, NULL);
						
						if ((timeend.tv_usec - timest.tv_usec > 1000000)|| (ledend.tv_sec > ledst.tv_sec && (ledend.tv_usec + 1000000 - ledst.tv_usec > 100000))){
							gettimeofday(&timest, NULL);
							timer--;
							printf("%d\n", timer);
							
							if (timer == 0){
								timer = 5;
								change_player();
							}
						}
						
						while(1){
							unsigned char FND_DATA_TBL[] = {
								0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,
								0x83,0xC6,0xA1,0x86,0x8E,0xC0,0xF9,0xA4,0xB0,0x99,0x89
									};
							unsigned char fnd_num[4];

							fnd_num[0] = FND_DATA_TBL[0];
							fnd_num[1] = FND_DATA_TBL[0];
							fnd_num[2] = FND_DATA_TBL[0];
							fnd_num[3] = FND_DATA_TBL[timer];
							write(fnd_fd, &fnd_num, sizeof(fnd_num));
							gettimeofday(&fndend, NULL);
							if ((fndend.tv_usec - fndst.tv_usec > 100000) || (fndend.tv_sec > fndst.tv_sec && (fndend.tv_usec + 1000000 - fndst.tv_usec > 100000))) {
                    					fnd_fd = close(fnd_fd);
                   					 break;
                					}							
						}

           				break;
					}

					}
					break;
				}
			}
			gettimeofday(&dotst, NULL);
		}

  
  ```
  - ### 타이머 시간 측정 부분
  - ### 스코어 판 문자열 만드는 거
  - ### 여러가지 예외 처리 ( 중복 선택 및 뒤집어진 카드 선택 )?
  - ### 맞춘 도트 없애기

# 4. 참고 자료 
