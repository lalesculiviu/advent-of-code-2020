#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

#include <cstring>

const int MAXZ=15;
const int MAXY=22;
const int MAXX=22;

const int STARTZ=7;
const int STARTY=7;
const int STARTX=7;

int a[MAXZ][MAXY][MAXX];
int b[MAXZ][MAXY][MAXX];

int sumNeigh(int z, int y, int x)
{
	int sum=0;
	
	sum+=a[z-1][y-1][x-1];
	sum+=a[z-1][y-1][x];
	sum+=a[z-1][y-1][x+1];
	sum+=a[z-1][y][x-1];
	sum+=a[z-1][y][x];
	sum+=a[z-1][y][x+1];
	sum+=a[z-1][y+1][x-1];
	sum+=a[z-1][y+1][x];
	sum+=a[z-1][y+1][x+1];

	sum+=a[z][y-1][x-1];
	sum+=a[z][y-1][x];
	sum+=a[z][y-1][x+1];
	sum+=a[z][y][x-1];
	sum+=a[z][y][x+1];
	sum+=a[z][y+1][x-1];
	sum+=a[z][y+1][x];
	sum+=a[z][y+1][x+1];

	sum+=a[z+1][y-1][x-1];
	sum+=a[z+1][y-1][x];
	sum+=a[z+1][y-1][x+1];
	sum+=a[z+1][y][x-1];
	sum+=a[z+1][y][x];
	sum+=a[z+1][y][x+1];
	sum+=a[z+1][y+1][x-1];
	sum+=a[z+1][y+1][x];
	sum+=a[z+1][y+1][x+1];

	return sum;
}

int main()
{
//	ifstream in("input-basic.txt");
	ifstream in("input");
	
	for(int z=0; z<MAXZ; z++)
		for(int y=0; y<MAXX; y++)
			for(int x=0; x<MAXX; x++)
				a[z][y][x]=/*b[z][y][x]=*/0;
	
	char str[257];
	int y=STARTY;
	for(;;){
		in.getline(str, 256);
		if(in.eof())
			break;
		//cout<<"str="<<str<<endl;
		for(int x=STARTX; x<int(strlen(str))+STARTX; x++)
			if(str[x-STARTX]=='#')
				a[STARTZ][y][x]=1;
		y++;
	}

	/*cout<<"initial:"<<endl;

	for(int z=0; z<MAXZ; z++){
		cout<<"z="<<z<<endl;
		cout<<"  012345678901234567890123456789"<<endl;
		for(int y=0; y<MAXY; y++){
			cout<<y%10<<" ";
			for(int x=0; x<MAXX; x++){
				if(a[z][y][x]==1)
					cout<<"#";
				else
					cout<<".";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	cout<<endl;*/
	
	for(int cycle=0; cycle<6; cycle++){
		for(int z=1; z<MAXZ-1; z++){
			for(int y=1; y<MAXY-1; y++){
				for(int x=1; x<MAXX-1; x++){
					/*if(cycle==0 && z==7 && y==9 && x==7){
						cout<<"a[z][y][x]="<<a[z][y][x]<<endl;
						cout<<"b[z][y][x]="<<b[z][y][x]<<endl;
						cout<<"sumNeigh(z, y, x)="<<sumNeigh(z, y, x)<<endl;
					}*/
					if(a[z][y][x]==1){
						int k=sumNeigh(z, y, x);
						if(k==2 || k==3)
							b[z][y][x]=1;
						else
							b[z][y][x]=0;
					}
					else{
						assert(a[z][y][x]==0);
						int k=sumNeigh(z, y, x);
						if(k==3)
							b[z][y][x]=1;
						else
							b[z][y][x]=0;
					}
				}
			}
		}
		
		for(int z=1; z<MAXZ-1; z++)
			for(int y=1; y<MAXY-1; y++)
				for(int x=1; x<MAXX-1; x++)
					a[z][y][x]=b[z][y][x];

		/*cout<<"cycle="<<cycle<<endl;

		for(int z=0; z<MAXZ; z++){
			cout<<"z="<<z<<endl;
			cout<<"  012345678901234567890123456789"<<endl;
			for(int y=0; y<MAXY; y++){
				cout<<y%10<<" ";
				for(int x=0; x<MAXX; x++){
					if(a[z][y][x]==1)
						cout<<"#";
					else
						cout<<".";
				}
				cout<<endl;
			}
			cout<<endl;
		}
		
		cout<<endl;*/
	}

	int sum=0;
	for(int z=0; z<MAXZ; z++)
		for(int y=0; y<MAXY; y++)
			for(int x=0; x<MAXX; x++)
				if(a[z][y][x]==1)
					sum++;
					
	cout<<"sum="<<sum<<endl;

	return 0;
}
