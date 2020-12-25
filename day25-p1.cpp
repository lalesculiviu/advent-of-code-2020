#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

typedef long long int int64;

int cardPublicKey;
int doorPublicKey;

int cardLoopSize;
int doorLoopSize;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	in>>cardPublicKey;
	in>>doorPublicKey;
	
	int q=1;
	cardLoopSize=-1;
	for(int k=1; k<=1000000000; k++){
		q=int((int64(7)*int64(q))%int64(20201227));
		if(cardPublicKey==q){
			cardLoopSize=k;
			break;
		}
	}
	cout<<"cardLoopSize="<<cardLoopSize<<endl;

	q=1;
	doorLoopSize=-1;
	for(int k=1; k<=1000000000; k++){
		q=int((int64(7)*int64(q))%int64(20201227));
		if(doorPublicKey==q){
			doorLoopSize=k;
			break;
		}
	}
	cout<<"doorLoopSize="<<doorLoopSize<<endl;

	q=1;
	for(int k=1; k<=cardLoopSize; k++)
		q=int((int64(q)*int64(doorPublicKey))%int64(20201227));
		
	int answer=q;

	q=1;
	for(int k=1; k<=doorLoopSize; k++)
		q=int((int64(q)*int64(cardPublicKey))%int64(20201227));
		
	assert(answer==q);
	
	cout<<"The answer to part 1 is: "<<answer<<endl;
	
	return 0;
}
