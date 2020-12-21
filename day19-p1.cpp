#include <cassert>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_RULES=200;

int nrules;

vector<int> leftPossibility[MAX_RULES];
vector<int> rightPossibility[MAX_RULES];
int aorb[MAX_RULES]; //-1 means not a letter, 0 means "a", 1 means "b"

char strings[600][256+1];

int nstrings;

int a[MAX_RULES][256+1][256+1]; //-1 = not init, 0 = false, 1 = true

char crtstr[256+1];

bool rec(int nrule, int start, int end)
{
	//cout<<"crtstr="<<crtstr<<", nrule="<<nrule<<", start="<<start<<", end="<<end<<endl;

	if(a[nrule][start][end]>=0){
		//cout<<"already computed: a[nrule][start][end]="<<a[nrule][start][end]<<endl;
		return a[nrule][start][end];
	}
	else if(aorb[nrule]!=-1){
		if(end-start==1 && aorb[nrule]==0 && crtstr[start]=='a'){
			//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
			return (a[nrule][start][end]=1);
		}
		else if(end-start==1 && aorb[nrule]==1 && crtstr[start]=='b'){
			//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
			return (a[nrule][start][end]=1);
		}
		else{
			//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 0"<<endl;
			return (a[nrule][start][end]=0);
		}
	}
	else{
		//if(nrule==3 && start==1 && end==3)
		//	assert(0);
	
		if(leftPossibility[nrule].size()==2){
			assert(leftPossibility[nrule].size()==2);
			int p1=leftPossibility[nrule][0];
			int p2=leftPossibility[nrule][1];
			for(int q=1; q<end-start; q++)
				if(rec(p1, start, start+q) && rec(p2, start+q, end)){
					//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
					return (a[nrule][start][end]=1);
				}
		}
		else{
			assert(leftPossibility[nrule].size()==1);
			int p1=leftPossibility[nrule][0];
			if(rec(p1, start, end)){
				//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
				return (a[nrule][start][end]=1);
			}
		}
		
		if(rightPossibility[nrule].size()>0){
			if(rightPossibility[nrule].size()==2){
				assert(rightPossibility[nrule].size()==2);
				
				int p1=rightPossibility[nrule][0];
				int p2=rightPossibility[nrule][1];
				for(int q=1; q<end-start; q++)
					if(rec(p1, start, start+q) && rec(p2, start+q, end)){
						//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
						return (a[nrule][start][end]=1);
					}
			}
			else{
				assert(rightPossibility[nrule].size()==1);
				
				int p1=rightPossibility[nrule][0];
				if(rec(p1, start, end)){
					//cout<<"a[nrule][start][end]="<<a[nrule][start][end]<<", returning 1"<<endl;
					return (a[nrule][start][end]=1);
				}
			}
		}
		
		//cout<<"returning 0"<<endl;
		return (a[nrule][start][end]=0);
	}
}

bool accepted(char str[256+1])
{
	for(int i=0; i<nrules; i++)
		for(int j=0; j<257; j++)
			for(int k=0; k<257; k++)
				a[i][j][k]=-1;
	//memset(a, sizeof(a), -1);
	strcpy(crtstr, str);
	return rec(0, 0, strlen(str));
}

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	nrules=nstrings=0;

	char s[256+1];
	
	for(;;){
		in.getline(s, 256);
		
		//cout<<"s="<<s<<endl;
		
		if(s[0]=='\0')
			break;

		char s2[256+1];
		int i=0;
		while(s[i]!=':'){
			s2[i]=s[i];
			i++;
		}
		s2[i]='\0';
		i+=2;
		int r=atoi(s2);
		//cout<<"r="<<r<<endl;
		aorb[r]=-1;
		if(nrules<r)
			nrules=r;
		bool left=true;
		int j=0;
		for(;;){
			s2[j]=s[i];
			if(s[i]==' ' || s[i]=='\0'){
				s2[j]='\0';
				j=0;
				int p=atoi(s2);
				if(left)
					leftPossibility[r].push_back(p);
				else
					rightPossibility[r].push_back(p);
				i++;
			}
			else if(s[i]=='\"'){
				assert(aorb[r]==-1);
				if(s[i+1]=='a'){
					aorb[r]=0;
				}
				else{
					assert(s[i+1]=='b');
					aorb[r]=1;
				}
				i+=3;
			}
			else if(s[i]=='|'){
				assert(left);
				left=false;
				i+=2;
				j=0;
			}
			else{
				assert(s[i]>='0' && s[i]<='9');
				i++;
				j++;
			}
			if(s[i]=='\0')
				break;
		}
		assert(s[i]=='\0');
		s2[j]='\0';
		j=0;
		int p=atoi(s2);
		if(left)
			leftPossibility[r].push_back(p);
		else
			rightPossibility[r].push_back(p);
		i++;
	}
	
	for(nstrings=0; ; nstrings++){
		char s[256+1];
		in.getline(s, 256);
		if(in.eof())
			break;
		strcpy(strings[nstrings], s);
	}
	
	nrules++;
	for(int i=0; i<nrules; i++){
		if(aorb[i]==-1){
			cout<<"i="<<i<<", rulesLeft[i]=";
			for(size_t j=0; j<leftPossibility[i].size(); j++)
				cout<<leftPossibility[i][j]<<" ";
			cout<<", rulesRight[i]=";
			for(size_t j=0; j<rightPossibility[i].size(); j++)
				cout<<rightPossibility[i][j]<<" ";
			cout<<endl;
		}
		else if(aorb[i]==0){
			cout<<"i="<<i<<", aorb=\"a\""<<endl;
		}
		else if(aorb[i]==1){
			cout<<"i="<<i<<", aorb=\"b\""<<endl;
		}
	}
	
	cout<<endl;
	
	for(int i=0; i<nstrings; i++)
		cout<<"i="<<i<<", strings[i]="<<strings[i]<<endl;
		
	int cnt=0;
	for(int i=0; i<nstrings; i++){
		if(accepted(strings[i])){
			cnt++;
			cout<<"Accepted: "<<strings[i]<<endl;
		}
		else{
			cout<<"NOT accepted: "<<strings[i]<<endl;
		}
	}
	cout<<"cnt="<<cnt<<endl;
	
	return 0;
}
