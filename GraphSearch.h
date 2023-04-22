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
	int BreadthFirstSearch(string targetGenre);
	int DepthFirstSearch(string targetGenre);
	
private:
	Genre rootGenre;
	string targetGenre;
};

