#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	int cnt=0;
	
	for(;;){
		bool byr=false, iyr=false, eyr=false, hgt=false, hcl=false, ecl=false, pid=false/*, cid=false*/;
	
		for(;;){
			string s;
			getline(in, s);
			if(in.eof() || s.empty())
				break;
				
			int pos1=0;
			for(;;){
				size_t pos2=s.find(' ', pos1);
				if(pos2==string::npos){
					string s1=s.substr(pos1);

					if(s1.substr(0, 4)=="byr:")
						byr=true;
					else if(s1.substr(0, 4)=="iyr:")
						iyr=true;
					else if(s1.substr(0, 4)=="eyr:")
						eyr=true;
					else if(s1.substr(0, 4)=="hgt:")
						hgt=true;
					else if(s1.substr(0, 4)=="hcl:")
						hcl=true;
					else if(s1.substr(0, 4)=="ecl:")
						ecl=true;
					else if(s1.substr(0, 4)=="pid:")
						pid=true;
					//else if(s1.substr(0, 4)=="cid:")
					//	cid=true;

					cout<<"s1="<<s1<<endl;
					break;
				}
				string s1=s.substr(pos1, pos2-pos1);

				if(s1.substr(0, 4)=="byr:")
					byr=true;
				else if(s1.substr(0, 4)=="iyr:")
					iyr=true;
				else if(s1.substr(0, 4)=="eyr:")
					eyr=true;
				else if(s1.substr(0, 4)=="hgt:")
					hgt=true;
				else if(s1.substr(0, 4)=="hcl:")
					hcl=true;
				else if(s1.substr(0, 4)=="ecl:")
					ecl=true;
				else if(s1.substr(0, 4)=="pid:")
					pid=true;
				//else if(s1.substr(0, 4)=="cid:")
				//	cid=true;

				cout<<"s1="<<s1<<endl;
				pos1=pos2+1;
			}
		}
		
		if(byr&&iyr&&eyr&&hgt&&hcl&&ecl&&pid)
			cnt++;
		
		if(in.eof())
			break;
	}
	
	cout<<"answer to day 4 part 1 is: "<<cnt<<endl;
	
	return 0;
}
