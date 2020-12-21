#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAX_TILES=144;
const int LENGTH=10;

int nTiles;
int tileNumber[MAX_TILES];
int margins[MAX_TILES][8];
char tiles[MAX_TILES][LENGTH+1][LENGTH+1];

int cnt[1<<LENGTH];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	nTiles=0;
	
	int j=0;
	
	for(;;){
		char s[256+1];
		in.getline(s, 256);
		if(in.eof())
			break;
		if(s[0]=='T'){
			j=0;
			nTiles++;
			sscanf(s, "Tile %d:", &tileNumber[nTiles-1]);
		}
		else if(s[0]=='#' || s[0]=='.'){
			strcpy(tiles[nTiles-1][j], s);
			j++;
		}
	}
	
	cout<<"nTiles="<<nTiles<<endl;
	for(int i=0; i<nTiles; i++){
		cout<<"Tile "<<tileNumber[i]<<endl;
		for(int j=0; j<LENGTH; j++)
			cout<<tiles[i][j]<<endl;
		cout<<endl;
	}
	
	for(int i=0; i<nTiles; i++){
		int k=0;
		for(int j=0; j<LENGTH; j++)
			k = 2 * k + (tiles[i][0][j]=='#' ? 1 : 0);
		margins[i][0]=k;

		k=0;
		for(int j=LENGTH-1; j>=0; j--)
			k = 2 * k + (tiles[i][0][j]=='#' ? 1 : 0);
		margins[i][1]=k;

		k=0;
		for(int j=0; j<LENGTH; j++)
			k = 2 * k + (tiles[i][LENGTH-1][j]=='#' ? 1 : 0);
		margins[i][2]=k;

		k=0;
		for(int j=LENGTH-1; j>=0; j--)
			k = 2 * k + (tiles[i][LENGTH-1][j]=='#' ? 1 : 0);
		margins[i][3]=k;

		k=0;
		for(int j=0; j<LENGTH; j++)
			k = 2 * k + (tiles[i][j][0]=='#' ? 1 : 0);
		margins[i][4]=k;

		k=0;
		for(int j=LENGTH-1; j>=0; j--)
			k = 2 * k + (tiles[i][j][0]=='#' ? 1 : 0);
		margins[i][5]=k;

		k=0;
		for(int j=0; j<LENGTH; j++)
			k = 2 * k + (tiles[i][j][LENGTH-1]=='#' ? 1 : 0);
		margins[i][6]=k;

		k=0;
		for(int j=LENGTH-1; j>=0; j--)
			k = 2 * k + (tiles[i][j][LENGTH-1]=='#' ? 1 : 0);
		margins[i][7]=k;
		
		/*if(i==0){
			cout<<"Tile "<<tileNumber[i]<<endl;
			for(int j=0; j<8; j++)
				cout<<"j="<<j<<", binary="<<margins[i][j]<<endl;
		}*/
	}
	
	for(int i=0; i<(1<<LENGTH); i++)
		cnt[i]=0;
	for(int i=0; i<nTiles; i++)
		for(int j=0; j<8; j++)
			cnt[margins[i][j]]++;
	
	long long int prod=1;
	int q=0;
	for(int i=0; i<nTiles; i++){
		int k=0;
		for(int j=0; j<8; j++)
			if(cnt[margins[i][j]]<2)
				k++;
		if(k>=4){
			prod*=tileNumber[i];
			q++;
		}
	}
	assert(q==4);
	
	cout<<"prod="<<prod<<endl;
	
	return 0;
}
