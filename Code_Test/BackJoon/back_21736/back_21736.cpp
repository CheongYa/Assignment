#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m; //가로, 세로
int startX, startY; //I의 시작 위치
int cnt = 0; //만난 사람의 명 수
vector<vector<char>> map;
vector<vector<bool>> visit;

// 방향 상, 하, 좌, 우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void bfs()
{
	queue<pair<int, int>> q; //bfs를 위한 queue

	q.push({ startX, startY });
	visit[startX][startY] = true;

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visit[nx][ny])
			{
				if (map[nx][ny] == 'P')
					cnt++;
				if (map[nx][ny] == 'P' || map[nx][ny] == 'O')
				{
					visit[nx][ny] = true;
					q.push({ nx, ny });
				}
			}
		}
	}
}

int main()
{
	cin >> n >> m;

	map = vector<vector<char>> (n, vector<char>(m));
	visit = vector<vector<bool>>(n, vector<bool>(m, false));
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'I')
			{
				startX = i;
				startY = j;
			}
		}
	}

	bfs();

	if (cnt > 0)
		cout << cnt << '\n';
	else
		cout << "TT\n";

	return 0;
}
