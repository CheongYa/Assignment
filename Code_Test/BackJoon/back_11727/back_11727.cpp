﻿#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> dp(n + 1, 0);

	if (n < 2)
	{
		cout << 1;
		return 0;
	}

	dp[1] = 1;
	dp[2] = 3;
	for (int i = 3; i < n + 1; i++)
		dp[i] = (dp[i - 1] + dp[i - 2] * 2) % 10007;
	cout << dp[n];

	return 0;
}