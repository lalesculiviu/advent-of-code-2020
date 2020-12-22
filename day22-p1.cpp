#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <cassert>

using namespace std;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	string str;
	
	queue<int> q1;
	queue<int> q2;
	
	int crtPlayer=1;
	
	while(getline(in, str)){
		if(str=="Player 1:")
			continue;
		else if(str=="")
			continue;
		else if(str=="Player 2:")
			crtPlayer=2;
		else{
			int card=stoi(str);
			if(crtPlayer==1)
				q1.push(card);
			else
				q2.push(card);
		}
	}
	
	while(!q1.empty() && !q2.empty()){
		int card1=q1.front();
		q1.pop();
		int card2=q2.front();
		q2.pop();
		if(card1>card2){
			q1.push(card1);
			q1.push(card2);
		}
		else{
			assert(card2>card1);
			q2.push(card2);
			q2.push(card1);
		}
	}
	
	queue<int> *wq;
	
	if(q1.empty()){
		assert(!q2.empty());
		wq=&q2;
	}
	else{
		wq=&q1;
	}
	
	int result=0;
	
	for(size_t i=wq->size(); i>=1; i--){
		result+=i*wq->front();
		wq->pop();
	}
	
	cout<<"result="<<result<<endl;
	
	return 0;
}
