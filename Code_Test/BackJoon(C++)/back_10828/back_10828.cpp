#include <iostream>
#include <stack>

using namespace std;

int N, num;
string command;
stack<int> st;

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> command;
		if (command == "push")
		{
			cin >> num;
			st.push(num);

		}
		else if (command == "pop")
		{
			if (st.empty())
				cout << -1 << endl;
			else
			{
				cout << st.top() << endl;
				st.pop();
			}
		}
		else if (command == "size")
		{
			cout << st.size() << endl;
		}
		else if (command == "empty")
		{
			if (st.empty())
				cout << 1 << endl;
			else
				cout << 0 << endl;
		}
		else if (command == "top")
		{
			if (st.empty())
				cout << -1 << endl;
			else
				cout << st.top() << endl;
		}
	}
}
