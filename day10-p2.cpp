#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int int64;

const int MAX=256;
int64 a[MAX];

bool exists[MAX];

int main()
{
	//ifstream in("sample-input-1.txt");
	//ifstream in("sample-input-2.txt");
	ifstream in("input");
	
	vector<int> joltages;
	joltages.push_back(0);
	
	for(int i=1; i<MAX; i++)
		exists[i]=false;
	exists[0]=true;
	
	for(;;){
		int k;
		in>>k;
		if(in.eof())
			break;
		joltages.push_back(k);
		exists[k]=true;
	}
	
	sort(joltages.begin(), joltages.end());
	
	int k=joltages[joltages.size()-1];
	joltages.push_back(k+3);
	exists[k+3]=true;
	
	/*int n1=0;
	int n3=0;
	
	for(size_t i=0; i<joltages.size()-1; i++)
		if(joltages[i+1]-joltages[i]==1)
			n1++;
		else if(joltages[i+1]-joltages[i]==3)
			n3++;
		else
			assert(joltages[i+1]-joltages[i]==2);
	
	cout<<"n1="<<n1<<", n3="<<n3<<endl;
	cout<<"day 10 part 1 result="<<n1*n3<<endl;*/
	
	int m=k+3;
	for(int i=1; i<=m; i++)
		a[i]=0;
	a[0]=1;
	
	for(int i=1; i<=m; i++){
		a[i]=0;
		if(exists[i-1])
			a[i]+=a[i-1];
		if(i>=2 && exists[i-2])
			a[i]+=a[i-2];
		if(i>=3 && exists[i-3])
			a[i]+=a[i-3];
	}
	
	cout<<"day 10 part 2 answer="<<a[m]<<endl;
	
	return 0;
}
