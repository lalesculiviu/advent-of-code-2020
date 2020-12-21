#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAX_DIM=12;
const int MAX_TILES=MAX_DIM*MAX_DIM;
const int LENGTH=10;

int nTiles;
int tileNumber[MAX_TILES];
int margins[MAX_TILES][8];
char tiles[MAX_TILES][LENGTH+1][LENGTH+1];

int cnt[1<<LENGTH];

int map[MAX_DIM][MAX_DIM]; //each value is from 0 to nTiles-1

int variants[MAX_TILES][16][4]; //16 is rotations/flips, 4 is number of edges

int nDim;

bool visited[MAX_TILES];

int solutionTile[MAX_DIM][MAX_DIM];
int solutionDir[MAX_DIM][MAX_DIM];

void swap(char& c1, char& c2)
{
	char c=c1;
	c1=c2;
	c2=c;
}

void flipVertical(char a[LENGTH+1][LENGTH+1])
{
	for(int i=0; i<LENGTH; i++)
		for(int j=0, k=LENGTH-1; j<k; j++, k--)
			swap(a[i][j], a[i][k]);
}

void flipHorizontal(char a[LENGTH+1][LENGTH+1])
{
	for(int i=0, k=LENGTH-1; i<k; i++, k--)
		for(int j=0; j<LENGTH; j++)
			swap(a[i][j], a[k][j]);
}

void rotateClockwise(char a[LENGTH+1][LENGTH+1])
{
	char tmp[LENGTH+1][LENGTH+1];
	
	for(int i=1; i<LENGTH-1; i++)
		for(int j=1; j<LENGTH-1; j++)
			tmp[i][j]=a[LENGTH-1-j][i];
			
	for(int i=1; i<LENGTH-1; i++)
		for(int j=1; j<LENGTH-1; j++)
			a[i][j]=tmp[i][j];
}

void flipVerticalLarge(char b[MAX_DIM*LENGTH][MAX_DIM*LENGTH])
{
	for(int i=0; i<MAX_DIM*LENGTH; i++)
		for(int j=0, k=MAX_DIM*LENGTH-1; j<k; j++, k--)
			swap(b[i][j], b[i][k]);
}

void flipHorizontalLarge(char b[MAX_DIM*LENGTH][MAX_DIM*LENGTH])
{
	for(int i=0, k=MAX_DIM*LENGTH-1; i<k; i++, k--)
		for(int j=0; j<MAX_DIM*LENGTH; j++)
			swap(b[i][j], b[k][j]);
}

void rotateClockwiseLarge(char b[MAX_DIM*LENGTH][MAX_DIM*LENGTH])
{
	char tmp[MAX_DIM*LENGTH][MAX_DIM*LENGTH];
	
	for(int i=0; i<MAX_DIM*LENGTH; i++)
		for(int j=0; j<MAX_DIM*LENGTH; j++)
			tmp[i][j]=b[MAX_DIM*LENGTH-1-j][i];
			
	for(int i=0; i<MAX_DIM*LENGTH; i++)
		for(int j=0; j<MAX_DIM*LENGTH; j++)
			b[i][j]=tmp[i][j];
}

void direction16Tile(int tile, int dir, char result[LENGTH+1][LENGTH+1])
{
	for(int i=0; i<LENGTH+1; i++)
		for(int j=0; j<LENGTH+1; j++)
			result[i][j]=tiles[tile][i][j];

	if(dir/4==1){
		rotateClockwise(result);
	}
	else if(dir/4==2){
		rotateClockwise(result);
		rotateClockwise(result);
	}
	else if(dir/4==3){
		rotateClockwise(result);
		rotateClockwise(result);
		rotateClockwise(result);
	}
	
	if(dir%4==1){
		flipVertical(result);
	}
	else if(dir%4==2){
		flipHorizontal(result);
	}
	else if(dir%4==3){
		flipVertical(result);
		flipHorizontal(result);
	}
	
	return;
}

bool back(int i)
{
	//cout<<"i="<<i<<endl;

	static int mx=0;
	if(i>mx){
		mx=i;
		cout<<"mx="<<mx<<endl;
	}
	
	if(i>=nTiles)
		return true;

	int row=i/nDim;
	int col=i%nDim;
	
	/*int nextRow=row;
	int nextCol=col+1;
	if(nextCol>=nDim){
		nextRow++;
		nextCol=0;
	}
	if(nextRow>=nDim)
		return true;*/
	
	for(int j=0; j<nTiles; j++)
		if(!visited[j]){
			for(int d=0; d<16; d++){
				if((row==0 && cnt[variants[j][d][0]]==1)
				 || (row>0 && variants[solutionTile[row-1][col]][solutionDir[row-1][col]][2]==variants[j][d][0])){
					if((col==0 && cnt[variants[j][d][3]]==1)
					 || (col>0 && variants[solutionTile[row][col-1]][solutionDir[row][col-1]][1]==variants[j][d][3])){
						visited[j]=true;
						solutionTile[row][col]=j;
						solutionDir[row][col]=d;
						if(back(i+1))
							return true;
						visited[j]=false;
					}
				}
			}
		}
		
	return false;
}

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
	
	nDim=int(sqrt(nTiles));
	
	/*cout<<"nTiles="<<nTiles<<endl;
	for(int i=0; i<nTiles; i++){
		cout<<"Tile "<<tileNumber[i]<<endl;
		for(int j=0; j<LENGTH; j++)
			cout<<tiles[i][j]<<endl;
		cout<<endl;
	}*/
	
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
		
		variants[i][0][0]=margins[i][0];
		variants[i][0][1]=margins[i][6];
		variants[i][0][2]=margins[i][2];
		variants[i][0][3]=margins[i][4];

		variants[i][1][0]=margins[i][1];
		variants[i][1][1]=margins[i][4];
		variants[i][1][2]=margins[i][3];
		variants[i][1][3]=margins[i][6];

		variants[i][2][0]=margins[i][2];
		variants[i][2][1]=margins[i][7];
		variants[i][2][2]=margins[i][0];
		variants[i][2][3]=margins[i][5];

		variants[i][3][0]=margins[i][3];
		variants[i][3][1]=margins[i][5];
		variants[i][3][2]=margins[i][1];
		variants[i][3][3]=margins[i][7];

		//rotate once clockwise
		variants[i][4][0]=margins[i][5];
		variants[i][4][1]=margins[i][0];
		variants[i][4][2]=margins[i][7];
		variants[i][4][3]=margins[i][2];

		variants[i][5][0]=margins[i][4];
		variants[i][5][1]=margins[i][2];
		variants[i][5][2]=margins[i][6];
		variants[i][5][3]=margins[i][0];

		variants[i][6][0]=margins[i][7];
		variants[i][6][1]=margins[i][1];
		variants[i][6][2]=margins[i][5];
		variants[i][6][3]=margins[i][3];

		variants[i][7][0]=margins[i][4];
		variants[i][7][1]=margins[i][3];
		variants[i][7][2]=margins[i][5];
		variants[i][7][3]=margins[i][1];

		//rotate twice
		variants[i][8][0]=margins[i][3];
		variants[i][8][1]=margins[i][5];
		variants[i][8][2]=margins[i][1];
		variants[i][8][3]=margins[i][7];

		variants[i][9][0]=margins[i][2];
		variants[i][9][1]=margins[i][7];
		variants[i][9][2]=margins[i][0];
		variants[i][9][3]=margins[i][5];

		variants[i][10][0]=margins[i][1];
		variants[i][10][1]=margins[i][4];
		variants[i][10][2]=margins[i][3];
		variants[i][10][3]=margins[i][6];

		variants[i][11][0]=margins[i][2];
		variants[i][11][1]=margins[i][6];
		variants[i][11][2]=margins[i][0];
		variants[i][11][3]=margins[i][4];

		//rotate three times
		variants[i][12][0]=margins[i][6];
		variants[i][12][1]=margins[i][3];
		variants[i][12][2]=margins[i][4];
		variants[i][12][3]=margins[i][1];

		variants[i][13][0]=margins[i][7];
		variants[i][13][1]=margins[i][1];
		variants[i][13][2]=margins[i][5];
		variants[i][13][3]=margins[i][3];

		variants[i][14][0]=margins[i][4];
		variants[i][14][1]=margins[i][2];
		variants[i][14][2]=margins[i][6];
		variants[i][14][3]=margins[i][0];

		variants[i][15][0]=margins[i][5];
		variants[i][15][1]=margins[i][0];
		variants[i][15][2]=margins[i][7];
		variants[i][15][3]=margins[i][2];
	}

	for(int i=0; i<(1<<LENGTH); i++)
		cnt[i]=0;
	for(int i=0; i<nTiles; i++)
		for(int j=0; j<8; j++)
			cnt[margins[i][j]]++;
	
	for(int i=0; i<nTiles; i++)
		visited[i]=false;
	bool t=back(0);
	cout<<"t="<<t<<endl;
	
	if(t)
		for(int row=0; row<nDim; row++)
			for(int col=0; col<nDim; col++)
				cout<<"row="<<row<<", col="<<col<<", tile="<<tileNumber[solutionTile[row][col]]<<", dir="<<solutionDir[row][col]<<endl;

	cout<<endl;
	
	char resultingTiles[MAX_DIM][MAX_DIM][LENGTH+1][LENGTH+1];
	for(int row=0; row<nDim; row++){
		for(int col=0; col<nDim; col++){
			char tmp[LENGTH+1][LENGTH+1];
			direction16Tile(solutionTile[row][col], solutionDir[row][col], tmp);
			for(int i=0; i<LENGTH; i++)
				for(int j=0; j<LENGTH; j++)
					resultingTiles[row][col][i][j]=tmp[i][j];
		}
	}
	
	char a[MAX_DIM*LENGTH][MAX_DIM*LENGTH];
	int nr=0;
	int nc=0;
	for(int p=0; p<nDim; p++){
		for(int i=1; i<LENGTH-1; i++){
			for(int q=0; q<nDim; q++){
				for(int j=1; j<LENGTH-1; j++){
					a[nr][nc]=resultingTiles[p][q][i][j];
					cout<<resultingTiles[p][q][i][j];
					nc++;
				}
				cout<<" ";
				//nc++;
			}
			cout<<endl;
			nr++;
			nc=0;
		}
		//cout<<endl;
		//nr++;
		//nc=0;
	}
	
	nc=nr;
	
	for(int i=0; i<nr; i++){
		for(int j=0; j<nc; j++)
			cout<<a[i][j];
		cout<<endl;
	}
	
	char b[MAX_DIM*LENGTH][MAX_DIM*LENGTH];
	char c[MAX_DIM*LENGTH][MAX_DIM*LENGTH];
	
	int monsterRows=3;
	int monsterCols=20;
	char monster[3][20];
	for(int i=0; i<monsterRows; i++)
		for(int j=0; j<monsterCols; j++)
			monster[i][j]=' ';
	monster[0][18]='#';

	monster[1][0]='#';
	monster[1][5]='#';
	monster[1][6]='#';
	monster[1][11]='#';
	monster[1][12]='#';
	monster[1][17]='#';
	monster[1][18]='#';
	monster[1][19]='#';

	monster[2][1]='#';
	monster[2][4]='#';
	monster[2][7]='#';
	monster[2][10]='#';
	monster[2][13]='#';
	monster[2][16]='#';
	
	for(int dir=0; dir<15; dir++){
		//flip and rotate a to b
		for(int i=0; i<nr; i++)
			for(int j=0; j<nc; j++)
				b[i][j]=a[i][j];
				
		if(dir/4==1){
			rotateClockwiseLarge(b);
		}
		else if(dir/4==2){
			rotateClockwiseLarge(b);
			rotateClockwiseLarge(b);
		}
		else if(dir/4==3){
			rotateClockwiseLarge(b);
			rotateClockwiseLarge(b);
			rotateClockwiseLarge(b);
		}
	
		if(dir%4==1){
			flipVerticalLarge(b);
		}
		else if(dir%4==2){
			flipHorizontalLarge(b);
		}
		else if(dir%4==3){
			flipVerticalLarge(b);
			flipHorizontalLarge(b);
		}
		
		//copy b to c
		for(int i=0; i<nr; i++)
			for(int j=0; j<nc; j++)
				c[i][j]=b[i][j];
		
		//search for monsters in b, record them in c
		//if monster(s) found, output result and stop
		bool overallFound=false;
		for(int i=0; i<=nr-monsterRows; i++)
			for(int j=0; j<=nc-monsterCols; j++){
				bool found=true;
				for(int mr=0; mr<monsterRows && found; mr++)
					for(int mc=0; mc<monsterCols && found; mc++)
						if(monster[mr][mc]=='#')
							if(b[i+mr][j+mc]!='#')
								found=false;
				
				if(found){
					overallFound=true;

					for(int mr=0; mr<monsterRows && found; mr++)
						for(int mc=0; mc<monsterCols && found; mc++)
							if(monster[mr][mc]=='#'){
								assert(c[i+mr][j+mc]=='#' || c[i+mr][j+mc]=='O');
								c[i+mr][j+mc]='O';
							}
				}
			}
			
		if(overallFound){
			int noise=0;
			for(int i=0; i<nr; i++)
				for(int j=0; j<nc; j++)
					if(c[i][j]=='#')
						noise++;
			cout<<"noise="<<noise<<endl;
			break;
		}
	}
	
	return 0;
	
	/*assert(0);
	
	long long int prod=1;
	int q=0;
	for(int i=0; i<nTiles; i++){
		int k=0;
		for(int j=0; j<8; j++)
			if(cnt[margins[i][j]]<2)
				k++;
		if(k>=4){
			cout<<"corner tileNumber="<<tileNumber[i]<<endl;
			prod*=tileNumber[i];
			q++;
		}
	}
	assert(q==4);
	
	cout<<"prod="<<prod<<endl;
	
	//assert(0);
	
	//corner 0 is upper-left
	int corner0=-1;
	int corner0Orientation=-1;
	for(int i=0; i<nTiles; i++){
		int k=0;
		for(int j=0; j<8; j++)
			if(cnt[margins[i][j]]<2)
				k++;
		if(k>=4){
			corner0=i;
			break;
		}
	}
	assert(corner0>=0);
	for(int orient=0; orient<16; orient++){
		//cout<<"cnt[variants[corner0][orient][0]]+cnt[variants[corner0][orient][1]]+cnt[variants[corner0][orient][2]]+cnt[variants[corner0][orient][3]]="<<
		// cnt[variants[corner0][orient][0]]+cnt[variants[corner0][orient][1]]+cnt[variants[corner0][orient][2]]+cnt[variants[corner0][orient][3]]<<endl;
		//if(cnt[variants[corner0][orient][0]]+cnt[variants[corner0][orient][1]]+cnt[variants[corner0][orient][2]]+cnt[variants[corner0][orient][3]]==6){
		//	corner0Orientation=orient;
		//	break;
		//}
		//cout<<"cnt[variants[corner0][orient][0]]+cnt[variants[corner0][orient][3]]="<<cnt[variants[corner0][orient][0]]+cnt[variants[corner0][orient][3]]<<endl;
		if(cnt[variants[corner0][orient][0]]==1 && cnt[variants[corner0][orient][3]]==1 && cnt[variants[corner0][orient][1]]==2 && cnt[variants[corner0][orient][2]]==2){
			//assert(corner0Orientation==-1);
			corner0Orientation=orient;
			cout<<"orient="<<orient<<endl;
			//break; //goghi
		}
	}

	corner0Orientation=12; //goghi
	
	assert(corner0Orientation>=0);
	cout<<"corner0="<<corner0<<", corner0Orientation="<<corner0Orientation<<endl;
	
	cout<<"nDim="<<nDim<<endl;
	
	bool used[MAX_TILES];
	for(int i=0; i<nTiles; i++)
		used[i]=false;
	used[corner0]=true;
	
	int tilesMatrix[MAX_DIM][MAX_DIM];
	int tilesOrientation[MAX_DIM][MAX_DIM];
	
	tilesMatrix[0][0]=corner0;
	tilesOrientation[0][0]=corner0Orientation;
	
	cout<<"the upper-left corner cell is number "<<tileNumber[tilesMatrix[0][0]]<<", orientation is "<<tilesOrientation[0][0]<<endl;
	for(int j=1; j<nDim; j++){ //upper side
		bool found=false;
		for(int q=0; q<nTiles && !found; q++){
			if(!used[q]){
				for(int d=0; d<16 && !found; d++){
					if(variants[tilesMatrix[0][j-1]][tilesOrientation[0][j-1]][1]==variants[q][d][3]
					 //&& cnt[variants[q][d][0]]==1
					 && cnt[variants[q][d][1]]>=2 && cnt[variants[q][d][2]]>=2){
						found=true;
						tilesMatrix[0][j]=q;
						tilesOrientation[0][j]=d;
						//cout<<"found. j="<<j<<", q="<<q<<", d="<<d<<endl;
						used[q]=true;
						break;
					}
				}
			}
		}
		cout<<"j="<<j<<endl;
		assert(found);
		cout<<"for this j, the cell is number "<<tileNumber[tilesMatrix[0][j]]<<", orientation is "<<tilesOrientation[0][j]<<endl;
	}
	
	for(int i=1; i<nDim; i++){ //all the rest
		for(int j=0; j<nDim; j++){
			bool found=false;
			for(int q=0; q<nTiles && !found; q++){
				if(!used[q]){
					for(int d=0; d<16 && !found; d++){
						if(variants[tilesMatrix[i-1][j]][tilesOrientation[i-1][j]][2]==variants[q][d][0]){
							found=true;
							tilesMatrix[i][j]=q;
							tilesOrientation[i][j]=d;
							used[q]=true;
							break;
						}
					}
				}
			}
			assert(found);
		}
	}
	
	for(int i=0; i<nDim; i++){
		for(int j=0; j<nDim; j++){
			cout<<tileNumber[tilesMatrix[i][j]]<<" ";
		}
		cout<<endl;
	}
	
	return 0;*/
}
