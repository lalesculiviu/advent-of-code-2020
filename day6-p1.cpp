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
			a[i]=false;

		for(;;){
			string s;
			getline(in, s);
			if(in.eof() || s.empty())
				break;
				
			for(size_t i=0; i<s.size(); i++)
				a[s[i]-'a']=true;
		}
		
		for(int i=0; i<26; i++)
			if(a[i])
				result++;
		
		if(in.eof())
			break;
	}
	
	cout<<"result of day 6 part 1 is "<<result<<endl;

	return 0;
}
