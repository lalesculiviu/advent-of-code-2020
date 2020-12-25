#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long int int64;

int main()
{
	//ifstream in("sample-input.txt");
	//int nPreamble=5; //for sample-input.txt
	
	ifstream in("input");
	int nPreamble=25; //for input
	
	vector<int64> a;
	
	for(int i=0; i<nPreamble; i++){
		int64 k;
		in>>k;
		assert(!in.eof());
		a.push_back(k);
		//cout<<"Preamble - i="<<i<<endl<<", k="<<k<<endl;
	}
	
	for(;;){
		int64 k;
		in>>k;
		if(in.eof())
			break;
		
		assert(nPreamble==int(a.size()));
		bool found=false;
		for(int i=0; i<nPreamble-1 && !found; i++)
			for(int j=i+1; j<nPreamble && !found; j++)
				if(a[i]+a[j]==k)
					found=true;
		
		if(!found){
			cout<<"day 9 part 1 answer is "<<k<<endl;
			return 0;
		}
		
		a.erase(a.begin());
		a.push_back(k);
	}
	
	return 0;
}
