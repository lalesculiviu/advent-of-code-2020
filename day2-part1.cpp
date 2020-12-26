#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int cnt=0;
	//ifstream in("sample-input.txt");
	ifstream in("input");
	for(;;){
		string s;
	
		getline(in, s);
		if(in.eof())
			break;
			
		int pos1=0;
		int pos2=s.find('-', pos1);
		int m=stoi(s.substr(pos1, pos2-pos1));
		pos1=pos2+1;
		pos2=s.find(' ', pos1);
		int M=stoi(s.substr(pos1, pos2-pos1));
		char c=s[pos2+1];
		cout<<"c="<<c<<endl;
		pos1=pos2+4;
		cout<<s.substr(pos1)<<endl;
		string s2=s.substr(pos1);
		
		int k=0;
		for(size_t i=0; i<s2.size(); i++)
			if(s2[i]==c)
				k++;
				
		if(k>=m && k<=M)
			cnt++;
	}
	cout<<"The answer to day 2 part 1 is: "<<cnt<<endl;

	return 0;
}
