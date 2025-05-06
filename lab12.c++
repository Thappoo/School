#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>
using namespace std;

const int INF = numeric_limits<int>::max();

struct PQNode {
    int vertex;
    int distance;

    bool operator>(const PQNode& other) const {
        return distance > other.distance;
    }
};

class PriorityQueue {
    private:
        vector<PQNode> heap;
    
        void heapifyUp(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (heap[index] > heap[parent]) break;
                swap(heap[index], heap[parent]);
                index = parent;
            }
        }
    
        void heapifyDown(int index) {
            int left, right, smallest;
            while (true) {
                left = 2 * index + 1;
                right = 2 * index + 2;
                smallest = index;
    
                if (left < heap.size() && !(heap[left] > heap[smallest])) {
                    smallest = left;
                }
                if (right < heap.size() && !(heap[right] > heap[smallest])) {
                    smallest = right;
                }
                if (smallest == index) break;
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
        }
    
    public:
        void push(PQNode node) {
            heap.push_back(node);
            heapifyUp(heap.size() - 1);
        }
    
        PQNode pop() {
            PQNode top = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                heapifyDown(0);
            }
            return top;
        }
    
        bool empty() const {
            return heap.empty();
        }
    };

// Graph class using adjacency list
class Graph {
private:
    int Vertices;
    vector<vector<pair<int, int>>> adjList; 

public:
    Graph(int v) {
        Vertices = v;
        adjList.resize(Vertices);
    }

    // Add edge to graph (undirected or directed depending on use case)
    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    // Iterator to get all adjacent vertices
    const vector<pair<int, int>>& getNeighbors(int u) const {
        return adjList[u];
    }

    int getNumVertices() const {
        return Vertices;
    }

    // Display graph for verification
    void displayGraph() const {
        cout << "Graph adjacency list:\n";
        for (int u = 1; u < Vertices; ++u) {
            cout << "Vertex " << u << ": ";
            for (auto& neighbor : adjList[u]) {
                cout << "(" << neighbor.first << ", w=" << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

// Dijkstra Version 1: source to all vertices
void dijkstraAll(const Graph& graph, int source, vector<int>& dist, vector<int>& pred) {
    int V = graph.getNumVertices();
    dist.assign(V, INF);
    pred.assign(V, -1);
    dist[source] = 0;

    PriorityQueue pq;
    pq.push({source, 0});

    while (!pq.empty()) {
        int u = pq.pop().vertex;
        int d = dist[u]; // Get current distance

        for (auto [v, weight] : graph.getNeighbors(u)) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }
}

// Dijkstra Version 2: source to one destination
int dijkstraOneDestination(const Graph& graph, int source, int dest, vector<int>& pred) {
    int V = graph.getNumVertices();
    vector<int> dist(V, INF);
    pred.assign(V, -1);
    dist[source] = 0;

    PriorityQueue pq;
    pq.push({source, 0});

    while (!pq.empty()) {
        int u = pq.pop().vertex;
        int d = dist[u];

        if (u == dest) break;

        for (auto [v, weight] : graph.getNeighbors(u)) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    return dist[dest];
}

// Dijkstra Version 3: source to multiple destinations
void dijkstraMultiple(const Graph& graph, int source, const vector<int>& destinations, vector<int>& dist, vector<int>& pred) {
    dijkstraAll(graph, source, dist, pred);

    cout << "\nShortest distances from source " << source << " to multiple destinations:\n";
    for (int dest : destinations) {
        cout << "To " << dest << " = " << (dist[dest] == INF ? -1 : dist[dest]) << "\n";
    }
}

// Helper to print distance and predecessor arrays
void printResults(const vector<int>& dist, const vector<int>& pred) {
    cout << "\nDistance array:\n";
    for (size_t i = 1; i < dist.size(); ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }

    cout << "\nPredecessor array:\n";
    for (size_t i = 1; i < pred.size(); ++i) {
        cout << "Vertex " << i << ": " << pred[i] << endl;
    }
}

int main() {
    Graph g(6); 


    return 0;
}