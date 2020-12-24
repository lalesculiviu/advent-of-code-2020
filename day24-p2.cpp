#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int a[256][256];
int b[256][256];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	for(int i=0; i<256; i++)
		for(int j=0; j<256; j++)
			a[i][j]=0;
	
	for(;;){
		string s;
		
		getline(in, s);
		
		if(in.eof())
			break;
			
		int i=127;
		int j=127;
		
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
		
		assert(i>=0 && i<256);
		assert(j>=0 && j<256);
		a[i][j]=1-a[i][j];
	}
	
	int cnt=0;
	for(int i=0; i<256; i++)
		for(int j=0; j<256; j++)
			if(a[i][j]==1)
				cnt++;

	cout<<"result part 1="<<cnt<<endl;

	for(int iter=0; iter<100; iter++){
		for(int i=1; i<255; i++)
			for(int j=1; j<255; j++){
				int sn=a[i][j-1]+a[i][j+1]+a[i-1][j-1]+a[i-1][j]+a[i+1][j]+a[i+1][j+1];
				if(a[i][j]==1){
					if(sn==0 || sn>2)
						b[i][j]=0;
					else
						b[i][j]=1;
				}
				else{
					assert(a[i][j]==0);
					if(sn==2)
						b[i][j]=1;
					else
						b[i][j]=0;
				}
			}
		
		for(int i=1; i<255; i++)
			for(int j=1; j<255; j++)
				a[i][j]=b[i][j];
	}

	cnt=0;
	for(int i=1; i<255; i++)
		for(int j=1; j<255; j++)
			if(a[i][j]==1)
				cnt++;

	cout<<"result part 2="<<cnt<<endl;

	return 0;
}
