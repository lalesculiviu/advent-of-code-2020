#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	//fstream in("sample-input.txt");
	fstream in("input");
	
	vector<int> a;
	
	for(;;){
		int k;
		in>>k;
		if(in.eof())
			break;
		a.push_back(k);
	}
	
	sort(a.begin(), a.end());
	
	for(int k=0; k<int(a.size()); k++){
		int searchedNumber=2020-a[k];
		if(searchedNumber<=0 || searchedNumber>2020){
			assert(0);
			continue;
		}
	
		int i=0;
		int j=int(a.size())-1;
		while(i<j){
			if(a[i]+a[j]==searchedNumber && i!=k && j!=k){
				cout<<"The answer to day 1 part 2 is: "<<a[i]*a[j]*a[k]<<endl;
				return 0;
			}
			else if(a[i]+a[j]<searchedNumber){
				i++;
			}
			else{
				assert(a[i]+a[j]>searchedNumber);
				j--;
			}
		}
	}

	return 0;
}
