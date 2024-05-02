#include <iostream>
#include <queue>

using namespace std;

int N, num;
string command;
queue<int> qu;

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> command;
        if (command == "push")
        {
            cin >> num;
            qu.push(num);
        }
        else if (command == "pop")
        {
            if (qu.empty())
                cout << -1 << endl;
            else
            {
                cout << qu.front() << endl;
                qu.pop();
            }
        }
        else if (command == "size")
        {
            cout << qu.size() << endl;
        }
        else if (command == "empty")
        {
            if (qu.empty())
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
        else if (command == "front")
        {
            if (qu.empty())
                cout << -1 << endl;
            else
                cout << qu.front() << endl;
        }
        else if (command == "back")
        {
            if (qu.empty())
                cout << -1 << endl;
            else
                cout << qu.back() << endl;
        }
    }
}
