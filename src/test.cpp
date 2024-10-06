#include <bits/stdc++.h>

using namespace std;
#include "project2.hpp"

template <typename T>
void TEST_PQ(T pq) {
	cout << "=================" << endl;

	cout << "print():" << endl;
	pq.print();

	cout << "insert(): (1, 10), (7, 20), (2, 5), (13, 1), (5, 15) " << endl;
	pq.insert(make_pair(1, 10));
	pq.insert(make_pair(7, 20));
	pq.insert(make_pair(2, 5));
	pq.insert(make_pair(13, 1));
	pq.insert(make_pair(5, 15));
	cout << "queue is: ";
	pq.print();	

	cout << "peek():" << pq.peek() << endl;
	
	cout << "extract(): " << pq.extract() << endl;	
	cout << "queue is: ";
	pq.print();

	cout << "decreaseKey(7, 0): ";
	pq.decreaseKey(7, 0);
	cout << "queue is: ";
	pq.print();
	cout << "=================" << endl;
}

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

	cout << "pqa test" << endl;
	PriorityQ_Array pqa{};
	TEST_PQ(pqa);	

	cout << "pqh test" << endl;
	PriorityQ_Heap pqh{};
	TEST_PQ(pqh);	
	
}


