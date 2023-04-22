#include <iostream>;

#include "GraphSearch.h"

using namespace::std;

GraphSearch::GraphSearch() {
	
}
GraphSearch::GraphSearch(Genre* rootGenre) {
	this->rootGenre = *rootGenre;
}
int GraphSearch::breadthFirstSearch(string targetGenre) {
	int distance = 0;
	queue<Genre> q;
	map<string, bool> visited;
	q.push(rootGenre);
	visited[rootGenre.returnGenre()] = true;

	while (!q.empty()) {
		Genre curr = q.front();
		cout << curr.returnGenre() << endl;
		if (targetGenre == curr.returnGenre()) {
			return distance;
		}
		q.pop();
		vector<Genre*> mostCompatibleGenres = curr.returnMostCompatibleGenres();
		for (int i = 0; i < mostCompatibleGenres.size(); i++) {
			Genre adj = *mostCompatibleGenres[i];
			string adjString = adj.returnGenre();
			if (!visited[adjString]) {
				distance++;
				visited[adjString] = true;
				q.push(adj);
			}
		}
	}
	return 0;
}
int GraphSearch::depthFirstSearch(string targetGenre) {
	int distance = 0;
	stack<Genre> s;
	map<string, bool> visited;
	s.push(rootGenre);
	visited[rootGenre.returnGenre()] = true;

	while (!s.empty()) {
		Genre curr = s.top();
		cout << curr.returnGenre() << endl;
		if (targetGenre == curr.returnGenre()) {
			return distance;
		}
		s.pop();
		vector<Genre*> mostCompatibleGenres = curr.returnMostCompatibleGenres();
		for (int i = 0; i < mostCompatibleGenres.size(); i++) {
			Genre adj = *mostCompatibleGenres[i];
			string adjString = adj.returnGenre();
			if (!visited[adjString]) {
				distance++;
				visited[adjString] = true;
				s.push(adj);
			}
		}
	}
	return 0;
}