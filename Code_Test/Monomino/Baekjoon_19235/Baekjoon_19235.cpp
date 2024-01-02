#include <iostream>
#include <cstring>
using namespace std;

// ��ĭ¥�� ���
#define SHAP_1 1
// ���η� �� ���
#define SHAP_2 2
// ���η� �� ���
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

// ���� �Ķ��� ������ ��� ���翩�� �ľ� �� �׿��ִ� ���� ���� ��ȯ
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

// ���� �ʷϻ� ������ ��� ���翩�� �ľ� �� �׿��ִ� ���� ���� ��ȯ
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

// �Ķ��� ���� ����� �ı��� �� �����ִ� ����� �Ʒ��� ������
void push_blue_block() {
	bool changeBlue;
	do {
		changeBlue = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// ��Ͽ� ����� ��ȣ�� 1 �Ǵ� 2�� ��
				if (blue[j][i] == SHAP_1 || blue[j][i] == SHAP_2) {
					if (blue[j][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						changeBlue = true;
					}
				}
				// ��Ͽ� ����� ��ȣ�� 3�� ��
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

// �ʷϻ� ���� ����� �ı��� �� �����ִ� ����� �Ʒ��� ������
void push_green_block() {
	bool changeGreen;
	do {
		changeGreen = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// ��Ͽ� ����� ��ȣ�� 1 �Ǵ� 3�� ��
				if (green[i][j] == SHAP_1 || green[i][j] == SHAP_3) {
					if (green[i + 1][j] == 0) {
						swap(green[i][j], green[i + 1][j]);
						changeGreen = true;
					}
				}
				// ��Ͽ� ����� ��ȣ�� 2�� ��
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
// ��翡�� �� �� �̻��� �ϼ� �Ǹ� �� ���� �� true ��ȯ
// �Ķ��� �������� �� ���� �ϼ��� ���� ������ �� ����
bool break_blue() {
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;

		// �� �ϼ� Ȯ��
		for (int j = 0; j < 4; j++) {
			check &= (blue[j][i] > 0);
		}
	
		// �� �� �ϼ��� �� �� ���� (�ʱ�ȭ)
		if (check) {	
			blue[0][i] = blue[1][i] = blue[2][i] = blue[3][i] = 0;
			tetris = true;
			ans++; 
		}
	}
	return tetris;
}

// �ʷϿ��� �� �� �̻��� �ϼ� �Ǹ� �� ���� �� true ��ȯ
// �ʷϻ� �������� �� ���� �ϼ��� ���� ������ �� ����
bool break_green() {
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (green[i][j] > 0);
		}
		// �� �� �ϼ��� �� �� ����
		if (check) {
			green[i][0] = green[i][1] = green[i][2] = green[i][3] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}

// blue �� ���� ������ ����� ���� ������
// ���� ������ ����� ���� �������� �����̱� ������ �������� ���� ��������
void put_blue_block(int t, int x) {
	// blue ��� ����
	if (t == SHAP_1) {
		for (int i = 1; i < 6; i++) {
			// ������ ĭ�̹Ƿ� ��ġ�ϰ� ����������.
			if (i == 5) blue[x][i] = 1;
			// ����ĭ�� ����� �����Ƿ� ��ġ�ϰ� ����������.
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

// green �� ���� ������ ����� ���� ������
// ���� ������ ����� ���� �������� �����̱� ������ �������� ���� ��������
void put_green_block(int t, int y) {
	// green ��� ����
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
	// ù �� n �� �Է� �ޱ�
	cin >> n;

	// n�� �ݺ�
	for (int i = 0; i < n; i++) {	
		int t, x, y;

		// t, x, y �Է� ����
		cin >> t >> x >> y;

		// �Ķ���, �ʷϻ� ������ ��� ��ġ
		put_blue_block(t, x);
		put_green_block(t, y);

		// ��Ʈ���� �ϼ� �� �� �� �μ���, ���� �ִ� ��� ������ �ݺ�
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

	// �Ķ��� ���
	cout << "�Ķ��� Ÿ�� ��Ȳ" << endl;
	int col = sizeof(blue[0]) / sizeof(int);
	int row = sizeof(blue) / sizeof(blue[0]);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << blue[i][j];
		}
		cout << endl;
	}

	// �ʷϻ� ���
	cout << "�ʷϻ� Ÿ�� ��Ȳ\n";
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