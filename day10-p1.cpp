#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	//ifstream in("sample-input-1.txt");
	//ifstream in("sample-input-2.txt");
	ifstream in("input");
	
	vector<int> joltages;
	joltages.push_back(0);
	
	for(;;){
		int k;
		in>>k;
		if(in.eof())
			break;
		joltages.push_back(k);
	}
	
	sort(joltages.begin(), joltages.end());
	
	int k=joltages[joltages.size()-1];
	joltages.push_back(k+3);
	
	int n1=0;
	int n3=0;
	
	for(size_t i=0; i<joltages.size()-1; i++)
		if(joltages[i+1]-joltages[i]==1)
			n1++;
		else if(joltages[i+1]-joltages[i]==3)
			n3++;
		else
			assert(joltages[i+1]-joltages[i]==2);
	
	cout<<"n1="<<n1<<", n3="<<n3<<endl;
	cout<<"day 10 part 1 result="<<n1*n3<<endl;
	
	return 0;
}
