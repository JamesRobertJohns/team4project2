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
			if (w < 0) { throw invalid_argument{ "[-] in addEdge(): weight must be positive" }; }
			if (src < 0 || src > numVertex || dst < 0 || dst > numVertex) { 
				throw invalid_argument{ "[-] in addEdge(): index out of bound" };
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
			adjMatrix.resize(v, vector<int>(v, numeric_limits<int>::max())); 
		}
		void addEdge(int src, int dst, int w) {
			if (w < 0) { throw invalid_argument{ "[-] in addEdge(): weight must be positive" }; }
			if (src < 0 || src > numVertex || dst < 0 || dst > numVertex) { 
				throw invalid_argument{ "[-] in addEdge(): index out of bound" };
			}
			adjMatrix[src][dst] = w;
			numEdge++;
		}

		const void print() const {
			for (int i  = 0; i < numVertex; i++) {
				for (int j = 0; j < numVertex; j++) {
					if (adjMatrix[i][j] == numeric_limits<int>::max()) cout << "INF ";
					else cout << adjMatrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		const vector<vector<int>>& getAdjMatrix(void) const { return adjMatrix; }

	private:
		vector<vector<int>> adjMatrix;
};

class PriorityQ {
	public:
		virtual int peek() = 0;
		virtual int extract() = 0;
		virtual void insert(pair<int,int>) = 0;
		virtual void decreaseKey(int, int) = 0;
		virtual bool isEmpty() = 0;
		virtual void print() = 0;
};

class PriorityQ_Array : public PriorityQ {
	public:
		PriorityQ_Array(vector<pair<int,int>>& a) : A{ a } {}
		PriorityQ_Array() : A{ 0 } {}	
		
		bool isEmpty() override { return A.size() == 0? true : false; }
		int peek() override { 
			if (isEmpty()) throw runtime_error{ "[-] in peek(): queue is emmpty" };
			return A[0].first; 
		}		
		void insert(pair<int, int> node) override {
			if (isEmpty())  A.push_back(node);
			else {	
				for (auto it = A.begin(); it <= A.end(); it++) {
					if (node.second < it->second) { 
						A.insert(it, node);
						break;
					}
				}		
			}
		}
		int extract() override {
			int min = A[0].first;
			A.erase(A.begin());
			return min;
		}
		void decreaseKey(int v, int w) override {
			auto it = A.begin(); 
			int vw;
			while (it <= A.end()) { 
				if (it->first == v) {
					vw = it->second; 
					break;
				}
				it++; 
			}
			if (it > A.end()) throw invalid_argument{ "[-] in decreaseKey(): index out of bound" };
			if (w > vw) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small " };
			A.erase(it);
			insert(make_pair(v, w));
		}
		void print() override {
			if (isEmpty()) {
				cout << "Queue is Empty" << endl;
				return;
			}
			for (const auto i : A) {
				cout << "(" << i.first << ", " << i.second << "), ";
			}
			cout << endl;
		}

	private:
		vector<pair<int, int>> A;

};

#endif // PROJECT2_HPP 
