#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

#include <cstring>

const int MAXW=15;
const int MAXZ=15;
const int MAXY=22;
const int MAXX=22;

const int STARTW=7;
const int STARTZ=7;
const int STARTY=7;
const int STARTX=7;

int a[MAXW][MAXZ][MAXY][MAXX];
int b[MAXW][MAXZ][MAXY][MAXX];

int sumNeigh(int w, int z, int y, int x)
{
	int sum=0;
	
	sum+=a[w][z-1][y-1][x-1];
	sum+=a[w][z-1][y-1][x];
	sum+=a[w][z-1][y-1][x+1];
	sum+=a[w][z-1][y][x-1];
	sum+=a[w][z-1][y][x];
	sum+=a[w][z-1][y][x+1];
	sum+=a[w][z-1][y+1][x-1];
	sum+=a[w][z-1][y+1][x];
	sum+=a[w][z-1][y+1][x+1];

	sum+=a[w][z][y-1][x-1];
	sum+=a[w][z][y-1][x];
	sum+=a[w][z][y-1][x+1];
	sum+=a[w][z][y][x-1];
//	sum+=a[w][z][y][x];
	sum+=a[w][z][y][x+1];
	sum+=a[w][z][y+1][x-1];
	sum+=a[w][z][y+1][x];
	sum+=a[w][z][y+1][x+1];

	sum+=a[w][z+1][y-1][x-1];
	sum+=a[w][z+1][y-1][x];
	sum+=a[w][z+1][y-1][x+1];
	sum+=a[w][z+1][y][x-1];
	sum+=a[w][z+1][y][x];
	sum+=a[w][z+1][y][x+1];
	sum+=a[w][z+1][y+1][x-1];
	sum+=a[w][z+1][y+1][x];
	sum+=a[w][z+1][y+1][x+1];


	sum+=a[w-1][z-1][y-1][x-1];
	sum+=a[w-1][z-1][y-1][x];
	sum+=a[w-1][z-1][y-1][x+1];
	sum+=a[w-1][z-1][y][x-1];
	sum+=a[w-1][z-1][y][x];
	sum+=a[w-1][z-1][y][x+1];
	sum+=a[w-1][z-1][y+1][x-1];
	sum+=a[w-1][z-1][y+1][x];
	sum+=a[w-1][z-1][y+1][x+1];

	sum+=a[w-1][z][y-1][x-1];
	sum+=a[w-1][z][y-1][x];
	sum+=a[w-1][z][y-1][x+1];
	sum+=a[w-1][z][y][x-1];
	sum+=a[w-1][z][y][x];
	sum+=a[w-1][z][y][x+1];
	sum+=a[w-1][z][y+1][x-1];
	sum+=a[w-1][z][y+1][x];
	sum+=a[w-1][z][y+1][x+1];

	sum+=a[w-1][z+1][y-1][x-1];
	sum+=a[w-1][z+1][y-1][x];
	sum+=a[w-1][z+1][y-1][x+1];
	sum+=a[w-1][z+1][y][x-1];
	sum+=a[w-1][z+1][y][x];
	sum+=a[w-1][z+1][y][x+1];
	sum+=a[w-1][z+1][y+1][x-1];
	sum+=a[w-1][z+1][y+1][x];
	sum+=a[w-1][z+1][y+1][x+1];


	sum+=a[w+1][z-1][y-1][x-1];
	sum+=a[w+1][z-1][y-1][x];
	sum+=a[w+1][z-1][y-1][x+1];
	sum+=a[w+1][z-1][y][x-1];
	sum+=a[w+1][z-1][y][x];
	sum+=a[w+1][z-1][y][x+1];
	sum+=a[w+1][z-1][y+1][x-1];
	sum+=a[w+1][z-1][y+1][x];
	sum+=a[w+1][z-1][y+1][x+1];

	sum+=a[w+1][z][y-1][x-1];
	sum+=a[w+1][z][y-1][x];
	sum+=a[w+1][z][y-1][x+1];
	sum+=a[w+1][z][y][x-1];
	sum+=a[w+1][z][y][x];
	sum+=a[w+1][z][y][x+1];
	sum+=a[w+1][z][y+1][x-1];
	sum+=a[w+1][z][y+1][x];
	sum+=a[w+1][z][y+1][x+1];

	sum+=a[w+1][z+1][y-1][x-1];
	sum+=a[w+1][z+1][y-1][x];
	sum+=a[w+1][z+1][y-1][x+1];
	sum+=a[w+1][z+1][y][x-1];
	sum+=a[w+1][z+1][y][x];
	sum+=a[w+1][z+1][y][x+1];
	sum+=a[w+1][z+1][y+1][x-1];
	sum+=a[w+1][z+1][y+1][x];
	sum+=a[w+1][z+1][y+1][x+1];

	return sum;
}

int main()
{
	ifstream in("input-basic.txt");
//	ifstream in("input");
	
	for(int w=0; w<MAXW; w++)
		for(int z=0; z<MAXZ; z++)
			for(int y=0; y<MAXX; y++)
				for(int x=0; x<MAXX; x++)
					a[w][z][y][x]=/*b[z][y][x]=*/0;
	
	char str[257];
	int y=STARTY;
	for(;;){
		in.getline(str, 256);
		if(in.eof())
			break;
		//cout<<"str="<<str<<endl;
		for(int x=STARTX; x<int(strlen(str))+STARTX; x++)
			if(str[x-STARTX]=='#')
				a[STARTW][STARTZ][y][x]=1;
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
		for(int w=1; w<MAXW-1; w++){
			for(int z=1; z<MAXZ-1; z++){
				for(int y=1; y<MAXY-1; y++){
					for(int x=1; x<MAXX-1; x++){
						/*if(cycle==0 && z==7 && y==9 && x==7){
							cout<<"a[z][y][x]="<<a[z][y][x]<<endl;
							cout<<"b[z][y][x]="<<b[z][y][x]<<endl;
							cout<<"sumNeigh(z, y, x)="<<sumNeigh(z, y, x)<<endl;
						}*/
						if(a[w][z][y][x]==1){
							int k=sumNeigh(w, z, y, x);
							if(k==2 || k==3)
									b[w][z][y][x]=1;
							else
								b[w][z][y][x]=0;
						}
						else{
							assert(a[w][z][y][x]==0);
							int k=sumNeigh(w, z, y, x);
							if(k==3)
								b[w][z][y][x]=1;
							else
								b[w][z][y][x]=0;
						}
					}
				}
			}
		}
		
		for(int w=1; w<MAXW-1; w++)
			for(int z=1; z<MAXZ-1; z++)
				for(int y=1; y<MAXY-1; y++)
					for(int x=1; x<MAXX-1; x++)
						a[w][z][y][x]=b[w][z][y][x];
	
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
	for(int w=0; w<MAXW; w++)
		for(int z=0; z<MAXZ; z++)
			for(int y=0; y<MAXY; y++)
				for(int x=0; x<MAXX; x++)
					if(a[w][z][y][x]==1)
						sum++;
					
	cout<<"sum="<<sum<<endl;

	return 0;
}
