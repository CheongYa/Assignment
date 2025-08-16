#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	vector<pair<int, int>> list;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int one, two;
		cin >> one >> two;
		list.push_back(make_pair(one, two));
	}
	sort(list.begin(), list.end());



	for (int i = 0; i < n; i++)
	{
		cout << list[i].first << list[i].second << '\n';
	}
}

