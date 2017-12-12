#include "Altino.h"
#include <stdio.h>

//ver1.1 : 방향함수와 배열함수 추가 완료.

SensorData sdata; //센서를 이용하기 위한 선언

int M[115][115]; // 궤적을 출력하기 위해 2차원 배열을 만들어 줌.
int D = 80000; // 현재 방향값을 보조해줄 값
int x = 85; // 현재 위치 x
int y = 55; // 현재 위치 y
int c = 0; // 궤적의 간격을 카운터 해줌


int direct() { // 현재 방향을 계산해서 2차원 배열에 ■을 찍어줌

	if (D % 8000 >= 0 && D % 8000 < 1000) { //북쪽으로 갈 경우

		y = y - 1;
		M[y][x] = "■";


	}

	if (D % 8000 >= 1000 && D % 8000 < 2000) { //북동쪽으로 갈 경우


		y = y - 1;
		x = x + 1;
		M[y][x] = "■";


	}


	if (D % 8000 >= 2000 && D % 8000 < 3000) { //동쪽으로 갈 경우


		x = x + 1;
		M[y][x] = "■";


	}

	if (D % 8000 >= 3000 && D % 8000 < 4000) { //동남쪽으로 갈 경우


		y = y + 1;
		x = x + 1;
		M[y][x] = "■";

	}

	if (D % 8000 >= 4000 && D % 8000 < 5000) { //남쪽으로 갈 경우


		y = y + 1;
		M[y][x] = "■";

	}

	if (D % 8000 >= 5000 && D % 8000 < 6000) { //남서쪽으로 갈 경우


		y = y + 1;
		x = x - 1;
		M[y][x] = "■";


	}


	if (D % 8000 >= 6000 && D % 8000 < 7000) { //서쪽으로 갈 경우


		x = x - 1;
		M[y][x] = "■";


	}

	if (D % 8000 >= 7000 && D % 8000 < 8000) { //북서쪽으로 갈 경우


		x = x - 1;
		y = y - 1;
		M[y][x] = "■";

	}

}

int main() {

	Open(szPort); // 블루투스 연결

Sound(44); delay(500); Sound(0); delay(100); Sound(44); delay(500); Sound(0); delay(100); Sound(46); delay(500); Sound(0); delay(100); Sound(46); delay(500); Sound(0); delay(100);Sound(44); delay(500); Sound(0); delay(100); Sound(44); delay(500); Sound(0); delay(100);Sound(41); delay(1000); Sound(0); delay(100);Sound(44); delay(500); Sound(0); delay(100); Sound(41); delay(500); Sound(0); delay(100);Sound(39);
	int i = 0; // 2차원 배열을 위해 i와 j를 선언함
	int j = 0;


	while (i <= 114) {


		while (j <= 114) { // 모든 2차월 배열을 흰 공간으로 채워줌


			M[i][j] = "□";

			j = j + 1;

		}

		j = 0;
		i = i + 1;

	}



	while (1) {

		Sendbuf[21] = 10;
		sdata = Sensor(1); // 센서값을 부르기 위한 함수

		if (sdata.IRSensor[2]>16) { // [2]번 센서와 벽의 거리가 약 3CM정도 보다 가까우면 좌회전


			Steering(1); //좌회전
			D = D - 36; //방향 각도 -35만큼 왼쪽으로

			Go(290, 290); //뒷바퀴 속도 290,290

		}

		if (sdata.IRSensor[2] <= 16 && sdata.IRSensor[2]>8) { // [2]번 센서와 벽의 거리가 약 3~5CM일경우 직진


			Steering(2); //전진
			D = D + 0; // 방향 각도 변화 없이 고정

			Go(290, 290); //뒷바퀴 속도 290,290

		}

		if (sdata.IRSensor[2] <= 8) { // [2]번 센서와 벽의 거리가 약 5CM일경우 벽에 붙기 위해 우회전


			Steering(3); //우회전
			D = D + 36; // 방향 각도 +35만큼 오른쪽으로

			Go(290, 290); // 뒷바퀴 속도 290,290

		}

		if (c == 3) { // C의 값이 낮을수로 더 촘촘하게 궤적을 기록. 하지만 오버플로우 발생 가능.

			direct(); // 현재의 방향으로 2차원배열에 기록하는 함수 direct();를 호출한다.
			c = 0;

		}

		c = c + 1;

		if (sdata.IRSensor[4] >= 600) { // 알티노 주행의 종료 조건 IR [4번] 센서를 손으로 잡는다.

			break;
		}


	}

	i = 0;
	j = 0; // i와 j값 초기화.

	while (i <= 114) { // 지금까지 2차원 배열에 기록했던 궤적들을 CMD 콘솔창에 출력 한다.


		while (j <= 114) {

			printf("%s", M[i][j]);


			j = j + 1;

		}
		printf("\n");
		j = 0;
		i = i + 1;

	}

	Close(); //알티노와의 연결을 끊는다.

	return 0;

}
