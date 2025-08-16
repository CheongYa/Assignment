#include <iostream>

using namespace std;

int N, ans;

int main()
{
    cin >> N;
    ans = 0;

    for (int i = 5; i <= N; i *= 5)
        ans += N / i;
    cout << ans << '\n';
}


