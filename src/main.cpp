#include <bits/stdc++.h>
using namespace std;
#include "project2.hpp"

int main() {
	try {
		int i = 1;
		string name = "../data/fixed_edges_";
		while (i <= 10) { 
			Graph_Matrix G1{};
			Dijkstra_1 algo1{};
			Graph_List G2{};
			Dijkstra_2 algo2{};
			Graph_List G3{};
			Dijksra_3 algo3{};

			string appendedName = name + to_string(i) + ".txt";
			cout << "logging " << appendedName << " now...\n";
			logger(appendedName, "../data/fixed_edges_output_1.csv", G1, algo1);			
			logger(appendedName, "../data/fixed_edges_output_2.csv", G2, algo2);
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
			Graph_Matrix G1{};
			Dijkstra_1 algo1{};
			Graph_List G2{};
			Dijkstra_2 algo2{};
			Graph_List G3{};
			Dijkstra_3 algo3{};

			string appendedName = name + to_string(i) + ".txt";
			cout << "logging " << appendedName << " now...\n";
			logger(appendedName, "../data/fixed_vertex_output_1.csv", G1, algo1);			
			logger(appendedName, "../data/fixed_vertex_output_2.csv", G2, algo2);
			logger(appendedName, "../data/fixed_vertex_output_3.csv", G3, algo3);
			i++;
		}
	} catch(std::exception& e) {
		cout << e.what() << endl;
		exit(1);
	} 


}
