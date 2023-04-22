#pragma once
#include <map>;
#include <string>;
#include <chrono>;

using namespace::std;

class Genre
{
public:
	Genre();
	Genre(string genre);
	void AddCorrelation(string linkedGenre);
	void GenerateCorrelationFactors(map<string, Genre>& initializedGenres);
	void GenerateRankedCorrelationFactors();
	void initializeCompatibleGenre(Genre* compatibleGenre);
	map<string, int>* returnCorrelations();
	map<string, float>* returnCorrelationFactors();
	map<string, float>* returnMostLinkedGenres();
	vector<Genre*> returnMostCompatibleGenres();
	string returnGenre();
	bool returnVisited();
	void enableVisited();
	void disableVisited();
	int returnPopularity();

private:
	string genre;
	int popularity;
	bool visited;
	map<string, int> correlationMap;
	map<string, float> correlationFactors;
	map<string, float> mostRelatedGenres;
	vector<Genre*> mostCompatibleGenres;
};

