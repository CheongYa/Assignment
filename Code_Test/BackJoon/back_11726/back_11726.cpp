#include <iostream>
#include <vector>

using namespace std;

int n;

int main()
{
    cin >> n;
    vector<int> dp(n + 1, 0);

    if (n < 2)
    {
        cout << 1;
        return 0;
    }

    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < n + 1; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;

    cout << dp[n];
}

