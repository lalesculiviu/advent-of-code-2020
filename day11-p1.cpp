#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char a[128][128];
char b[128][128];

int nRows;
int nCols;

int nOccupiedNeighbors(int i, int j)
{
	int dr[]={-1, -1, -1, 0, 0, 1, 1, 1};
	int dc[]={-1, 0, 1, -1, 1, -1, 0, 1};
	
	int sum=0;
	for(int dir=0; dir<8; dir++)
		if(a[i+dr[dir]][j+dc[dir]]=='#')
			sum++;
	return sum;
}

void printMatrix(char a[128][128])
{
	/*for(int i=1; i<=nRows; i++){
		for(int j=1; j<=nCols; j++)
			cout<<a[i][j];
		cout<<endl;
	}
	cout<<endl;*/
}

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	nRows=0;
	nCols=0;
	
	for(;;){
		char s[128];
		
		in.getline(s, 127);
	
		if(in.eof())
			break;
			
		a[nRows][0]='.';
		int j;
		for(j=0; s[j]; j++)
			a[nRows+1][j+1]=s[j];
		a[nRows+1][j+1]='.';
		nRows++;
		
		if(nCols==0)
			nCols=j;
		else
			assert(nCols==j);
	}

	printMatrix(a);
	
	for(;;){
		bool change=false;
		for(int i=1; i<=nRows; i++)
			for(int j=1; j<=nCols; j++){
				b[i][j]=a[i][j];
				if(a[i][j]=='L' && nOccupiedNeighbors(i, j)==0){
					b[i][j]='#';
					change=true;
				}
				else if(a[i][j]=='#' && nOccupiedNeighbors(i, j)>=4){
					b[i][j]='L';
					change=true;
				}
			}
	
		if(!change)
			break;

		for(int i=1; i<=nRows; i++)
			for(int j=1; j<=nCols; j++)
				a[i][j]=b[i][j];
				
		printMatrix(a);
	}
	
	int cnt=0;
	for(int i=1; i<=nRows; i++)
		for(int j=1; j<=nCols; j++)
			if(a[i][j]=='#')
				cnt++;
	cout<<"part 1 result="<<cnt<<endl;
	
	return 0;
}
