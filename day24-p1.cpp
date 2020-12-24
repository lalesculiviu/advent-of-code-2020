#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int a[64][64];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	for(int i=0; i<64; i++)
		for(int j=0; j<64; j++)
			a[i][j]=0;
	
	for(;;){
		string s;
		
		getline(in, s);
		
		if(in.eof())
			break;
			
		int i=31;
		int j=31;
		
		for(size_t k=0; k<s.size(); k++){
			if(s[k]=='w'){
				j--;
			}
			else if(s[k]=='e'){
				j++;
			}
			else if(s[k]=='s'){
				i++;
				if(s[k+1]=='e')
					j++;
				k++;
			}
			else if(s[k]=='n'){
				i--;
				if(s[k+1]=='w')
					j--;
				k++;
			}
		}
		
		assert(i>=0 && i<64);
		assert(j>=0 && j<64);
		a[i][j]=1-a[i][j];
	}
	
	int cnt=0;
	for(int i=0; i<64; i++)
		for(int j=0; j<64; j++)
			if(a[i][j]==1)
				cnt++;

	cout<<"result="<<cnt<<endl;

	return 0;
}
