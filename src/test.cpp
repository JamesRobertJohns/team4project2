#include <bits/stdc++.h>

using namespace std;
#include "project2.hpp"

int main() {
	Graph_List a{};
	a.setNumVertex(5);
	a.addEdge(0, 1, 10);
	a.addEdge(0, 2, 20);
	a.addEdge(1, 2, 10);
	a.addEdge(2, 1, 10);
	a.addEdge(1, 4, 30);
	a.addEdge(2, 3, 20);
	a.addEdge(3, 5, 10);
	a.print();
	cout << "number of vertex " << a.getNumVertex() << endl;
	cout << "number of edges " << a.getNumEdge() << endl;

	Graph_Matrix b{};
	b.setNumVertex(5);
	b.addEdge(0, 1, 10);
	b.addEdge(0, 2, 20);
	b.addEdge(1, 2, 10);
	b.addEdge(2, 1, 10);
	b.addEdge(1, 4, 30);
	b.addEdge(2, 3, 20);
	b.addEdge(3, 5, 10);
	b.print();
	cout << "number of vertex " << b.getNumVertex() << endl;
	cout << "number of edges " << b.getNumEdge() << endl;
}
