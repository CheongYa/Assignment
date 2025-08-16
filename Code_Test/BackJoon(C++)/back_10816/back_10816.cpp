#include <iostream>
#include <map>

using namespace std;

int N, M, num;
map<int, int> cards;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		cards[num]++;
	}

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> num;
		cout << cards[num] << " ";
	}
}


