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

	cout << endl;
	Dijkstra_3  d2{};
	d2.findPath(d, 0);
	d2.print_path(0, 4);
	cout << endl;
	d2.print_path(0, 2); 

	try {
		int i = 1;
		string name = "../data/fixed_edges_";
		while (i <= 10) { 
			Graph_List G3{};
			Dijkstra_3 algo3{};

			string appendedName = name + to_string(i) + ".txt";
			cout << "logging " << appendedName << " now...\n";
			logger(appendedName, "../data/fixed_edges_output_3.csv", G3, algo3);
			i++;
		}
	} catch(std::exception& e) {
		cout << e.what() << endl;
		exit(1);
	} 

	 try {
		int i = 1;
		string name = "../data/fixed_vertex_";
		while (i <= 10) { 
			Graph_List G3{};
			Dijkstra_3 algo3{};

			string appendedName = name + to_string(i) + ".txt";
			cout << "logging " << appendedName << " now...\n";
			logger(appendedName, "../data/fixed_vertex_output_3.csv", G3, algo3);
			i++;
		}
	} catch(std::exception& e) {
		cout << e.what() << endl;
		exit(1);
	} 



}


