#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int val[1000001]; //val[0] is unused
//int pred[10]; //pred[0] is unused
int succ[1000001]; //succ[0] is unused
int inv[1000001];

int main()
{
	//string input="389125467"; //sample input
	string input="974618352"; //official input
	
	for(int i=1; i<=9; i++){
		val[i]=input[i-1]-'0';
		inv[val[i]]=i;
		
		/*if(i>=2)
			pred[i]=i-1;
		else
			pred[i]=9;*/
			
		//if(i<=8)
			succ[i]=i+1;
		//else
		//	succ[i]=1;
	}
	for(int i=10; i<=999999; i++){
		val[i]=i;
		inv[i]=i;
		succ[i]=i+1;
	}
	val[1000000]=1000000;
	inv[1000000]=1000000;
	succ[1000000]=1;
	
	int crt=val[1];
	int crtPos=1;
	
	for(int iter=0; iter<10000000; iter++){
		//debug output
		/*int _crtPos=crtPos;
		for(int j=1; j<=9; j++){
			cout<<val[_crtPos];
			_crtPos=succ[_crtPos];
		}
		cout<<endl;*/

		int dest=-1;
		int destPos=-1;
		dest=crt;
		for(;;){
			dest--;
			if(dest<1)
				dest=1000000;
			if(dest!=val[succ[crtPos]] && dest!=val[succ[succ[crtPos]]] && dest!=val[succ[succ[succ[crtPos]]]])
				break;
		}
		
		assert(dest>=1 && dest<=1000000);
		
		destPos=inv[dest];
		/*int k=destPos;
		for(int i=1; i<=1000000; i++)
			if(dest==val[i])
				destPos=i;*/
		//cout<<"dest="<<dest<<", k="<<k<<", destPos="<<destPos<<endl;
		//assert(k==destPos);
				
		assert(destPos>=1 && destPos<=1000000);
		
		//cout<<"crt="<<crt<<", crtPos="<<crtPos<<endl;
		//cout<<"dest="<<dest<<", destPos="<<destPos<<endl;
		
		int i1=succ[crtPos];
		int i2=succ[succ[i1]];
		
		//cout<<"i1="<<i1<<", i2="<<i2<<endl;
		
		succ[crtPos]=succ[i2];
		//pred[succ[i2]]=crtPos;
		
		//pred[succ[destPos]]=i2;
		int t=succ[destPos];
		succ[destPos]=i1;

		//pred[i1]=destPos;
		succ[i2]=t; //succ[destPos];
		
		crtPos=succ[crtPos];
		crt=val[crtPos];

		//cout<<"crt="<<crt<<", crtPos="<<crtPos<<endl;
	}
	
	int i;
	int j=inv[1];
	for(i=1; i<=1000000; i++)
		if(val[i]==1)
			break;
	assert(i<=1000000);
	
	assert(i==j);
	
	crtPos=succ[i];
	
	long long int result=1;
	
	for(int j=0; j<2; j++){
		cout<<val[crtPos]<<" ";
		result*=val[crtPos];
		crtPos=succ[crtPos];
	}
	
	cout<<endl;
	
	cout<<"result="<<result<<endl;
	
	//cout<<"after 934001 comes "<<val[succ[inv[934001]]]<<endl;
	
	return 0;
}
