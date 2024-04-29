#include <iostream>
#include <stack>

using namespace std;

int T;

string VPS(string x)
{
    stack<char> st;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == '(')
        {
            st.push(x[i]);
        }
        else
        {
            if (st.empty()) return "NO";
            st.pop();
        }
    }
    if (st.empty())
    {
        return "YES";
    }
    else
    {
        return "NO";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string x;

    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> x;
        cout << VPS(x) << '\n';
    }
}