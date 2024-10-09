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

	pair<int, int> node;
   	node = pq.extract();	
	cout << "extract(): " << node.first << ", " << node.second << endl;	
	cout << "queue is: ";
	pq.print();

	node = pq.extract();	
	cout << "extract(): " << node.first << ", " << node.second << endl;	
	cout << "queue is: ";
	pq.print();
		
	cout << "decreaseKey(7, 0): ";
	pq.decreaseKey(7, 0);
	cout << "queue is: ";
	pq.print();
	
	cout << "decreaseKey(5, 5): ";
	pq.decreaseKey(5, 5);
	cout << "queue is: ";
	pq.print();


	cout << "=================" << endl;
}

int main() {
	/* Graph_List a{};
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
	cout << "number of edges " << a.getNumEdge() << endl; */

	/* Graph_Matrix b{};
	b.setNumVertex(6);
	b.addEdge(0, 1, 10);
	b.addEdge(0, 2, 20);
	b.addEdge(1, 2, 10);
	b.addEdge(2, 1, 10);
	b.addEdge(1, 4, 30);
	b.addEdge(2, 3, 20);
	b.addEdge(3, 5, 10);
	b.print(); */

	/* cout << "pqa test" << endl;
	PriorityQ_Array pqa{};
	TEST_PQ(pqa);	

	cout << "pqh test" << endl;
	PriorityQ_Heap pqh{};
	TEST_PQ(pqh);	*/

	/* Graph_Matrix c{};
	c.setNumVertex(5); 
	c.addEdge(0, 1, 10); 
	c.addEdge(0, 3, 5);
	c.addEdge(1,2,1);
	c.addEdge(1,3,2);
	c.addEdge(3,1,3);
	c.addEdge(3,2,9);
	c.addEdge(2,4,4);
	c.addEdge(3,4,2);
	c.addEdge(4,0,7);
	c.addEdge(4,2,6);
	c.print(); */

	/* PriorityQ_Heap test{};
	TEST_PQ(test); */

	Graph_List d{}; d.setNumVertex(5);
	d.addEdge(0, 1, 10);
	d.addEdge(0, 3, 5);
	d.addEdge(1,2,1);
	d.addEdge(1,3,2);
	d.addEdge(3,1,3);
	d.addEdge(3,2,9);
	d.addEdge(2,4,4);
	d.addEdge(3,4,2);
	d.addEdge(4,0,7);
	d.addEdge(4,2,6);
	d.print();

	/* cout << endl;
	Dijkstra_1 d1{};
	d1.findPath(c, 0);
	d1.print_path(0,4);
	cout << endl;
	d1.print_path(0, 2); */
	
	cout << endl;
	Dijkstra_2  d2{};
	d2.findPath(d, 0);
	d2.print_path(0, 4);
	cout << endl;
	d2.print_path(0, 2);
}


