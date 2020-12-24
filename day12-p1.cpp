#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	int dx=0;
	int dy=0;
	int crtdir=0;
	int deltax[4]={1, 0, -1, 0};
	int deltay[4]={0, 1, 0, -1};
	
	for(;;){
		string s;
		getline(in, s);
		if(in.eof())
			break;
			
		int amount=stoi(s.substr(1, s.size()-1));
		if(s[0]=='F'){
			dx+=amount*deltax[crtdir];
			dy+=amount*deltay[crtdir];
		}
		else if(s[0]=='N'){
			dy-=amount;
		}
		else if(s[0]=='S'){
			dy+=amount;
		}
		else if(s[0]=='E'){
			dx+=amount;
		}
		else if(s[0]=='W'){
			dx-=amount;
		}
		else if(s[0]=='R'){
			if(amount==90)
				crtdir=(crtdir+1)%4;
			else if(amount==180)
				crtdir=(crtdir+2)%4;
			else if(amount==270)
				crtdir=(crtdir+3)%4;
			else
				assert(0);
		}
		else if(s[0]=='L'){
			if(amount==90)
				crtdir=(crtdir-1+4)%4;
			else if(amount==180)
				crtdir=(crtdir-2+4)%4;
			else if(amount==270)
				crtdir=(crtdir-3+4)%4;
			else
				assert(0);
		}
		else{
			assert(0);
		}
	}
	
	int result=abs(dx)+abs(dy);
	cout<<"answer to part 1 is "<<result<<endl;

	return 0;
}
