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
	
	int result=0;
	int i=0;
	int j=0;
	for(;;){
		i++;
		j+=3;
		if(i>=nRows)
			break;
		if(j>=nCols)
			j%=nCols;
		
		if(a[i][j]=='#')
			result++;
	}
	
	cout<<"The answer to day 3 part 1 is: "<<result<<endl;

	return 0;
}
