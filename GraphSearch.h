#include <iomanip>;
#include <vector>;
#include <queue>;
#include <stack>;
#include <string>;

#include "Genre.h"

#pragma once
class GraphSearch
{
public:
	GraphSearch();
	GraphSearch(Genre* rootGenre);
	float breadthFirstSearch(string targetGenre);
	float depthFirstSearch(string targetGenre);
	
private:
	Genre rootGenre;
	string targetGenre;
};

