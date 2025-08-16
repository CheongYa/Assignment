#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int ans = 0;
int ans_rg = 0;
vector<vector<char>> grid;
vector<vector<char>> grid_rg;
vector<vector<bool>> visit;
vector<vector<bool>> visit_rg;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void BFS(int startX, int startY, char color)
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

			if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visit[nx][ny] && grid[nx][ny] == color)
			{
				q.push({ nx, ny });
				visit[nx][ny] = true;
			}
		}
	}
}

void BFS_RG(int startX, int startY, char color)
{
	queue<pair<int, int>> q;
	q.push({ startX, startY });
	visit_rg[startX][startY] = true;

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visit_rg[nx][ny] && grid_rg[nx][ny] == color)
			{
				q.push({ nx, ny });
				visit_rg[nx][ny] = true;
			}
		}
	}
}

int main()
{
	cin >> n;
	grid = vector<vector<char>>(n, vector<char>(n));
	grid_rg = vector<vector<char>>(n, vector<char>(n));
	visit = vector<vector<bool>>(n, vector<bool>(n, false));
	visit_rg = vector<vector<bool>>(n, vector<bool>(n, false));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
			grid_rg[i][j] = (grid[i][j] == 'G') ? 'R' : grid[i][j];
		}
	}

	//정상인
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visit[i][j] == false)
			{
				BFS(i, j, grid[i][j]);
				ans++;
			}
		}
	}

	//적록색약
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visit_rg[i][j] == false)
			{
				BFS_RG(i, j, grid_rg[i][j]);
				ans_rg++;
			}
		}
	}

	cout << ans << " " << ans_rg;
}


