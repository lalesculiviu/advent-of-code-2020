#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

bool existsInList[1024];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	int result=-1;
	
	for(int i=0; i<1024; i++)
		existsInList[i]=false;
	
	for(;;){
		string s;
		getline(in, s);
		
		if(in.eof())
			break;
			
		int row0=0;
		int row1=128;
		for(int i=0; i<7; i++)
			if(s[i]=='F')
				row1-=(row1-row0)/2;
			else{
				assert(s[i]=='B');
				row0+=(row1-row0)/2;
			}
		assert(row0==row1-1);

		int seat0=0;
		int seat1=8;
		for(int i=7; i<10; i++)
			if(s[i]=='L')
				seat1-=(seat1-seat0)/2;
			else{
				assert(s[i]=='R');
				seat0+=(seat1-seat0)/2;
			}
		assert(seat0==seat1-1);
		
		int id=row0*8+seat0;
		if(result<id)
			result=id;
			
		assert(id>=0);
		assert(existsInList[id]==false);
		existsInList[id]=true;
	}
	
	cout<<"answer to day 5 part 1 is: "<<result<<endl;
	
	for(int i=0; i<1024; i++)
		if(!existsInList[i])
			cout<<"Not existing: "<<i<<endl;

	return 0;
}
