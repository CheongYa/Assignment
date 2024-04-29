// 1260번 문제

#include <iostream>
#include <queue> // queue 사용을 위한 헤더
#include <string.h> // memset 사용을 위한 헤더

int N, M, V;
int arr[1001][1001]; // 1 <= N <= 1,000 고려
bool visited[1001];
int cnt;

// 재귀 사용하는 방식 / 깊이 우선 탐색
void DFS(int V)
{
	// 시작점 표시
	visited[V] = true;
	// V 출력
	std::cout << V << " ";
	for (int i = 1; i <= N; i++)
	{
		// 재귀 실행 부분
		if (arr[V][i] == 1 && visited[i] == false)
		{
			DFS(i);
		}
		// 재귀 중 조건을 통해 빠져나오는 부분
		if (i == N)
		{
			return;
		}
	}
}

// 큐 사용하는 방식 / 너비 우선 탐색
void BFS(int V)
{
	std::queue<int> q;
	q.push(V);

	// queue가 비어있지 않을 때 실행
	while (!q.empty())
	{
		// 큐에서 하나의 원소를 뽑아 출력
		int x = q.front();
		// 시작점 표시
		visited[x] = true;
		std::cout << x << " ";
		q.pop();

		for (int i = 1; i <= N; i++)
		{
			if (arr[x][i] == 1 && visited[i] == false)
			{
				q.push(i);
				visited[i] = true; // 중복된 값 출력 막기 위한 표시
			}
		}
	}
}

int main()
{
	std::cin >> N >> M >> V; // N: 정점의 개수, M: 간선의 개수, V: 시작할 정점의 번호

	for (int i = 0; i < M; i++) {
		int a, b;
		std::cin >> a >> b;
		arr[a][b] = 1; // 입력 순서에 상관 없이 처리
		arr[b][a] = 1;
	}

	DFS(V);

	std::cout << "\n";

	// DFS 에서 사용된 배열 visited의 값을 0으로 초기화
	memset(visited, false, sizeof(visited));

	BFS(V);

	return 0;
}
