#include <cassert>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

typedef long long int int64;

bool isDigit(char c)
{
	return c>='0' && c<='9';
}

int64 getValue(char s[257])
{
	stack<char> st;
	queue<char> deq;
	
	for(int64 i=0; s[i]; i++){
		if(s[i]==' ')
			continue;
		else if(isDigit(s[i])){
			cout<<s[i];
			deq.push(s[i]);
		}
		else if(s[i]=='+'){
			while(!st.empty() && st.top()=='+' && st.top()!='('){
				cout<<st.top();
				deq.push(st.top());
				st.pop();
			}
			st.push(s[i]);
		}
		else if(s[i]=='*'){
			while(!st.empty() && (st.top()=='+' || st.top()=='*') && st.top()!='('){
				cout<<st.top();
				deq.push(st.top());
				st.pop();
			}
			st.push(s[i]);
		}
		else if(s[i]=='('){
			st.push(s[i]);
		}
		else if(s[i]==')'){
			while(!st.empty() && st.top()!='('){
				cout<<st.top();
				deq.push(st.top());
				st.pop();
			}
			assert(!st.empty());
			assert(st.top()=='(');
			st.pop();
		}
	}

	while(!st.empty()){
		cout<<st.top();
		deq.push(st.top());
		st.pop();
	}
	
	cout<<endl;
	
	stack<int64> st2;
	
	for(;;){
		if(deq.empty())
			break;
		char c=deq.front();
		deq.pop();
		if(isDigit(c))
			st2.push(c-'0');
		else if(c=='+'){
			int64 op1=st2.top();
			st2.pop();
			int64 op2=st2.top();
			st2.pop();
			int64 r=op1+op2;
			st2.push(r);
		}
		else if(c=='*'){
			int64 op1=st2.top();
			st2.pop();
			int64 op2=st2.top();
			st2.pop();
			int64 r=op1*op2;
			st2.push(r);
		}
		else
			assert(0);
	}
	
	int64 sum=st2.top();
	st2.pop();
	assert(st2.empty());
	return sum;
}

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	int64 totalSum=0;
	for(;;){
		char s[257];
		in.getline(s, 256);
		if(in.eof())
			break;
		int64 sum=getValue(s);
		cout<<"s="<<s<<endl;
		cout<<"sum="<<sum<<endl;
		cout<<endl;
		totalSum+=sum;
	}
	cout<<"totalSum="<<totalSum<<endl;

	return 0;
}
