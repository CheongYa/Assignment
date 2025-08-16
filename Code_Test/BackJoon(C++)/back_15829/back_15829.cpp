// 인터넷 검색. 문제가 왜 이따구여..

#include <iostream>

using namespace std;

int main()
{
    int L;
    string str;
    long long m = 1234567891;
    long long r = 1;
    long long sum = 0;

    cin >> L;
    cin >> str;

    for (int i = 0; i < L; i++) {
        sum += ((long(str[i]) - 96) * r) % m;
        r = (r * 31) % m;
    }

    cout << sum % m;
}
