//Preventing Crimes in C++

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Define a Global Variables
int numberOfCrimes = 0;

//Define a Crime Object to store information
class Crime{

public:
	string type;
	string description;
	int time;

};

//Function that will be used to monitor any reported crimes
void monitorCrime(Crime currentCrime){

	cout << "Type of crime: " << currentCrime.type << endl;
	cout << "Description of crime: " << currentCrime.description << endl;
	cout << "Time of crime: " << currentCrime.time << endl;
	numberOfCrimes++;
	cout << "Number of reported crimes so far: " << numberOfCrimes << endl;

}

//Function to record all reported crimes
void recordCrime(Crime currentCrime){

	ofstream crimeDatabase;
	crimeDatabase.open("database.txt");

	crimeDatabase << currentCrime.type << ", " << currentCrime.description << ", " << currentCrime.time;

	crimeDatabase.close();

}

//Function to display all reported crimes
void displayCrimes(){

	string line;
	ifstream crimeDatabase;
	crimeDatabase.open("database.txt");

	if(crimeDatabase.is_open()){

		while(getline(crimeDatabase, line)){
			cout << line << endl;
		}

	}
	else{
		cout << "File could not be opened.";
	}

	crimeDatabase.close();

}

//Function to get crime information from user
Crime getCrimeInfo(){

	string type;
	string description;
	int time;

	cout << "Crime Type: ";
	cin >> type;
	cout << "Crime Description: ";
	cin >> description;
	cout << "Time of Crime: ";
	cin >> time;

	Crime newCrime;
	newCrime.type = type;
	newCrime.description = description;
	newCrime.time = time;

	return newCrime;

}

//Function to analyze the reported crimes
void analyzeCrimes(){

	int maxTime = 0;
	string mostCommonCrime;
	vector<string> types;

	ifstream crimeDatabase;
	crimeDatabase.open("database.txt");

	if(crimeDatabase.is_open()){

		string line;

		while(getline(crimeDatabase, line)){
			vector<string> tokens;
			string token;
			stringstream stream(line);

			while(getline(stream, token, ',')){
				tokens.push_back(token);
			}

			if(stoi(tokens[2]) > maxTime){
				maxTime = stoi(tokens[2]);
			}

			types.push_back(tokens[0]);
		}

		map<string, int> typeCount;
		for(int i =0; i < types.size(); i++){
			typeCount[types[i]]++;
		}

		int maxValue = 0;
		for(map<string, int>::iterator it = typeCount.begin(); it != typeCount.end(); it++){
			if(it->second > maxValue){
				maxValue = it->second;
				mostCommonCrime = it->first;
			}
		}

		cout << "Most Common Crime: " << mostCommonCrime << endl;
		cout << "Longest Time Since Crime Was Reported: " << maxTime << endl;

	}
	else{
		cout << "File could not be opened.";
	}

	crimeDatabase.close();

}

int main(){

	while(true){

		cout << "1. Report Crime" << endl;
		cout << "2. Monitor All Reported Crimes" << endl;
		cout << "3. Display All Reported Crimes" << endl;
		cout << "4. Analyze All Reported Crimes" << endl;
		cout << "5. Exit" << endl;
		int choice;
		cin >> choice;

		if(choice == 1){
			Crime newCrime = getCrimeInfo();
			monitorCrime(newCrime);
			recordCrime(newCrime);
		}
		else if(choice == 2){
			cout << "Number of reported crimes so far: " << numberOfCrimes << endl;
		}
		else if(choice == 3){
			displayCrimes();
		}
		else if(choice == 4){
			analyzeCrimes();
		}
		else if(choice == 5){
			break;
		}
		else{
			cout << "Invalid Choice!" << endl;
		}

	}

	return 0;

}