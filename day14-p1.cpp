#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

typedef long long int int64;

unordered_map<int, int64> memory;

const int N_BITS=36;

int64 m0, m1;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	string s;
	
	m1=0;
	m0=(1LL<<N_BITS)-1;
	
	for(;;){
		getline(in, s);
		
		if(in.eof())
			break;
			
		if(s[1]=='a'){ //new mask
			m1=0;
			m0=(1LL<<N_BITS)-1;
			for(size_t i=7; i<s.size(); i++){
				if(s[i]=='0'){
					m0 -= 1LL<<(s.size()-i-1);
				}
				else if(s[i]=='1'){
					m1 += 1LL<<(s.size()-i-1);
				}
				else{
					assert(s[i]=='X');
					//do nothing
				}
			}
			cout<<"m1="<<m1<<endl;
			cout<<"m0="<<m0<<endl;

			assert(m1>=0 && m1<((1LL<<N_BITS)-1));
			assert(m0>=0 && m0<((1LL<<N_BITS)-1));
		}
		else{
			assert(s[1]=='e');
			int pos1=4;
			int pos2=s.find(']', 4);
			int k=stoi(s.substr(pos1, pos2-pos1));
			cout<<"k="<<k;
			pos1=s.find('=', pos2)+2;
			int64 k2=stoll(s.substr(pos1, s.size()-pos1));
			cout<<", k2="<<k2<<endl;
			
			int64 newVal = (k2 & m0) | m1;
			cout<<"(k2&m0)|m1="<<((k2 & m0) | m1)<<", (k2|m1)&m0="<<((k2 | m1) & m0)<<endl;
			assert(newVal == ((k2 | m1) & m0));
			
			const auto& it=memory.find(k);
			if(it==memory.end())
				memory.insert(make_pair(k, newVal));
			else
				it->second=newVal;
		}
	}
	
	int64 answer=0;
	
	for(const auto& it : memory){
		answer+=it.second;
	}
	
	cout<<"part 1 answer="<<answer<<endl;

	return 0;
}
