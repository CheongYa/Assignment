#include <iostream>

using namespace std;

int N, cnt;

int main()
{
    cin >> N;
    for (int i = 666; ; i++)
    {
        int tmp = i;
        while (tmp >= 666)
        {
            if (tmp % 1000 == 666)
            {
                cnt++;
                break;
            }
            tmp /= 10;
        }
        if (N == cnt)
        {
            cout << i;
            break;
        }
    }
}
