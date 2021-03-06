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
	
	int i=0;
	int j=int(a.size())-1;
	while(i<j){
		if(a[i]+a[j]==2020){
			cout<<"The answer to day 1 part 1 is: "<<a[i]*a[j]<<endl;
			return 0;
		}
		else if(a[i]+a[j]<2020){
			i++;
		}
		else{
			assert(a[i]+a[j]>2020);
			j--;
		}
	}

	return 0;
}
