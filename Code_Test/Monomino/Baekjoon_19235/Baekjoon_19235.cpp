#include <iostream>
#include <cstring>
using namespace std;

// 한칸짜리 블록
#define SHAP_1 1
// 가로로 긴 블록
#define SHAP_2 2
// 세로로 긴 블록
#define SHAP_3 3

int n;
int blue[4][6] = { 0, };
int green[6][4] = { 0, };
int ans = 0;


int count_blocks() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (blue[i][j] > 0) {
				count++;
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j] > 0) {
				count++;
			}
		}
	}
	return count;
}

// 연한 파란색 구역의 블록 존재여부 파악 및 쌓여있는 열의 개수 반환
int check_light_blue() {
	int check = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (blue[j][i] > 0) {
				check++;
				break;
			}
		}
	}
	return check;
}

// 연한 초록색 구역의 블록 존재여부 파악 및 쌓여있는 열의 개수 반환
int check_light_green() {
	int check = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j] > 0) {
				check++;
				break;
			}
		}
	}
	return check;
}

// 파란색 구역 블록이 파괴된 후 남아있는 블록이 아래로 내려옴
void push_blue_block() {
	bool changeBlue;
	do {
		changeBlue = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// 블록에 저장된 번호가 1 또는 2일 때
				if (blue[j][i] == SHAP_1 || blue[j][i] == SHAP_2) {
					if (blue[j][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						changeBlue = true;
					}
				}
				// 블록에 저장된 번호가 3일 때
				else if (blue[j][i] == SHAP_3) {
					if (blue[j][i + 1] == 0 && blue[j + 1][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						swap(blue[j + 1][i], blue[j + 1][i + 1]);
						changeBlue = true;
					}
					j++;
				}
			}
		}
	} while (changeBlue);
}

// 초록색 구역 블록이 파괴된 후 남아있는 블록이 아래로 내려옴
void push_green_block() {
	bool changeGreen;
	do {
		changeGreen = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// 블록에 저장된 번호가 1 또는 3일 때
				if (green[i][j] == SHAP_1 || green[i][j] == SHAP_3) {
					if (green[i + 1][j] == 0) {
						swap(green[i][j], green[i + 1][j]);
						changeGreen = true;
					}
				}
				// 블록에 저장된 번호가 2일 때
				else if (green[i][j] == SHAP_2) {
					if (green[i + 1][j] == 0 && green[i + 1][j + 1] == 0) {
						swap(green[i][j], green[i + 1][j]);
						swap(green[i][j + 1], green[i + 1][j + 1]);
						changeGreen = true;
					}
					j++;
				}
			}
		}
	} while (changeGreen);
}
// 블루에서 한 줄 이상이 완성 되면 줄 삭제 및 true 반환
// 파란색 구역에서 한 줄이 완성된 것이 존재할 시 삭제
bool break_blue() {
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;

		// 줄 완성 확인
		for (int j = 0; j < 4; j++) {
			check &= (blue[j][i] > 0);
		}
	
		// 한 줄 완성될 시 열 삭제 (초기화)
		if (check) {	
			blue[0][i] = blue[1][i] = blue[2][i] = blue[3][i] = 0;
			tetris = true;
			ans++; 
		}
	}
	return tetris;
}

// 초록에서 한 줄 이상이 완성 되면 줄 삭제 및 true 반환
// 초록색 구역에서 한 줄이 완성된 것이 존재할 시 삭제
bool break_green() {
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (green[i][j] > 0);
		}
		// 한 줄 완성될 시 열 삭제
		if (check) {
			green[i][0] = green[i][1] = green[i][2] = green[i][3] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}

// blue 의 연한 구역에 블록을 놓는 시작점
// 연한 구역에 블록이 없을 때까지만 움직이기 때문에 시작점은 연한 구역부터
void put_blue_block(int t, int x) {
	// blue 블록 놓기
	if (t == SHAP_1) {
		for (int i = 1; i < 6; i++) {
			// 마지막 칸이므로 배치하고 빠져나간다.
			if (i == 5) blue[x][i] = 1;
			// 다음칸에 블록이 있으므로 배치하고 빠져나간다.
			else if (blue[x][i + 1] > 0) {
				blue[x][i] = 1;
				break;
			}
		}
	} else if (t == SHAP_2) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) blue[x][i] = blue[x][i - 1] = 2;
			else if (blue[x][i + 1] > 0) {
				blue[x][i] = blue[x][i - 1] = 2;
				break;
			}
		}
	} else if (t == SHAP_3) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) blue[x][i] = blue[x + 1][i] = 3;
			else if (blue[x][i + 1] > 0 || blue[x + 1][i + 1] > 0) {
				blue[x][i] = blue[x + 1][i] = 3;
				break;
			}
		}
	}
}

// green 의 연한 구역에 블록을 놓는 시작점
// 연한 구역에 블록이 없을 때까지만 움직이기 때문에 시작점은 연한 구역부터
void put_green_block(int t, int y) {
	// green 블록 놓기
	if (t == SHAP_1) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = 1;
			else if (green[i + 1][y] > 0) {
				green[i][y] = 1;
				break;
			}
		}
	} else if (t == SHAP_2) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = green[i][y + 1] = 2;
			else if (green[i + 1][y] > 0 || green[i + 1][y + 1] > 0) {
				green[i][y] = green[i][y + 1] = 2;
				break;
			}
		}
	} else if (t == SHAP_3) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = green[i - 1][y] = 3;
			else if (green[i + 1][y] > 0) {
				green[i][y] = green[i - 1][y] = 3;
				break;
			}
		}
	}
}

int main(void) {
	int n;
	// 첫 줄 n 값 입력 받기
	cin >> n;

	// n번 반복
	for (int i = 0; i < n; i++) {	
		int t, x, y;

		// t, x, y 입력 받음
		cin >> t >> x >> y;

		// 파란색, 초록색 구역에 블록 배치
		put_blue_block(t, x);
		put_green_block(t, y);

		// 테트리스 완성 시 그 줄 부수고, 위에 있는 블록 내리고 반복
		while (break_blue()) {
			push_blue_block();
		}
		while (break_green()) {
			push_green_block();
		}

		int lightBlue = check_light_blue();
		if (lightBlue > 0) {
			for (int i = 5 - lightBlue; i >= 2 - lightBlue; i--) {
				for (int j = 0; j < 4; j++) {
					blue[j][i + lightBlue] = blue[j][i];
				}
			}
			for (int i = 2 - lightBlue; i < 2; i++) {
				for (int j = 0; j < 4; j++) {
					blue[j][i] = 0;
				}
			}
		}

		int lightGreen = check_light_green();
		if (lightGreen > 0) {
			for (int i = 5 - lightGreen; i >= 2 - lightGreen; i--) {
				for (int j = 0; j < 4; j++) {
					green[i + lightGreen][j] = green[i][j];
				}
			}
			for (int i = 2 - lightGreen; i < 2; i++) {
				memset(green[i], 0, sizeof(int) * 4);
			}
		}
	}

	// 파란색 출력
	cout << "파란색 타일 상황" << endl;
	int col = sizeof(blue[0]) / sizeof(int);
	int row = sizeof(blue) / sizeof(blue[0]);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << blue[i][j];
		}
		cout << endl;
	}

	// 초록색 출력
	cout << "초록색 타일 상황\n";
	int col_green = sizeof(green[0]) / sizeof(int);
	int row_green = sizeof(green) / sizeof(green[0]);

	for (int i = 0; i < row_green; i++) {
		for (int j = 0; j < col_green; j++) {
			cout << green[i][j];
		}
		cout << "\n";
	}

	cout << ans << "\n";
	cout << count_blocks();

	return 0;
}