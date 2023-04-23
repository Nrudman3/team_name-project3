#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>

#include "Genre.h"
#include "GraphSearch.h"

using namespace::std;

string dataSelect() {
	string dataChoice;
	cout << "Select which data sets to load: \n";
	cout << " 1. Croatia\n 2. Romania\n 3. Hungary\n 4. All\n";
	getline(cin, dataChoice);
	while (dataChoice != "1" && dataChoice != "2" && dataChoice != "3" && dataChoice != "4") {
		cout << "Please enter a valid number\n";
		getline(cin, dataChoice);
	}
	return dataChoice;
}

string operationSelect() {
	string opChoice;
	cout << "Select operation:\n";
	cout << " 1. Most popular genre\n 2. Least Popular Genre\n 3. Enter a user's genres\n 4. View stats of a given genre\n 5. Exit\n";
	getline(cin, opChoice);
	return opChoice;
}

void genrePopularity(int mostLeast) {

}

void recommendedGenres() {
	vector<string> userGenres;
	string currGenre = "start";
	cout << "Enter a genre or type \"done\" if you are done entering genres\n";
	getline(cin, currGenre);
	while (currGenre != "done") {
		getline(cin, currGenre);
		userGenres.push_back(currGenre);
	}
}

void viewGenreStats() {

}

void depthVSBreadth(map<string, Genre>& initializedGenres) {
	string startGenre;
	string endGenre;
	cout << "Enter Starting Genre: \n";
	getline(cin, startGenre);
	cout << "Enter Ending Genre: \n";
	getline(cin, endGenre);
	GraphSearch dnb = GraphSearch(&initializedGenres[startGenre]);
	auto startBFS = chrono::high_resolution_clock::now();
	cout << "BFS: " << dnb.breadthFirstSearch(endGenre) << endl;
	auto stopBFS = chrono::high_resolution_clock::now();
	auto durationBFS = chrono::duration_cast<chrono::milliseconds>(stopBFS - startBFS);
	cout << "BFS duration : " << durationBFS.count() << endl;
	auto startDFS = chrono::high_resolution_clock::now();
	cout << "DFS: " << dnb.depthFirstSearch(endGenre) << endl;
	auto stopDFS = chrono::high_resolution_clock::now();
	auto durationDFS = chrono::duration_cast<chrono::milliseconds>(stopDFS - startDFS);
	cout << "DFS duration : " << durationDFS.count() << endl;


}

void insertGenres(vector<string>& userGenres, map<string, Genre> &initializedGenres, unordered_map<string, bool> &recognizedGenres) {
	for (int i = 0; i < userGenres.size(); i++) {
		if (recognizedGenres[userGenres[i]] != true) {
			initializedGenres[userGenres[i]] = Genre(userGenres[i]);
			recognizedGenres[userGenres[i]] = true;
		}
		for (int j = 0; j < userGenres.size(); j++) {
			initializedGenres[userGenres[i]].AddCorrelation(userGenres[j]);
		}
	}
}

void listLinkedGenres(string genre, map<string, Genre> &initializedGenres) {
	cout << genre << ": " << initializedGenres[genre].returnMostLinkedGenres();
}

int main() {

	//menu
	bool cycle = true;
	string data = dataSelect();

	//setting up file to be opened
	string fileName;
	if (data == "1" || data == "4") {
		fileName = "data/HR_genres.json";
	}
	else if (data == "2") {
		fileName = "data/RO_genres.json";
	}
	else if (data == "3") {
		fileName = "data/HU_genres.json";
	}
	cout << "Loading " << fileName << "...\n";

	ifstream file;
	file.open(fileName);
	//setting up things to read
	int dataPoints = 0;
	string line;
	bool recording = false;
	bool genreRecording = false;
	int j = 0;
	string genre = "";
	vector<string> userGenres;
	//keep track of what genres have shown up
	unordered_map<string, bool> recognizedGenres;
	//holds all of our genre objects
	map<string, Genre> initializedGenres;

	//formatting of file
	//entire file enclosed within {}
	//"ID": ["Genre1", "Genre2", "Genre2"...], repeat ENTIRE thing is technically on one line, reading might be ram intensive
	//example "12345": ["Pop", "Rock", "Alternative"], "11111": ["Reggae", "Rock", "Alternative"], ...
	while (file.is_open()) {
		//take in the data, takes a while
		while (getline(file, line, '[')) {
			dataPoints++;
			getline(file, line, ']');
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '"' && !genreRecording) {
					genreRecording = true;
				}
				else if (line[i] == '"') {
					userGenres.push_back(genre);
					genre.clear();
					j = 0;
					genreRecording = false;
				}
				else if (genreRecording) {
					genre = genre + line[i];
					j++;
				}
			}
			insertGenres(userGenres, initializedGenres, recognizedGenres);
			userGenres.clear();
		}
		if (data == "4" && fileName == "data/HR_genres.json") {
			fileName = "data/RO_genres.json";
			file.close();
			file.open(fileName);
			cout << "Loading " << fileName << "...\n";
		}
		else if (data == "4" && fileName == "data/RO_genres.json") {
			fileName = "data/HU_genres.json";
			file.close();
			file.open(fileName);
			cout << "Loading " << fileName << "...\n";
		}
		else {
			file.close();
			cout << "Loading complete.\n\n";
		}
		
	}
	//total data points processed
	cout << "Data Points: " << dataPoints << endl;
	cout << endl;
	cout << "Initializing Graph...\n\n";

	//Creating a graph with correlation factors
	auto iter = initializedGenres.begin();
	while (iter != initializedGenres.end()) {
		iter->second.GenerateCorrelationFactors(initializedGenres);
		iter->second.GenerateRankedCorrelationFactors();
		map<string, float> temp = *(iter->second.returnMostLinkedGenres());

		// create graph
		auto babyIter = temp.begin();
		while (babyIter != temp.end()) {
			iter->second.initializeCompatibleGenre(&initializedGenres[babyIter->first]);
			babyIter++;
		}
		iter++;
	}

	while (cycle) {
		string opChoice = operationSelect();
		if (opChoice == "1")
			genrePopularity(1);
		else if (opChoice == "2")
			genrePopularity(-1);
		else if (opChoice == "3")
			recommendedGenres();
		else if (opChoice == "4")
			viewGenreStats();
		else if (opChoice == "4")
			cycle = false;
		else if (opChoice == "DnB")
			depthVSBreadth(initializedGenres);
		else
			cout << "Invalid input, please only enter the number of the operation you would like\n";
	}

}