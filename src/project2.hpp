#ifndef PROJECT2_HPP
#define PROJECT2_HPP

class Graph {
	public:
		Graph(int v, int e) : numVertex{ v }, numEdge{ e } {}
		void setNumVertex(int v) { numVertex = v; } 
		void setNumEdge(int e) { numEdge = e; }
		int getNumEdge(void) const { return numEdge; }
		int getNumVertex(void) const { return numVertex; }

	protected:
		int numVertex, numEdge;
};

class Graph_List : public Graph {
	public:
		Graph_List(int v, int e, vector<vector<pair<int,int>>>& L) : Graph{v, e}, adjList{ L } {}
		Graph_List() : Graph(0, 0), adjList(0) {}

		void setNumVertex(int v) { numVertex = v; adjList.resize(v); }
		void addEdge(int src, int dst, int w) {
			if (w < 0) { throw invalid_argument{ "weight must be positive" }; }
			if (src < 0 || src > numVertex || dst < 0 || dst > numVertex) { 
				throw invalid_argument{ "index out of bound" };
			}
			adjList[src].emplace_back(dst, w);				
			numEdge++;
		}

		void print(void) const {
			for (int i = 0; i < numVertex; i ++) {
				cout << i << ": ";
				for (const auto& i : adjList[i]) {
					cout << "(" << i.first << ", " << i.second << ")" << "-->";
				}
				cout << endl;
			}	
		}

		const vector<vector<pair<int, int>>>& getAdjList() const { return adjList; }

	private:
		vector<vector<pair<int, int>>> adjList; 
};

class Graph_Matrix : public Graph {
	public: 
		Graph_Matrix(int v, int e, vector<vector<int>>& M) : Graph{ v, e }, adjMatrix{ M } {}
		Graph_Matrix() : Graph{0, 0}, adjMatrix{0} {}

		void setNumVertex(int v) { 
			numVertex = v; 
			adjMatrix.resize(v, vector<int>(v, INT_MAX)); 
		}
		void addEdge(int src, int dst, int w) {
			if (w < 0) { throw invalid_argument{ "weight must be positive" }; }
			if (src < 0 || src > numVertex || dst < 0 || dst > numVertex) { 
				throw invalid_argument{ "index out of bound" };
			}
			adjMatrix[src][dst] = w;
			numEdge++;
		}

		const void print() const {
			for (int i  = 0; i < numVertex; i++) {
				for (int j = 0; j < numVertex; j++) {
					if (adjMatrix[i][j] == INT_MAX) cout << "INF ";
					else cout << adjMatrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		const vector<vector<int>>& getAdjMatrix(void) const { return adjMatrix; }

	private:
		vector<vector<int>> adjMatrix;
};


#endif // PROJECT2_HPP 
