#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

const int MAX_FOODS=47;
const int MAX_INGREDIENTS=10000;
const int MAX_ALLERGENS=1000;

vector<int> ingredients[MAX_FOODS];
set<int> ingredientsSet[MAX_FOODS];
vector<int> allergens[MAX_FOODS];

unordered_map<string, int> ingredientsMap;
unordered_map<string, int> allergensMap;

int nFoods;
int nIngredients;
int nAllergens;

vector<string> ingredientsNames;
vector<string> allergensNames;

bool possible[MAX_INGREDIENTS][MAX_ALLERGENS];

int main()
{
	//ifstream in("sample-input.txt");
	ifstream in("input");
	
	string food;
	
	nFoods=0;
	nIngredients=0;
	nAllergens=0;
	
	while(getline(in, food)){
		cout<<"food="<<food<<endl<<endl;
		string ingredient;
		string allergen;
		size_t pos1=0;
		size_t pos2;
		for(;;){
			pos2=food.find(" ", pos1);
			ingredient=food.substr(pos1, pos2-pos1);
			cout<<"ingredient: "<<ingredient<<endl;
			
			int crtIngredient=-1;
			
			if(ingredientsMap.find(ingredient)==ingredientsMap.end()){
				ingredientsMap.insert(make_pair(ingredient, nIngredients));
				crtIngredient=nIngredients;
				
				ingredientsNames.push_back(ingredient);
				
				nIngredients++;
			}
			else{
				crtIngredient=ingredientsMap.find(ingredient)->second;
			}
			
			assert(crtIngredient>=0);
			
			ingredients[nFoods].push_back(crtIngredient);
			ingredientsSet[nFoods].insert(crtIngredient);
			
			pos1=pos2+1;
			if(food[pos2+1]=='('){
				cout<<endl;
				break;
			}
		}
		pos2=food.find("contains", pos1);
		cout<<"pos2="<<pos2<<endl;
		pos1=pos2+9;
		for(;;){
			pos2=food.find(" ", pos1);
			if(pos2==string::npos){
				pos2=food.find(")", pos1);
				allergen=food.substr(pos1, pos2-pos1);
				cout<<"allergen: "<<allergen<<endl;

				int crtAllergen=-1;
			
				if(allergensMap.find(allergen)==allergensMap.end()){
					allergensMap.insert(make_pair(allergen, nAllergens));
					crtAllergen=nAllergens;
					
					allergensNames.push_back(allergen);
					
					nAllergens++;
				}
				else{
					crtAllergen=allergensMap.find(allergen)->second;
				}
			
				assert(crtAllergen>=0);
				
				allergens[nFoods].push_back(crtAllergen);

				cout<<endl;
				break;
			}
			allergen=food.substr(pos1, pos2-pos1-1);
			cout<<"allergen: "<<allergen<<endl;

			int crtAllergen=-1;
		
			if(allergensMap.find(allergen)==allergensMap.end()){
				allergensMap.insert(make_pair(allergen, nAllergens));
				crtAllergen=nAllergens;

				allergensNames.push_back(allergen);

				nAllergens++;
			}
			else{
				crtAllergen=allergensMap.find(allergen)->second;
			}
			
			assert(crtAllergen>=0);
			
			allergens[nFoods].push_back(crtAllergen);

			pos1=pos2+1;
		}
		
		nFoods++;
	}
	
	for(int i=0; i<nIngredients; i++)
		for(int j=0; j<nAllergens; j++)
			possible[i][j]=true;
			
	for(int f=0; f<nFoods; f++){
		for(int a : allergens[f]){
			for(int i=0; i<nIngredients; i++){
				if(ingredientsSet[f].find(i)==ingredientsSet[f].end()){
					possible[i][a]=false;
				}
			}
		}
	}
	
	for(int i=0; i<nIngredients; i++){
		for(int a=0; a<nAllergens; a++){
			cout<<possible[i][a]<<" ";
		}
		cout<<endl;
	}
	
	set<int> possibleAllergenicIngredients;
	
	for(int i=0; i<nIngredients; i++){
		bool p=false;
		for(int a=0; a<nAllergens; a++)
			if(possible[i][a]){
				p=true;
				break;
			}
		if(p)
			possibleAllergenicIngredients.insert(i);
	}
	
	int cnt=0;
	for(int f=0; f<nFoods; f++)
		for(int i : ingredients[f])
			if(possibleAllergenicIngredients.find(i)==possibleAllergenicIngredients.end())
				cnt++;

	cout<<"cnt="<<cnt<<endl;
	
	for(int i=0; i<nIngredients; i++)
		if(possibleAllergenicIngredients.find(i)!=possibleAllergenicIngredients.end()){
			cout<<"Ingredient: "<<ingredientsNames[i]<<endl;
			
			cout<<"  Possible allergens:";
			for(int a=0; a<nAllergens; a++)
				if(possible[i][a])
					cout<<" "<<allergensNames[a];
			cout<<endl;
		}

	return 0;
}
