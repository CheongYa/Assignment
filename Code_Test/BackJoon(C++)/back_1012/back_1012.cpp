#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int t, m, n, k; //경우의 수, 가로, 세로, 배추 개수, 배추 좌표
vector<vector<int>> fild;
vector<vector<bool>> visit;

// 방향 상, 하, 좌, 우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void BFS(int startX, int startY)
{
	queue<pair<int, int>> q;
	q.push({ startX, startY });
	visit[startX][startY] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx >= 0 && nx < m && ny >= 0 && ny < n && fild[nx][ny] == 1 && !visit[nx][ny]) {
				visit[nx][ny] = true;
				q.push({ nx, ny });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	while (t--) {
		cin >> m >> n >> k;
		fild = vector<vector<int>>(m, vector<int>(n, 0));
		visit = vector<vector<bool>>(m, vector<bool>(n, false));

		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			fild[x][y] = 1;
		}

		int cnt = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (fild[i][j] == 1 && !visit[i][j]) {
					BFS(i, j);
					cnt++;
				}
			}
		}
		cout << cnt << '\n';
	}

	return 0;
}

