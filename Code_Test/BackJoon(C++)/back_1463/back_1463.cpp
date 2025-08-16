#include <iostream>
#include <vector>

using namespace std;

int x;
int cnt = 0;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> x;

	vector<int> dp(x + 1, 0);

    for (int i = 2; i <= x; i++) {
        dp[i] = dp[i - 1] + 1;  // 기본 연산 (1을 빼는 경우)
        if (i % 2 == 0) {
            dp[i] = min(dp[i], dp[i / 2] + 1);  // 2로 나누어 떨어질 때
        }
        if (i % 3 == 0) {
            dp[i] = min(dp[i], dp[i / 3] + 1);  // 3으로 나누어 떨어질 때
        }
    }

    cout << dp[x] << '\n';
    return 0;
}


