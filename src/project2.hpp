#ifndef PROJECT2_HPP
#define PROJECT2_HPP
using ii = std::pair<int, int>;
class Graph {
	public:
		Graph(int v, int e) : numVertex{ v }, numEdge{ e } {}
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
		virtual pair<int, int> extract() = 0;
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

		vector<pair<int, int>>& getA() { return A; }

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
		pair<int, int> extract() override {
			int min = peek();
			pair<int, int> node = getA()[0];
			A.erase(A.begin());
			return node;
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
			if (it == A.end()) throw invalid_argument{ "[-] in decreaseKey(): index out of bound. vertex index: " + to_string(v) + " weight: " + to_string(w) };
			if (w > vw) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small " };
			it->second = w;
			while (it > A.begin() && (it-1)->second > it->second) {
				iter_swap(it-1, it);					
				it--;		
			}			
		}
};


class PriorityQ_Heap2 : public PriorityQ {
	public:
		PriorityQ_Heap2() : PriorityQ{}, heapSize{ 0 } {}

		bool isEmpty() override { return heapSize==0? true:false; }
		pair<int, int> extract() override { 
			int min = peek();	   
			pair<int, int> node = getA()[0];
			A[0] = A[heapSize-1];
			heapSize--;
			minHeapify(1);
			return node;
		}
		void swapPairByIndex(int pair_A, int pair_B) {
			int t1 = A[pair_A].first; int t2 = A[pair_A].second; 
			A[pair_A].first = A[pair_B].first; 
			A[pair_A].second = A[pair_B].second;
			A[pair_B].first = t1;
			A[pair_B].second = t2;
		}
		void decreaseKey(int vertex, int key) override { 
			int index = m[vertex];	
			if (A[index].second < key) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small. current vertex is: " + to_string(index) + " current key is: " + to_string(A[index].second) + " new key trying to assign is: " + to_string(key) };
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
		
		void print_heap() {
			for (int i = 0; i < heapSize; i++) {
				cout << "( " << A[i].first << ", " << A[i].second << ") ";
			}
			cout << endl;
		}

	private:
		size_t heapSize;
		unordered_map<int, int> m;
};



class PriorityQ_Heap : public PriorityQ {
	public:
		PriorityQ_Heap() : PriorityQ{}, heapSize{ 0 } {}

		bool isEmpty() override { return heapSize==0? true:false; }
		pair<int, int> extract() override { 
			int min = peek();	   
			pair<int, int> node = getA()[0];
			// auto it = m.find(A[0].first); 	
			// m.erase(it);
			A[0] = A[heapSize-1];
			heapSize--;
			minHeapify(1);
			updateM();
			return node;
		}
		void swapPairByIndex(int pair_A, int pair_B) {
			int t1 = A[pair_A].first; int t2 = A[pair_A].second; // int t3 = m[t1];
			// m[A[pair_A].first] = m[A[pair_B].first];
			// m[A[pair_B].first] = t3;
			A[pair_A].first = A[pair_B].first; 
			A[pair_A].second = A[pair_B].second;
			A[pair_B].first = t1;
			A[pair_B].second = t2;
		}
		void decreaseKey(int vertex, int key) override { 
			int index = m[vertex];	
			if (A[index].second < key) throw invalid_argument{ "[-] in decreaseKey(): key needs to be at least as small. current vertex is: " + to_string(index) + " current key is: " + to_string(A[index].second) + " new key trying to assign is: " + to_string(key) };
			A[index].second = key;
			while (A[index].second < A[PARENT(index+1)-1].second && index > 0) {
				swapPairByIndex(index, (PARENT(index+1)-1));	
				index = PARENT(index+1) - 1;
			}

			updateM();
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

		unordered_map<int, int>& getM() { return m; }

		void print_heap() {
			for (int i = 0; i < heapSize; i++) {
				cout << "( " << A[i].first << ", " << A[i].second << ") ";
			}
			cout << endl;
		}

		void updateM() {
			m.clear();
			for (int i = 0; i < heapSize; i++) {
				m[A[i].first] = i;
			}				
		}

	private:
		size_t heapSize;
		unordered_map<int, int> m;
};


class Dijkstra {
	public:
		Dijkstra() {}

		void init(Graph& g, int s) {
			for (int v = 0; v < g.getNumVertex(); v++) {
				d.push_back(numeric_limits<int>::max());
				pi.push_back(-1);
				S.push_back(0);
			}
			d[s] = 0;
			S[s] = 1;
		}	

		void relax(int u, int v, int w, PriorityQ& q) {
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				pi[v] = u;
				q.decreaseKey(v, d[v]);
			}
		}

		void print_path(int s, int v) {
			if (v == s) 
				cout << s << " ";
			else if (pi[v] == -1) {
				cout << " no path from " << s << " to " << v << " exists." << endl;
			}	
			else {
				print_path(s, pi[v]);
				cout << v << " ";
			}
		}

		void print_S() const {
			cout << "print S:" << endl;
			for (const auto i : S) cout << i << " ";
			cout << endl;
		}

		void print_d() const {
			cout << "print d:" << endl;
			for (const auto i : d) cout << i << " " ;
			cout << endl;
		}

		void print_pi() const {
			cout << "print pi:" << endl;
			for (const auto i : pi) cout << i << " ";
			cout << endl;
		}
		
	protected:
		vector<int> d;
		vector<int> pi;	
		vector<int> S;
};

// Graph: adj matrix; Priority Queue:  array 
class Dijkstra_1 : public Dijkstra {
	public: 
		Dijkstra_1() : Dijkstra() {}

		void findPath(Graph_Matrix& g, int s) {
			init(g, s);
			PriorityQ_Array Q{};
			for (int v = 0; v < g.getNumVertex(); v++) {
				int E = g.getAdjMatrix()[s][v];
				Q.insert(make_pair(v, E));	
			}	

			pi[Q.peek()] = s;

			while (!Q.isEmpty()) {
				pair<int, int> node = Q.extract();
				int u = node.first;
				S[u] = 1;
				d[u] = node.second;
				for (int v = 0;  v < g.getNumVertex(); v++) {
					if (g.getAdjMatrix()[u][v] != numeric_limits<int>::max() && S[v] == 0) 
								relax(u, v, g.getAdjMatrix()[u][v], Q); 
					}	
				}
		}
};


// Graph: adjacency list; Priority Queue: Minimizing Heap

class Dijkstra_2 : public Dijkstra {
	public: 
		Dijkstra_2() : Dijkstra() {}

		void findPath(Graph_List& g, int s) {
			init(g, s);
			PriorityQ_Heap Q{};
		
			for (int i = 0; i < d.size(); i++) {
				Q.insert(make_pair(i, d[i]));
			}

			while (!Q.isEmpty()) {
				pair<int, int> node = Q.extract();
				int u = node.first;
				S[u] = 1;
				d[u] = node.second;
				for (const auto& i : g.getAdjList()[u]) {
					if (S[i.first] == 0) 
						relax(u, i.first, i.second, Q); 
				}
			}
			
		}
};

// optimise
class Dijkstra_3 : public Dijkstra {
	public: 
		Dijkstra_3() : Dijkstra() {}

		void findPath(Graph_List& g, int s) {
			vector<int> dist(g.getNumVertex(), pow(10, 9)); dist[s] = 0; 
			priority_queue<ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s)); 	
			for (int i = 0; i < g.getNumVertex(); i++) { pi.push_back(-1); }
			
			while (!pq.empty()) {
					ii top = pq.top(); pq.pop();		
					int d = top.first, u = top.second;
					if (d == dist[u]) {
						for (const auto& i : g.getAdjList()[u]) {
							int v = i.first; int weight_u_v = i.second;		
							if (dist[u] + weight_u_v < dist[v]) {
								dist[v] = dist[u] + weight_u_v;
								pq.push(ii(dist[v], v));
								pi[v] = u;
							}
						}
					}
			}
		}
};


void logger(string path_input, string path_output, Graph_Matrix G, Dijkstra_1 algo) {
	ifstream input; 
	ofstream output;
	input.open(path_input);
	output.open(path_output, ios::app);

	if (!input || !output) {throw std::runtime_error{"[-] In logger(): Error in opening files"}; }
	
	int num_vertex;
	input >> num_vertex;
	G.setNumVertex(num_vertex);
	
	int source, destination, weight;
    while (input >> source >> destination >> weight) { 
        G.addEdge(source, destination, weight); 
    }

	istream_iterator<int> start(input), end;
		
	const auto t1 = chrono::high_resolution_clock::now();
	algo.findPath(G, 0);
	const auto t2 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> ms_double = t2 - t1;

	output 	<< G.getNumVertex() << ", "
			<< G.getNumEdge() << ", " 
			<< ms_double.count() << "\n";	

	input.close();
	output.close();
}

void logger(string path_input, string path_output, Graph_List G, Dijkstra_2 algo) {
	ifstream input; 
	ofstream output;
	input.open(path_input);
	output.open(path_output, ios::app);

	if (!input || !output) {throw std::runtime_error{"[-] In logger(): Error in opening files"}; }
	
	int num_vertex;
	input >> num_vertex;
	G.setNumVertex(num_vertex);
	
	int source, destination, weight;
    while (input >> source >> destination >> weight) { 
        G.addEdge(source, destination, weight); 
    }

	istream_iterator<int> start(input), end;
		
	const auto t1 = chrono::high_resolution_clock::now();
	algo.findPath(G, 0);
	const auto t2 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> ms_double = t2 - t1;

	output 	<< G.getNumVertex() << ", "
			<< G.getNumEdge() << ", " 
			<< ms_double.count() << "\n";	

	input.close();
	output.close();
}

void logger(string path_input, string path_output, Graph_List G, Dijkstra_3 algo) {
	ifstream input; 
	ofstream output;
	input.open(path_input);
	output.open(path_output, ios::app);

	if (!input || !output) {throw std::runtime_error{"[-] In logger(): Error in opening files"}; }
	
	int num_vertex;
	input >> num_vertex;
	G.setNumVertex(num_vertex);
	
	int source, destination, weight;
    while (input >> source >> destination >> weight) { 
        G.addEdge(source, destination, weight); 
    }

	istream_iterator<int> start(input), end;
		
	const auto t1 = chrono::high_resolution_clock::now();
	algo.findPath(G, 0);
	const auto t2 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> ms_double = t2 - t1;

	output 	<< G.getNumVertex() << ", "
			<< G.getNumEdge() << ", " 
			<< ms_double.count() << "\n";	

	input.close();
	output.close();
}



#endif // PROJECT2_HPP 
