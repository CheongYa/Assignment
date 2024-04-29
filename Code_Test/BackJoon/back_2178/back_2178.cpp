//2178번 문제

#include <iostream>
#include <vector>

int N, M;
int map[100][100];

void bfs()
{

}

int main()
{
	std::string miro_num;
	std::cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		std::cin >> miro_num;
		for (int j = 0; j < M; j++)
		{
			map[i][j] = miro_num[j] - '0';
		}

		miro_num = "";
	}

	std::cout;

	return 0;
}