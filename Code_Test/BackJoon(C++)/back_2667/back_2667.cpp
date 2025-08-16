// map, visited 백터로 변경하기

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, cnt = 0; // 정사각형의 길이, 단지 개수
// int map[25][25] = { 0, }; // 단지 맵
// bool visited[25][25] = { 0, }; // 방문 표시 맵
// 25칸을 만들고, 그 안을 vector<int>(25, 0)으로 채운다.
vector<vector<int>> map(25, vector<int>(25, 0));
// 25칸을 만들고, 그 안을 vector<bool>(25, 0)으로 채운다.
vector<vector<bool>> visited(25, vector<bool>(25, false));
vector<int> housecnt; // 각 단지의 개수를 저장할 벡터

// X축과 Y축 상 우 하 좌
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0 ,1, 0 };

void DFS(int x, int y)
{
	visited[x][y] = true;
	housecnt[cnt]++; // 각 단지의 개수 파악

	// 상하좌우로 이동하면서 탐색
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		// 지정한 위치를 넘어간다면 continue 실행
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		// 벽이거나 이미 방문한 곳이면 continue 실행
		if (!map[nx][ny] || visited[nx][ny]) continue;
		DFS(nx, ny);
	}
}

int main()
{
	cin >> N;
	string map_num;

	// 입력받아 판 그리기
	for (int i = 0; i < N; i++)
	{
		cin >> map_num;
		for (int j = 0; j < N; j++)
		{
			map[i][j] = map_num[j] - '0';
		}
	}

	// 판에서 1을 탐색하고 탐색하지 않았던 곳이면 탐색하기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 1 && visited[i][j] == false)
			{
				housecnt.push_back(0); // 새로운 단지 발견 시 벡터에 0 추가
				DFS(i, j);
				cnt++;
			}
		}
	}

	cout << cnt << "\n";

	sort(housecnt.begin(), housecnt.end()); // 정렬

	for (const auto& result : housecnt) // 각 단지의 개수 출력
	{
		cout << result << "\n";
	}

	return 0;
}

