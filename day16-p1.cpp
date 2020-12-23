#include <cassert>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

bool correct[1000];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	string s;
	
	for(int i=1; i<=999; i++)
		correct[i]=false;
	
	for(;;){
		getline(in, s);
		
		if(s.empty())
			break;
		
		assert(!in.eof());
		
		int pos1=s.find(':', 0);
		pos1+=2;
		int pos2=s.find('-', pos1);
		int fr1=stoi(s.substr(pos1, pos2-pos1));
		//cout<<"fr1="<<fr1<<endl;
		
		pos1=pos2+1;
		pos2=s.find(' ', pos1);
		int fr2=stoi(s.substr(pos1, pos2-pos1));
		//cout<<"fr2="<<fr2<<endl;
		
		for(int i=fr1; i<=fr2; i++)
			correct[i]=true;
		
		pos1=pos2+4;
		pos2=s.find('-', pos1);
		int sr1=stoi(s.substr(pos1, pos2-pos1));
		//cout<<"sr1="<<sr1<<endl;

		pos1=pos2+1;
		pos2=s.size();
		int sr2=stoi(s.substr(pos1, pos2-pos1));
		//cout<<"sr2="<<sr2<<endl;

		for(int i=sr1; i<=sr2; i++)
			correct[i]=true;
	}
	
	getline(in, s);
	assert(s=="your ticket:");
	getline(in, s);
	getline(in, s);
	getline(in, s);
	assert(s=="nearby tickets:");
	
	int result=0;
	
	for(;;){
		getline(in, s);
		if(in.eof())
			break;
			
		int pos1=0;
		for(;;){
			size_t pos2=s.find(',', pos1);
			if(pos2==string::npos){
				int k=stoi(s.substr(pos1, s.size()-pos1));
				if(!correct[k])
					result+=k;

				break;
			}
			int k=stoi(s.substr(pos1, pos2-pos1));
			if(!correct[k])
				result+=k;
				
			pos1=pos2+1;
		}
	}
	
	cout<<"result="<<result<<endl;

	return 0;
}
