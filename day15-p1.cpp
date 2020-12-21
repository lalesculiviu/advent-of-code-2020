#include <cassert>
#include <iostream>
using namespace std;

const int N=30000000;

int a[N+1];
int b_first[N+1];
int b_second[N+1];

int main()
{
	a[1]=2;
	a[2]=0;
	a[3]=1;
	a[4]=9;
	a[5]=5;
	a[6]=19;
	/*a[1]=0;
	a[2]=3;
	a[3]=6;*/
	
	for(int i=0; i<=N; i++)
		b_first[i]=b_second[i]=0;
	for(int i=1; i<=6; i++)
		b_first[a[i]]=i;
	
	for(int i=7; i<=N; i++){
		//cout<<"BEGIN: b_first[0]="<<b_first[0]<<", b_second[0]="<<b_second[0]<<endl;
	
		if(b_second[a[i-1]]==0){
			//cout<<"i="<<i<<", 1."<<endl;
			a[i]=0;
			b_second[a[i]]=b_first[a[i]];
			b_first[a[i]]=i;
		}
		else if(b_first[a[i-1]]==0){
			//cout<<"i="<<i<<", 2."<<endl;
			a[i]=0;
			b_first[a[i]]=i;
		}
		else{
			//cout<<"i="<<i<<", 3."<<endl;
			a[i]=b_first[a[i-1]]-b_second[a[i-1]];
			b_second[a[i]]=b_first[a[i]];
			b_first[a[i]]=i;
		}
		//cout<<"i="<<i<<", a[i]="<<a[i]<<", a[i-1]="<<a[i-1]<<", b_first[a[i-1]]="<<b_first[a[i-1]]<<", b_second[a[i-1]]="<<b_second[a[i-1]]<<endl;

		//cout<<"END: b_first[0]="<<b_first[0]<<", b_second[0]="<<b_second[0]<<endl;

		//cout<<endl;
	}
	
	cout<<"a["<<N<<"]="<<a[N]<<endl;

	return 0;
}
