#include <iostream>
#include <vector>

int N, M, cnt; // 컴퓨터의 수, 네트워크 상에 직접 연결되어 있는 컴퓨터 쌍의 수, 전염된 컴퓨터의 수
std::vector<int> vec[101]; // 컴퓨터 수에 대한 벡터
bool visited[101]; // 접근한 것에 대한 표시

void dfs(int x)
{
	visited[x] = true; // 접근한 곳 표시

	// 접근한 곳의 원소 갯수만큼 반복
	for (int i = 0; i < vec[x].size(); i++)
	{
		int k = vec[x][i]; // 연결되어 있는 값 k에 대입

		if (visited[k] == false) // 접근해보지 않았을 시에 확인
		{
			cnt++;
			dfs(k);
		}
	}

	return;
}

int main()
{
	std::cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int A, B;
		std::cin >> A >> B;
		vec[A].push_back(B); // 다차원 방식으로 벡터에 값 넣기
		vec[B].push_back(A); // 양방향 확인
	}

	dfs(1);

	std::cout << cnt;

	return 0;
}

