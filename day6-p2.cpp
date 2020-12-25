#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool a[26];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	int result=0;
	
	for(;;){
		for(int i=0; i<26; i++)
			a[i]=true;

		for(;;){
			string s;
			getline(in, s);
			if(in.eof() || s.empty())
				break;
				
			for(char i='a'; i<='z'; i++)
				if(s.find(i)==string::npos)
					a[i-'a']=false;
		}
		
		for(int i=0; i<26; i++)
			if(a[i])
				result++;
				
		cout<<"partial result="<<result<<endl;
		
		if(in.eof())
			break;
	}
	
	cout<<"result of day 6 part 1 is "<<result<<endl;

	return 0;
}
