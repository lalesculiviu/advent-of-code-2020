#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAXR=512;
const int MAXC=32;

char a[MAXR][MAXC];

int nRows;
int nCols;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	nRows=0;
	nCols=0;
	
	for(;;){
		string s;
		getline(in, s);
		if(in.eof())
			break;
		if(nCols==0)
			nCols=int(s.size());
		else
			assert(nCols==int(s.size()));
			
		for(size_t i=0; i<s.size(); i++)
			a[nRows][i]=s[i];
			
		nRows++;
	}
	
	int sx[5]={1, 1, 1, 1, 2};
	int sy[5]={1, 3, 5, 7, 1};
	int finalResult=1;
	for(int s=0; s<5; s++){
		int i=0;
		int j=0;
		int result=0;
		for(;;){
			i+=sx[s];
			j+=sy[s];
			if(i>=nRows)
				break;
			if(j>=nCols)
				j%=nCols;
			
			if(a[i][j]=='#')
				result++;
		}
		cout<<"s="<<s+1<<", result="<<result<<endl;
		finalResult*=result;
	}
	
	cout<<"The answer to day 3 part 2 is: "<<finalResult<<endl;

	return 0;
}
