#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

bool isDigit(char c)
{
	return c>='0' && c<='9';
}

long long int getValue(char s[257])
{
	long long int val[3]={0, 0, 0};
	long long int op[3];
	const long long int PLUS=0;
	const long long int MULT=1;
	op[0]=PLUS;
	long long int level=0;
	for(long long int i=0; s[i]; i++){
		if(s[i]==' '){
			//do nothing
		}
		else if(isDigit(s[i])){
			if(op[level]==PLUS)
				val[level]+=s[i]-'0';
			else{
				assert(op[level]==MULT);
				val[level]*=s[i]-'0';
			}
		}
		else if(s[i]=='+')
			op[level]=PLUS;
		else if(s[i]=='*')
			op[level]=MULT;
		else if(s[i]=='('){
			assert(level<2);
			level++;
			val[level]=0;
			op[level]=PLUS;
		}
		else if(s[i]==')'){
			assert(level>0);
			level--;
			if(op[level]==PLUS){
				val[level]+=val[level+1];
			}
			else{
				assert(op[level]==MULT);
				val[level]*=val[level+1];
			}
		}
	}
	
	return val[0];
}

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	long long int totalSum=0;
	for(;;){
		char s[257];
		in.getline(s, 256);
		if(in.eof())
			break;
		long long int sum=getValue(s);
		cout<<"s="<<s<<endl;
		cout<<"sum="<<sum<<endl;
		cout<<endl;
		totalSum+=sum;
	}
	cout<<"totalSum="<<totalSum<<endl;

	return 0;
}
