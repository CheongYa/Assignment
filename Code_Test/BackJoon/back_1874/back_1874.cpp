#include <iostream>
#include <stack>

using namespace std;

int main()
{
    stack<int> st;
    string str;
    int cnt = 1;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;

        while (cnt <= num) {
            st.push(cnt);
            cnt += 1;
            //cout << "+\n";
            str += '+';
        }

        if (st.top() == num) {
            st.pop();
            //cout << "-\n";
            str += '-';
        }
        else {
            cout << "NO";
            return 0;
        }
    }

    for (int j = 0; j < str.length(); j++) {
        cout << str[j] << "\n";
    }

    return 0;
}