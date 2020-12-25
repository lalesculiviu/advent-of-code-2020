#include <cassert>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int NOP=0;
const int ACC=1;
const int JMP=2;

const int MAX=1024;

int op[MAX];
int arg[MAX];
int nInstructions;

bool visited[MAX];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	string s;
	
	nInstructions=0;
	
	for(;;){
		getline(in, s);
		if(in.eof())
			break;
			
		if(s[0]=='n'){
			op[nInstructions]=NOP;
		}
		else if(s[0]=='a'){
			op[nInstructions]=ACC;
			arg[nInstructions]=stoi(s.substr(4));
		}
		else if(s[0]=='j'){
			op[nInstructions]=JMP;
			arg[nInstructions]=stoi(s.substr(4));
		}
		else{
			assert(0);
		}
		
		nInstructions++;
	}
	
	int acc=0;
	for(int i=0; i<nInstructions; i++)
		visited[i]=false;
	int crt=0;
	for(;;){
		//cout<<"acc="<<acc<<", crt="<<crt<<endl;
		assert(crt<nInstructions);
		if(visited[crt])
			break;
		visited[crt]=true;
		if(op[crt]==NOP){
			cout<<"crt="<<crt<<", acc="<<acc<<", NOP"<<endl;
			crt++;
		}
		else if(op[crt]==ACC){
			cout<<"crt="<<crt<<", acc="<<acc<<", ACC "<<arg[crt]<<endl;
			acc+=arg[crt];
			crt++;
		}
		else if(op[crt]==JMP){
			cout<<"crt="<<crt<<", acc="<<acc<<", JMP "<<arg[crt]<<endl;
			crt+=arg[crt];
		}
	}
	
	cout<<"day 8 part 1 answer="<<acc<<endl;

	return 0;
}
