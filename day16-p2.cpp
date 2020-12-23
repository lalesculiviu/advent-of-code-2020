#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool correct[1000];

int ranges[20][2][2];
int nRanges;

vector<int> correctTickets[1000];
int nCorrectTickets;

int main()
{
	//ifstream in("sample-input.txt");
	//ifstream in("sample-input-p2.txt");
	ifstream in("input");
	
	string s;
	
	for(int i=0; i<=999; i++)
		correct[i]=false;
	
	nRanges=0;
	
	for(;;){
		getline(in, s);
		
		if(s.empty())
			break;
		
		assert(!in.eof());
		
		int pos1=s.find(':', 0);
		pos1+=2;
		int pos2=s.find('-', pos1);
		int fr1=stoi(s.substr(pos1, pos2-pos1));
		ranges[nRanges][0][0]=fr1;
		//cout<<"fr1="<<fr1<<endl;
		
		pos1=pos2+1;
		pos2=s.find(' ', pos1);
		int fr2=stoi(s.substr(pos1, pos2-pos1));
		ranges[nRanges][0][1]=fr2;
		//cout<<"fr2="<<fr2<<endl;
		
		for(int i=fr1; i<=fr2; i++)
			correct[i]=true;
		
		pos1=pos2+4;
		pos2=s.find('-', pos1);
		int sr1=stoi(s.substr(pos1, pos2-pos1));
		ranges[nRanges][1][0]=sr1;
		//cout<<"sr1="<<sr1<<endl;

		pos1=pos2+1;
		pos2=s.size();
		int sr2=stoi(s.substr(pos1, pos2-pos1));
		ranges[nRanges][1][1]=sr2;
		//cout<<"sr2="<<sr2<<endl;

		for(int i=sr1; i<=sr2; i++)
			correct[i]=true;
			
		nRanges++;
	}
	
	getline(in, s);
	assert(s=="your ticket:");
	getline(in, s);
	getline(in, s);
	getline(in, s);
	assert(s=="nearby tickets:");
	
	int result=0;
	
	nCorrectTickets=0;
	
	for(;;){
		getline(in, s);
		if(in.eof())
			break;
			
		int pos1=0;
		bool crtTicketValid=true;
		vector<int> a;
		for(;;){
			size_t pos2=s.find(',', pos1);
			if(pos2==string::npos){
				int k=stoi(s.substr(pos1, s.size()-pos1));
				a.push_back(k);
				if(!correct[k]){
					result+=k;
					crtTicketValid=false;
				}

				break;
			}
			int k=stoi(s.substr(pos1, pos2-pos1));
			a.push_back(k);
			if(!correct[k]){
				result+=k;
				crtTicketValid=false;
			}
			
			pos1=pos2+1;
		}
		
		if(crtTicketValid){
			correctTickets[nCorrectTickets++]=a;
		}
	}
	
	//cout<<"result part 1="<<result<<endl;
	
	cout<<"nRanges="<<nRanges<<endl;
	cout<<"nCorrectTickets="<<nCorrectTickets<<endl;
	
	for(int i=0; i<nRanges; i++){
		for(int k=0; k<nRanges; k++){
			int r=-1;
			bool correct=true;
			for(int j=0; j<nCorrectTickets; j++){
				if(!((correctTickets[j][i]>=ranges[k][0][0] && correctTickets[j][i]<=ranges[k][0][1])
				 || (correctTickets[j][i]>=ranges[k][1][0] && correctTickets[j][i]<=ranges[k][1][1]))){
					correct=false;
					break;
				}
			}
		
			if(correct){
				r=k;
				cout<<"correct, range "<<r+1<<" corresponds to ticket column "<<i+1<<endl;
			}
		}
		cout<<endl;
	}

	return 0;
}
