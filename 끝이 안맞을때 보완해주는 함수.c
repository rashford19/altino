#include <stdio.h> //끝이 안맞을때 서로 이어주는 함수.

int l = 0; // 기울기

int main() {


	if (x != 85) {

		l = (55 - y) / (85 - x);

	}

	if (x<85) {

		while (x<85) {

			M[y][x] = "■";

			x = x + 1;
			y = y + l;

		}
	}

	if (x>85) {

		while (x>85) {

			M[y][x] = "■";

			x = x - 1;
			y = y + l;

		}
	}

	if (x == 85) {

		if (y>55) {
			while (y>55) {

				M[y][x] = "■";
				y = y - 1;
			}
		}

		if (y<55) {
			while (y<55) {

				M[y][x] = "■";
				y = y + 1;
			}
		}

	}

}
