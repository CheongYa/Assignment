#include <iostream>

using namespace std;

int N, T, P;
int tSize[6];
int tCnt = 0;

int main()
{
    cin >> N;
    for (int i = 0; i < 6; i++)
        cin >> tSize[i];
    cin >> T >> P;

    for (int i = 0; i < 6; i++)
        tCnt += (tSize[i] / T + (tSize[i] % T > 0));

    cout << tCnt << '\n';
    cout << N / P << ' ' << N % P;

    return 0;
}


