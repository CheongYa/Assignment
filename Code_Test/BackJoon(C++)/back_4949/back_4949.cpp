#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    while (true) {
        string str = "";
        stack<char> st;
        getline(cin, str);
        bool result = true;

        if (str.length() == 1 && str[0] == '.') {
            break;
        }

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '[' || str[i] == '(') {
                st.push(str[i]);
            }

            if (str[i] == ']') {
                if (!st.empty() && st.top() == '[') {
                    st.pop();
                }
                else {
                    result = false;
                    break;
                }
            }
            else if (str[i] == ')') {
                if (!st.empty() && st.top() == '(') {
                    st.pop();
                }
                else {
                    result = false;
                    break;
                }
            }
        }

        if (st.empty() && result) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
}

