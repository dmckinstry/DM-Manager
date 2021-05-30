//OK, so this thing will store random generations of encounters and such.

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
//SOMETHING FOR RNG, to be addressed later
using namespace std;

void randomFromFile(const char *fName)
{
	//csv file for each thing
	//generate first line, "total", [total]
	fstream File;
	File.open(fName,ios::in);
	char line[300]; //THIS! IS!/...
	File.getline(line,300);
	if(!File) cout<<"err 404";
	int rng=0;
	for(int i=0;line[i]!=','&&line[i]!='\0';i++)
	{
		//temporarily use RNG as the reading of total, so I don't have to write another variable for total
		rng=rng*10;
		rng+=int(line[i]-'0');
		//sscout<<rng;
	}
	rng=rand()%(rng+1); //this should set rng to a random number (rand()) between 0 and total (rng)
	cout<<"["<<rng<<"] ";
	
	//create "sum", starts with value 0.
	int sum=0;
	//create lineNum and lineName
	int lineNum;
	char lineName[100];
	
	
	//while loop to look up "roll" (rng) on "table" (csv file)
		//while sum<= rng && hasNext(),
		//set lineNum and lineName
		//sum += lineNum
	while(sum<=rng&&File.peek()!=EOF)
	{
		File.getline(line,300);
		lineNum=0;
		int commaValue=0;
		for(int i=0;i<100;i++) lineName[i]=' ';
		
		//Linear search for loop
		for(int i=0;line[i]!=',';i++) {
		lineNum=(10*lineNum)+(line[i]-'0'); //find index ','
		
		commaValue=i+2; // set commaValue to index past ','. 1 to make up for the final i++ that doesn't happen, one to increment past the ','
		} 
		//end linear search for loop

		sum+=lineNum;
		for(int i=commaValue;line[i]!='\0';i++) lineName[i-commaValue]=line[i]; //lineName is just line offset by index of ','
		
	}
	//cout lineName
	cout<<lineName<<endl; //the whileLoop terminated, so lineName should be the name at which rng reaches or surpasses sum.
	File.close();
}

void genEvent()
{
	int choice;
	cout<<"Choose a location:"<<endl<<"[1] City"<<endl<<"[0] Cancel"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1: string fname="CityEvents.csv";
		randomFromFile(fname.c_str());
			break;
	}
}

void genTav()
{
	cout<<"Name:"<<endl;
	string fname="TavernNameOne.csv";
	randomFromFile(fname.c_str());
	fname="TavernNameTwo.csv";
	randomFromFile(fname.c_str());
	cout<<"Details about tavern: "<<endl;
	fname="TavernDetails.csv";
	randomFromFile(fname.c_str());
}

void genBuild()
{
	string fname="Residence.csv";//residence will be the default.
	
	//Add: Restaurants of fign dining, warehouses of oddly specific goods, waste management and public service areas, alternative names (Second-'s-Third)
		//illegal dealers and underground merchants (for stolen goods, dead bodies, and drugs or other illicit substances. Sometimes brothels)
		//Theaters, sacrificial altars (maybe unmanned)
	
	switch((rand()%20)+1)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			cout<<"Building type: residence"<<endl;
			fname="Residence.csv";
			randomFromFile(fname.c_str());
			break;
		case 11:
		case 12:
			cout<<"Building type: religious";
			fname="Religious.csv";
			randomFromFile(fname.c_str());
			break;
		case 13:
		case 14:
		case 15:
			cout<<"Building type: tavern";
			genTav();
			break;
		case 16:
		case 17:
			cout<<"Building type: warehouse"; //NOTE: add a separate table for Oddly Specific Goods
			fname="Warehouse.csv";
			randomFromFile(fname.c_str());
			break;
		default:
			cout<<"Building type: shop";
			fname="Shops.csv";
			randomFromFile(fname.c_str());
			break;
	}
	
}

void buildMenu()
{
	string filename="Residence.csv";
	int choice;
	cout<<"Which type of building would you like?"<<endl;
	cout<<"[1] Random"<<endl<<"[2] Residence"<<endl<<"[3] Tavern"<<endl;
	cout<<"[4] Shop"<<endl<<"[5] Religious"<<endl<<"[6] Warehouse"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			genBuild();
			break;
		case 2:
			randomFromFile(filename.c_str());
			break;
		case 3:
			genTav();
			break;
		case 4:
			filename="Shop.csv";
			randomFromFile(filename.c_str());
			break;
		case 5:
			filename="Religious.csv";
			randomFromFile(filename.c_str());
			break;
		case 6:
			filename="Warehouse.csv";
			randomFromFile(filename.c_str());
			break;
		case 0:
		default:
			cout<<"Well that was unexpected..."<<endl;
			break;
	}
}

void buildSettlement()
{
	//generate all details of town
	
	cout<<"The race relations in this town are:"<<endl;
	string fname="Race.csv";
	randomFromFile(fname.c_str());
	
	cout<<"As for the ruler:"<<endl;
	fname="Ruler.csv";
	randomFromFile(fname.c_str());
	
	cout<<"As you enter the town, you notice:"<<endl;
	fname="NotableTraitsTown.csv";
	randomFromFile(fname.c_str());
	
	cout<<"You have already heard rumors of this place before..."<<endl;
	fname="TownKnownFor.csv";
	randomFromFile(fname.c_str());
	
	cout<<"Currently, the town is facing: ";
	fname="CurrentCalamityTown.csv";
	randomFromFile(fname.c_str());
	
	//Events and buildings
	
	cout<<"An (optional) event that happens when you walk into town: "<<endl;
	fname="CityEvents.csv";
	randomFromFile(fname.c_str());
	
	cout<<"The most important, if not only, tavern:"<<endl;
	genTav();
	
	cout<<"The first religious building you notice, for better or for worse:"<<endl;
	fname="Religious.csv";
	randomFromFile(fname.c_str());
	
	cout<<"The largest shop (if useful, only use as a response to player actions):"<<endl;
	fname="Shops.csv";
	randomFromFile(fname.c_str());
	
	cout<<"A few more buildings in town: "<<endl;
	genBuild();
	genBuild();
	genBuild();
	
}

int main()
{
	//a loop for the menu
	bool endLoop=false;
	
	while(!endLoop)
	{
		int choice;
		cout<<"Enter a value:"<<endl<<"[1] Generate random event"<<endl<<"[2] Generate Building"<<endl;
		cout<<"[3] generate a settlement: ";
		cout<<"[0] break"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				genEvent();
				break;
			case 2: 
				buildMenu();
				break;
			case 3:
				buildSettlement();
				break;
			case 0:
			default:
				endLoop=true;
		}
		
	}
	
	
}
