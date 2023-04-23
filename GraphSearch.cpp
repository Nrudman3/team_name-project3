#include <iostream>;

#include "GraphSearch.h"

using namespace::std;

GraphSearch::GraphSearch() {
	
}
GraphSearch::GraphSearch(Genre* rootGenre) {
	this->rootGenre = *rootGenre;
}
int GraphSearch::breadthFirstSearch(string targetGenre) {
	queue<Genre> q;
	map<string, int> visited;
	q.push(rootGenre);
	visited[rootGenre.returnGenre()] = 1;

	while (!q.empty()) {
		Genre curr = q.front();
		//cout << curr.returnGenre() << endl;
		if (targetGenre == curr.returnGenre()) {
			return visited[curr.returnGenre()];
		}
		q.pop();
		vector<Genre*> mostCompatibleGenres = curr.returnMostCompatibleGenres();
		for (int i = 0; i < mostCompatibleGenres.size(); i++) {
			Genre adj = *mostCompatibleGenres[i];
			string adjString = adj.returnGenre();
			if (!visited[adjString]) {
				visited[adjString] = visited[curr.returnGenre()] + 1;
				q.push(adj);
			}
		}
	}
	return -1;
}
int GraphSearch::depthFirstSearch(string targetGenre) {
	int min = -1;
	stack<Genre> s;
	map<string, int> visited;
	s.push(rootGenre);
	visited[rootGenre.returnGenre()] = 1;
	while (!s.empty()) {
		Genre curr = s.top();
		//cout << curr.returnGenre() << " at min " << visited[curr.returnGenre()] << endl;
		//cout << "CURRENT MIN " << min << endl;
		if (targetGenre == curr.returnGenre()) {
			//cout << curr.returnGenre() << " VS " << targetGenre << " at min " << visited[curr.returnGenre()] << endl;
			//cout << "CURRENT MIN " << min << endl;
			if (min == -1)
				min = visited[curr.returnGenre()];
			else if (visited[curr.returnGenre()] < min)
				min = visited[curr.returnGenre()];
		}
		s.pop();
		vector<Genre*> mostCompatibleGenres = curr.returnMostCompatibleGenres();
		for (int i = 0; i < mostCompatibleGenres.size(); i++) {
			Genre adj = *mostCompatibleGenres[i];
			string adjString = adj.returnGenre();
			if ((!visited[adjString] || adjString == targetGenre) && (visited[curr.returnGenre()] < min || min == -1)) {
				visited[adjString] = visited[curr.returnGenre()] + 1;
				s.push(adj);
			}
		}
	}
	return min;
}