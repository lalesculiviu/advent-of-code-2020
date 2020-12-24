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
	
	int wpx=10;
	int wpy=-1;
	
	for(;;){
		string s;
		getline(in, s);
		if(in.eof())
			break;
			
		int amount=stoi(s.substr(1, s.size()-1));
		if(s[0]=='F'){
			dx+=amount*wpx;
			dy+=amount*wpy;
		}
		else if(s[0]=='N'){
			wpy-=amount;
		}
		else if(s[0]=='S'){
			wpy+=amount;
		}
		else if(s[0]=='E'){
			wpx+=amount;
		}
		else if(s[0]=='W'){
			wpx-=amount;
		}
		else if(s[0]=='R'){
			if(amount==90){
				int t=wpx;
				wpx=-wpy;
				wpy=t;
			}
			else if(amount==180){
				wpx=-wpx;
				wpy=-wpy;
			}
			else if(amount==270){
				int t=wpx;
				wpx=wpy;
				wpy=-t;
			}
			else{
				assert(0);
			}
		}
		else if(s[0]=='L'){
			if(amount==270){
				int t=wpx;
				wpx=-wpy;
				wpy=t;
			}
			else if(amount==180){
				wpx=-wpx;
				wpy=-wpy;
			}
			else if(amount==90){
				int t=wpx;
				wpx=wpy;
				wpy=-t;
			}
			else{
				assert(0);
			}
		}
		else{
			assert(0);
		}
	}
	
	int result=abs(dx)+abs(dy);
	cout<<"answer to part 2 is "<<result<<endl;

	return 0;
}
