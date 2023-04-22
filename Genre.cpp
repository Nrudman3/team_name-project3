#include <map>;
#include <string>;
#include <iostream>;
#include <iomanip>;
#include <vector>;
#include <queue>;
#include <stack>;

#include "Genre.h"

Genre::Genre() {
	this->genre = "default";
	this->visited = false;
}

Genre::Genre(string genre) {
	this->genre = genre;
	correlationMap[this->genre] = 0;
}

void Genre::AddCorrelation(string linkedGenre) {
	correlationMap[linkedGenre] = correlationMap[linkedGenre] + 1;
}

void Genre::GenerateCorrelationFactors() {
	//purely for flavor, doesn't really change much asides from eliminating its own genre from the pool which could be doen without converting ints to floats, also finds a given genres popularity
	cout << setprecision(5) << endl;
	auto iter = this->correlationMap.begin();
	float sum = 0;
	while (iter != this->correlationMap.end()) {
		if (iter->first != this->genre) {
			sum += iter->second;
		}
		iter++;
	}
	this->popularity = sum;
	iter = this->correlationMap.begin();
	while (iter != this->correlationMap.end()) {
		if (iter->first != this->genre) {
			correlationFactors[iter->first] = (float)iter->second / (float)sum * 100.0;
		}
		iter++;
	}
}

void Genre::GenerateRankedCorrelationFactors() {

	auto iter = correlationFactors.begin();
	int size = 5;
	vector<float> rankedArray(size, 0.0);
	vector<string> rankedGenres(size, "");
	float min = rankedArray[0];
	int minLocation = 0;

	while(iter != correlationFactors.end()) {
		min = rankedArray[0];
		minLocation = 0;
		for (int i = 0; i < size; i++) {
			if (rankedArray[i] < min) {
				min = rankedArray[i];
				minLocation = i;
			}
		}
		if (iter->second > min) {
			rankedArray[minLocation] = iter->second;
			rankedGenres[minLocation] = iter->first;
		}
		iter++;
	}
	for (int i = 0; i < rankedArray.size(); i++) {

		mostRelatedGenres[rankedGenres[i]] = rankedArray[i];
	}
}

void Genre::initializeCompatibleGenre(Genre* compatibleGenre) {
	this->mostCompatibleGenres.push_back(compatibleGenre);
}

map<string, int>* Genre::returnCorrelations() {
	return &correlationMap;
}
map<string, float>* Genre::returnCorrelationFactors() {
	return &correlationFactors;
}
map<string, float>* Genre::returnMostLinkedGenres() {
	return &mostRelatedGenres;
}
vector<Genre*> Genre::returnMostCompatibleGenres() {
	return mostCompatibleGenres;
}
bool Genre::returnVisited() {
	return visited;
}
void Genre::enableVisited() {
	this->visited = true;
}
void Genre::disableVisited() {
	this->visited = false;
}
int Genre::returnPopularity() {
	return this->popularity;
}