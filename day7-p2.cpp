#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

const int MAXC=1024;

int nColors;
int adj[MAXC][MAXC];

unordered_map<string, int> colorToInt;
string intToColor[MAXC];

int nBags[MAXC];

int dfs(int node)
{
	if(nBags[node]>=0)
		return nBags[node];
		
	int res=0;
	for(int k=0; k<nColors; k++)
		if(adj[k][node]>0)
			res+=adj[k][node]*dfs(k);
			
	return res+1;
}

int main()
{
	//ifstream in("sample-input-1.txt");
	//ifstream in("sample-input-2.txt");
	ifstream in("input");
	
	string s;
	
	for(int i=0; i<MAXC; i++)
		for(int j=0; j<MAXC; j++)
			adj[i][j]=0;
	
	for(;;){
		getline(in, s);
		if(in.eof())
			break;
			
		int pos1=s.find("bags");
		string color=s.substr(0, pos1-1);
		cout<<"COLOR="<<color<<endl;
		//cout<<"color="<<color<<endl;
		int largeColor=-1;
		if(colorToInt.find(color)==colorToInt.end()){
			colorToInt.insert(make_pair(color, nColors));
			largeColor=nColors;
			intToColor[largeColor]=color;
			nColors++;
		}
		else{
			largeColor=colorToInt.find(color)->second;
		}
		assert(largeColor>=0);
		//cout<<"largeColor="<<largeColor<<endl;
		//cout<<"nColors="<<nColors<<endl;
		
		pos1=s.find("contain")+8;
		if(s.find("no other bags.", pos1)!=string::npos){
			cout<<"contains no other bags"<<endl<<endl;
			continue;
		}
		
		for(;;){
			int pos2=s.find(' ', pos1);
			int cnt=stoi(s.substr(pos1, pos2-pos1));
			//cout<<"cnt="<<cnt<<endl;
			pos1=pos2+1;
			pos2=s.find(" bag", pos1);
			string color=s.substr(pos1, pos2-pos1);
			
			int smallColor=-1;
			if(colorToInt.find(color)==colorToInt.end()){
				colorToInt.insert(make_pair(color, nColors));
				smallColor=nColors;
				intToColor[smallColor]=color;
				nColors++;
			}
			else{
				smallColor=colorToInt.find(color)->second;
			}
			assert(smallColor>=0);
			
			assert(adj[smallColor][largeColor]==0);
			adj[smallColor][largeColor]=cnt;
			
			cout<<"color="<<color<<endl;
			pos2+=3;
			if(cnt>=2)
				pos2++; // "bagS"
			pos2++;
			//cout<<s[pos2]<<endl;
			if(s[pos2]=='.')
				break;
			
			pos1=pos2+2;
			assert(pos1<int(s.size()));
			//cout<<"'"<<s[pos1]<<"'"<<endl;
		}
		
		cout<<endl;
	}
	
	assert(colorToInt.find("shiny gold")!=colorToInt.end());
	int node=colorToInt.find("shiny gold")->second;
	
	for(int i=0; i<nColors; i++)
		nBags[i]=-1;
	
	int result=dfs(node)-1; //-1 for shiny gold
	
	cout<<"result of day 7 part 2 is: "<<result<<endl;

	return 0;
}
