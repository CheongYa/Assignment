#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int ans = 0;
vector<vector<int>> map;
vector<vector<bool>> visit;

// 방향 상, 하, 좌, 우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void BFS(int startX, int startY)
{
	queue<pair<int, int>> q;
	q.push({ startX, startY });
	visit[startX][startY] = true;

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx >= 0 && ny >= 0 && nx < N && ny < M)
			{
				if (map[nx][ny] == 1 && visit[nx][ny] == false)
				{
					visit[nx][ny] == true;
					map[nx][ny] = map[x][y] + 1;
					q.push({ nx, ny });
				}
			}
		}
	}

	ans = map[N - 1][M - 1];
}

int main()
{
	cin >> N >> M;

	map = vector<vector<int>>(N, vector<int>(M, 0));
	visit = vector<vector<bool>>(N, vector<bool>(M, false));

	for (int i = 0; i < N; i++)
	{
		string miro_num;
		cin >> miro_num;
		for (int j = 0; j < M; j++)
		{
			map[i][j] = miro_num[j] - '0';
		}
	}

	BFS(0, 0);

	cout << ans;

	return 0;
}