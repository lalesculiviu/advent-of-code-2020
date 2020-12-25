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
	
	int64 answerPart1=-1;
	
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
			answerPart1=k;
			break;
		}
		
		a.erase(a.begin());
		a.push_back(k);
	}
	
	assert(answerPart1>=0);
	
	in.close();
	//in.open("sample-input.txt");
	in.open("input");
	
	a.clear();
	
	for(;;){
		int64 k;
		in>>k;
		if(in.eof())
			break;
			
		a.push_back(k);
	}
	
	int i1=0;
	int i2=1;
	
	int answerFirst=-1;
	int answerSecond=-1;
	
	int64 sum=a[i1];
	for(;;){
		cout<<"i1="<<i1<<", i2="<<i2<<", sum="<<sum<<endl;
	
		if(sum==answerPart1 && i2>=i1+2){
			answerFirst=i1;
			answerSecond=i2;
		}

		sum+=a[i2];
		i2++;
		if(i2>=int(a.size()))
			break;
		
		while(sum>answerPart1 && i1<i2){
			sum-=a[i1];
			i1++;
		}
	}
	
	assert(answerFirst>=0 && answerSecond>=0);
	
	int64 m=-1;
	int64 M=-1;
	
	for(int i=answerFirst; i<answerSecond; i++){
		if(m==-1 || (m>=0 && m>a[i]))
			m=a[i];
		if(M==-1 || (M>=0 && M<a[i]))
			M=a[i];
	}
	
	cout<<"m="<<m<<", M="<<M<<endl;
	cout<<"answer to day 9 part 2 is "<<m+M<<endl;
	
	return 0;
}
