#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

bool isColor(string s)
{
	if(s.empty())
		return false;
	for(size_t i=0; i<s.size(); i++)
		if((s[i]<'0' || s[i]>'9')&&(s[i]<'a' || s[i]>'f'))
			return false;
			
	return true;
}

bool isNumber(string s)
{
	if(s.empty())
		return false;
	for(size_t i=0; i<s.size(); i++)
		if(s[i]<'0' || s[i]>'9')
			return false;
			
	return true;
}

int main()
{
	//ifstream in("sample-input-valid.txt");
	//ifstream in("sample-input-invalid.txt");
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



				if(s1.substr(0, 4)=="byr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=1920 && stoi(s1.substr(4))<=2002)
						byr=true;
				}
				else if(s1.substr(0, 4)=="iyr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=2010 && stoi(s1.substr(4))<=2020)
						iyr=true;
				}
				else if(s1.substr(0, 4)=="eyr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=2020 && stoi(s1.substr(4))<=2030)
						eyr=true;
				}
				else if(s1.substr(0, 4)=="hgt:"){
					if(s1.size()>=6 && s1.substr(s1.size()-2)=="cm" && isNumber(s1.substr(4, s1.size()-6)) && stoi(s1.substr(4, s1.size()-6))>=150 && stoi(s1.substr(4, s1.size()-6))<=193)
						hgt=true;
					else if(s1.size()>=6 && s1.substr(s1.size()-2)=="in" && isNumber(s1.substr(4, s1.size()-6)) && stoi(s1.substr(4, s1.size()-6))>=59 && stoi(s1.substr(4, s1.size()-6))<=76)
						hgt=true;
				}
				else if(s1.substr(0, 4)=="hcl:"){
					if(s1.size()==11 && s1[4]=='#' && isColor(s1.substr(5)))
						hcl=true;
				}
				else if(s1.substr(0, 4)=="ecl:"){
					if((s1.size()==7) && (s1.substr(4)=="amb" ||
					 s1.substr(4)=="blu" ||
					 s1.substr(4)=="brn" ||
					 s1.substr(4)=="gry" ||
					 s1.substr(4)=="grn" ||
					 s1.substr(4)=="hzl" ||
					 s1.substr(4)=="oth"))
						ecl=true;
				}
				else if(s1.substr(0, 4)=="pid:"){
					if(s1.size()==13 && isNumber(s1.substr(4)))
						pid=true;
				}
				//else if(s1.substr(0, 4)=="cid:")
				//	cid=true;


					cout<<"s1="<<s1<<endl;
					break;
				}
				string s1=s.substr(pos1, pos2-pos1);

				if(s1.substr(0, 4)=="byr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=1920 && stoi(s1.substr(4))<=2002)
						byr=true;
				}
				else if(s1.substr(0, 4)=="iyr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=2010 && stoi(s1.substr(4))<=2020)
						iyr=true;
				}
				else if(s1.substr(0, 4)=="eyr:"){
					if(s1.size()==8 && isNumber(s1.substr(4)) && stoi(s1.substr(4))>=2020 && stoi(s1.substr(4))<=2030)
						eyr=true;
				}
				else if(s1.substr(0, 4)=="hgt:"){
					if(s1.size()>=6 && s1.substr(s1.size()-2)=="cm" && isNumber(s1.substr(4, s1.size()-6)) && stoi(s1.substr(4, s1.size()-6))>=150 && stoi(s1.substr(4, s1.size()-6))<=193)
						hgt=true;
					else if(s1.size()>=6 && s1.substr(s1.size()-2)=="in" && isNumber(s1.substr(4, s1.size()-6)) && stoi(s1.substr(4, s1.size()-6))>=59 && stoi(s1.substr(4, s1.size()-6))<=76)
						hgt=true;
				}
				else if(s1.substr(0, 4)=="hcl:"){
					if(s1.size()==11 && s1[4]=='#' && isColor(s1.substr(5)))
						hcl=true;
				}
				else if(s1.substr(0, 4)=="ecl:"){
					if((s1.size()==7) && (s1.substr(4)=="amb" ||
					 s1.substr(4)=="blu" ||
					 s1.substr(4)=="brn" ||
					 s1.substr(4)=="gry" ||
					 s1.substr(4)=="grn" ||
					 s1.substr(4)=="hzl" ||
					 s1.substr(4)=="oth"))
						ecl=true;
				}
				else if(s1.substr(0, 4)=="pid:"){
					if(s1.size()==13 && isNumber(s1.substr(4)))
						pid=true;
				}
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
	
	cout<<"answer to day 4 part 2 is: "<<cnt<<endl;
	
	return 0;
}
