#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "Genre.h"

using namespace::std;

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

int main() {

	using namespace::std;

	//setting up file to be opened
	string fileName = "HR_genres.json";
	ifstream file;
	file.open(fileName);

	//formatting of file
	//entire file enclosed within {}
	//"ID": ["Genre1", "Genre2", "Genre2"...], repeat ENTIRE thing is technically on one line, reading might be ram intensive
	//example "12345": ["Pop", "Rock", "Alternative"], "11111": ["Reggae", "Rock", "Alternative"], ...
	if (file.is_open()) {
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

		//take in the data, takes a while
		if (true) {
			while(getline(file, line, '[')) {
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
		}

		//total data points processed
		cout << "Data Points: " << dataPoints << endl;

		//Creating a graph with correlation factors
		auto iter = initializedGenres.begin();
		while (iter != initializedGenres.end()) {
			iter->second.GenerateCorrelationFactors();
			iter->second.GenerateRankedCorrelationFactors();
			map<string, float> temp = *(iter->second.returnCorrelationFactors());

			// create graph
			auto babyIter = temp.begin();
			while (babyIter != temp.end()) {
				iter->second.initializeCompatibleGenre(&initializedGenres[babyIter->first]);
				babyIter++;
			}


			
			/*auto babyIter = temp.begin();
			cout << iter->first << ": ";
			while (babyIter != temp.end()) {
				cout << babyIter->first << "(" << babyIter->second << "%)" << ", ";
				babyIter++;
			}
			cout << endl;

			temp = *(iter->second.returnMostLinkedGenres());
			auto babyIter2 = temp.begin();
			cout << iter->first << ": ";
			while (babyIter2 != temp.end()) {
				cout << babyIter2->first << "(" << babyIter2->second << "%)" << ", ";
				babyIter2++;
			}
			cout << endl;
			iter++;*/
		}



	}

}