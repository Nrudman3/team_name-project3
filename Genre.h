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
	void initializeRecommendationCorrelationFactors(string targetGenre, float weight);
	map<string, int>* returnCorrelations();
	map<string, float>* returnCorrelationFactors();
	map<string, float>* returnMostLinkedGenres();
	map<string, float>* returnRecommendedationCorrelationFactors();
	vector<Genre*> returnMostCompatibleGenres();
	string returnGenre();
	int returnPopularity();

private:
	string genre;
	int popularity;
	bool visited;
	map<string, int> correlationMap;
	map<string, float> correlationFactors;
	map<string, float> mostRelatedGenres;
	//final map utilized to suggest recommendations
	map<string, float> recommendationCorrelationFactors;
	vector<Genre*> mostCompatibleGenres;
};

