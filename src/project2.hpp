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
		PriorityQ() : A{ 0 } {}
		int peek() { 
			if (isEmpty()) throw runtime_error{ "[-] in peek(): queue is emmpty" };
			return A[0].first; 
		}
		virtual int extract() = 0;
		virtual void insert(pair<int,int>) = 0;
		virtual void decreaseKey(int, int) = 0;
		virtual bool isEmpty() = 0;
		void print() {
			if (isEmpty()) {
				cout << "Queue is Empty" << endl;
				return;
			}
			for (const auto i : A) {
				cout << "(" << i.first << ", " << i.second << "), ";
			}
			cout << endl;
		}

		protected:
			vector<pair<int, int>> A;
};

class PriorityQ_Array : public PriorityQ {
	public:
		PriorityQ_Array() : PriorityQ{} {}	
		bool isEmpty() override { return A.size() == 0? true : false; }
		void insert(pair<int, int> node) override {
			if (isEmpty())  A.push_back(node);
			else {	
				auto it = A.begin();
				while (it != A.end()) {
					if (node.second < it->second) { 
						A.insert(it, node);
						return ;
					}
					it++;
				}		
				A.insert(it, node);
			}
		}
		int extract() override {
			int min = peek();
			A.erase(A.begin());
			return min;
		}
		void decreaseKey(int v, int w) override {
			auto it = A.begin(); 
			int vw;
			while (it != A.end()) { 
				if (it->first == v) {
					vw = it->second; 
					break;
				}
				it++; 
			}
			if (it == A.end()) throw invalid_argument{ "[-] in decreaseKey(): index out of bound" };
			if (w > vw) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small " };
			it->second = w;
			while (it > A.begin() && (it-1)->second > it->second) {
				iter_swap(it-1, it);					
				it--;		
			}			
		}
};


class PriorityQ_Heap : public PriorityQ {
	public:
		PriorityQ_Heap() : PriorityQ{}, heapSize{ 0 } {}

		bool isEmpty() override { return heapSize==0? true:false; }
		int extract() override { 
			int min = peek();	   
			auto it = m.find(A[0].first); m.erase(it);
			A[0] = A[heapSize-1];
			heapSize--;
			minHeapify(1);
			return min;
		}
		void swapPairByIndex(int pair_A, int pair_B) {
			int t1 = A[pair_A].first; int t2 = A[pair_A].second; int t3 = m[t1];
			m[A[pair_A].first] = m[A[pair_B].first];
			m[A[pair_B].first] = t3;
			A[pair_A].first = A[pair_B].first; 
			A[pair_A].second = A[pair_B].second;
			A[pair_B].first = t1;
			A[pair_B].second = t2;
		}
		void decreaseKey(int vertex, int key) override { 
			int index = m[vertex];	
			if (A[index].second < key) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small" };
			A[index].second = key;
			while (A[index].second < A[PARENT(index+1)-1].second && index > 0) {
				swapPairByIndex(index, (PARENT(index+1)-1));	
				index = PARENT(index+1) - 1;
			}
		} 

		void insert(pair<int,int> node) override {
			if (isEmpty()) { 
				A.push_back(node);	
				m[node.first] = 0;
				heapSize++;
			}
			else {
				heapSize++;
				A.push_back(node);
				A[heapSize-1].second = numeric_limits<int>::max();
				m[node.first] = heapSize-1;
				decreaseKey(node.first, node.second); 
			}
		}

		int PARENT(int i) const { return i/2; }
		int LEFT(int i) const { return 2*i; }
		int RIGHT(int i) const { return 2*i + 1; }

		void minHeapify(int i) {
			int l = LEFT(i); int r = RIGHT(i); int smallest = i;
			if (l <= heapSize && A[l-1].second < A[i-1].second) { smallest = l; }	
			if (r <= heapSize && A[r-1].second < A[smallest-1].second) { smallest = r; }
			if (smallest != i) {
				swapPairByIndex(i-1, smallest-1);
				minHeapify(smallest);
			}
		}
		
		void print_map() {
			cout << "map: ";
			for (const auto& i : m)
				cout << i.first << ": " << i.second << ", ";
			cout << endl;
		}

	private:
		size_t heapSize;
		unordered_map<int, int> m;
};

#endif // PROJECT2_HPP 
