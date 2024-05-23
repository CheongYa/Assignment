#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m; //가로, 세로
int startX, startY; //I의 시작 위치
int cnt = 0; //만난 사람의 명 수

// 방향 상, 하, 좌, 우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void bfs(vector<vector<char>>& map)
{
	queue<pair<int, int>> q; //bfs를 위한 queue

	q.push({ startX, startY });
	map[startX][startY] = 'X';

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx >= 0 && nx < n && ny >= 0 && ny < m)
			{
				if (map[nx][ny] == 'P')
				{
					cnt++;
					map[nx][ny] = 'X';
					q.push({ nx, ny });
				} else if (map[nx][ny] == 'O')
				{
					map[nx][ny] = 'X';
					q.push({ nx, ny });
				}
			}
		}
	}
}

int main()
{
	cin >> n >> m;

	vector<vector<char>> map(n, vector<char>(m)); //맵
	
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

	bfs(map);

	if (cnt > 0)
		cout << cnt << '\n';
	else
		cout << "TT\n";

	return 0;
}
