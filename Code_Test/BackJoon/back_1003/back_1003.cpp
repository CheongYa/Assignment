#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int arr[41] = { 0, 1, 1 };
    for (int i = 3; i < 41; i++)
        arr[i] = arr[i - 1] + arr[i - 2];
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int num;
        cin >> num;

        if (num == 0)
            cout << "1 0\n";
        else if (num == 1)
            cout << "0 1\n";
        else
            cout << arr[num - 1] << " " << arr[num] << '\n';
    }

    
}

