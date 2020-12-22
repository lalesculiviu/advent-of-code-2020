#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <cassert>
#include <set>
#include <vector>
#include <utility>

using namespace std;

int gameWinner(int level, const queue<int>& _q1, const queue<int>& _q2)
{
	queue<int> q1(_q1);
	queue<int> q2(_q2);
	
	if(level>0){ //https://www.reddit.com/r/adventofcode/comments/khyjgv/2020_day_22_solutions/ , improvement by curious_sapi3n
		queue<int> q1(_q1);
		queue<int> q2(_q2);
		int ts=int(q1.size())+int(q2.size());
		int mx=-1;
		int mxp=-1;
		while(!q1.empty()){
			if(mx<q1.front()){
				mx=q1.front();
				mxp=1;
			}
			q1.pop();
		}
		while(!q2.empty()){
			if(mx<q2.front()){
				mx=q2.front();
				mxp=2;
			}
			q2.pop();
		}
		assert(mx>=0);
		assert(mxp>=0);
		if(mx>ts && mxp==1)
			return 1;
	}
	
	set<pair<queue<int>, queue<int> > > cycle;

	//winner is 1 or 2
	while(!q1.empty() && !q2.empty()){
		if(cycle.find(make_pair(q1, q2))!=cycle.end())
			return 1;
		cycle.insert(make_pair(q1, q2));
	
		int card1=q1.front();
		q1.pop();
		int card2=q2.front();
		q2.pop();
		if(card1<=int(q1.size()) && card2<=int(q2.size())){
			queue<int> q1a(q1);
			queue<int> q2a(q2);

			queue<int> q1b;
			queue<int> q2b;
			
			for(int i=0; i<card1; i++){
				q1b.push(q1a.front());
				q1a.pop();
			}
			for(int i=0; i<card2; i++){
				q2b.push(q2a.front());
				q2a.pop();
			}

			int w=gameWinner(level+1, q1b, q2b);
			if(w==1){
				q1.push(card1);
				q1.push(card2);
			}
			else{
				q2.push(card2);
				q2.push(card1);
			}
		}
		else if(card1>card2){
			q1.push(card1);
			q1.push(card2);
		}
		else{
			assert(card2>card1);
			q2.push(card2);
			q2.push(card1);
		}
	}
	
	if(level==0){
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
	}
	
	if(q1.empty()){
		return 2;
	}
	else{
		assert(q2.empty());
		return 1;
	}
}

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
	
	/*while(!q1.empty() && !q2.empty()){
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
	
	cout<<"result="<<result<<endl;*/
	
	cout<<"winner is: "<<gameWinner(0, q1, q2)<<endl;
	
	return 0;
}
