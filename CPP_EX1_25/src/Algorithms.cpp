/*
 * Email: thelet.shevach@gmail.com
 * File: Algorithms.cpp
 * Description: Implementation of the Algorithms class within the namespace graph.
 */

 #include <cstdio>
 #include <cstdlib>
 #include "Algorithms.h"
 
 namespace graph {
 
 // --- Simple Queue Implementation for BFS ---
 class Queue {
 private:
     int* data;
     int front, rear, capacity;
 public:
     Queue(int cap) : front(0), rear(0), capacity(cap){
         data = new int[capacity];
     }
     ~Queue() {
         delete[] data;
     }
     void enqueue(int value) {
         // Resize if needed.
         if ((rear + 1) % capacity == front) {
             int newCap = capacity * 2;
             int* newData = new int[newCap];
             int size = (rear - front + capacity) % capacity;
             for (int i = 0; i < size; i++) {
                 newData[i] = data[(front + i) % capacity];
             }
             front = 0;
             rear = size;
             capacity = newCap;
             delete[] data;
             data = newData;
         }
         data[rear] = value;
         rear = (rear + 1) % capacity;
     }
     int dequeue() {
         if (isEmpty())
             return -1; // Error condition.
         int value = data[front];
         front = (front + 1) % capacity;
         return value;
     }
     bool isEmpty() {
         return front == rear;
     }
 };
 
 // --- BFS Implementation ---
 Graph* Algorithms::bfs(const Graph& g, int src) {
     int n = g.getNumVertices();
     Graph* tree = new Graph(n);
     bool* visited = new bool[n];
     for (int i = 0; i < n; i++)
         visited[i] = false;
 
     Queue queue(n);
     visited[src] = true;
     queue.enqueue(src);
 
     while (!queue.isEmpty()) {
         int current = queue.dequeue();
         int count = g.getNeighborCount(current);
         Edge* neighbors = g.getAdjList(current);
         for (int i = 0; i < count; i++) {
             int neighbor = neighbors[i].dest;
             if (!visited[neighbor]) {
                 visited[neighbor] = true;
                 queue.enqueue(neighbor);
                 // Add edge to the BFS tree.
                 tree->addEdge(current, neighbor, neighbors[i].weight);
             }
         }
     }
     delete[] visited;
     return tree;
 }
 
 // --- DFS Implementation ---
 Graph* Algorithms::dfs(const Graph& g, int src) {
     int n = g.getNumVertices();
     Graph* tree = new Graph(n);
     bool* visited = new bool[n];
     for (int i = 0; i < n; i++)
         visited[i] = false;
 
     // Define a helper structure for recursion.
     struct DFSHelper {
         static void dfsVisit(const Graph& g, int current, bool* visited, Graph* tree) {
             visited[current] = true;
             int count = g.getNeighborCount(current);
             Edge* neighbors = g.getAdjList(current);
             for (int i = 0; i < count; i++) {
                 int neighbor = neighbors[i].dest;
                 if (!visited[neighbor]) {
                     tree->addEdge(current, neighbor, neighbors[i].weight);
                     dfsVisit(g, neighbor, visited, tree);
                 }
             }
         }
     };
 
     DFSHelper::dfsVisit(g, src, visited, tree);
     delete[] visited;
     return tree;
 }
 
 // --- Dijkstra's Algorithm ---
 Graph* Algorithms::dijkstra(const Graph& g, int src) {
    int n = g.getNumVertices();
    Graph* tree = new Graph(n);
    int* dist = new int[n];
    bool* visited = new bool[n];
    int* parent = new int[n];

    for (int i = 0; i < n; i++) {
        dist[i] = 1000000;  // A large number to represent infinity.
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int i = 0; i < n; i++) {
        // Find the unvisited vertex with the smallest distance.
        int minDist = 1000000;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        int count = g.getNeighborCount(u);
        Edge* neighbors = g.getAdjList(u);
        for (int k = 0; k < count; k++) {
            // If a negative weight is encountered, free allocated memory and delete the tree.
            if (neighbors[k].weight < 0) {
                delete[] dist;
                delete[] visited;
                delete[] parent;
                delete tree;
                throw "Negative weight edge encountered in Dijkstra algorithm";
            }

            int v = neighbors[k].dest;
            int weight = neighbors[k].weight;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Build the shortest path tree.
    for (int i = 0; i < n; i++) {
        if (i != src && parent[i] != -1) {
            int count = g.getNeighborCount(parent[i]);
            Edge* neighbors = g.getAdjList(parent[i]);
            int w = 1;
            for (int k = 0; k < count; k++) {
                if (neighbors[k].dest == i) {
                    w = neighbors[k].weight;
                    break;
                }
            }
            tree->addEdge(parent[i], i, w);
        }
    }

    delete[] dist;
    delete[] visited;
    delete[] parent;
    return tree;
}


 
 // --- Prim's Algorithm ---
 Graph* Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph* tree = new Graph(n);
    bool* inTree = new bool[n];
    int* key = new int[n];
    int* parent = new int[n];

    for (int i = 0; i < n; i++) {
        inTree[i] = false;
        key[i] = 1000000;
        parent[i] = -1;
    }
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int minKey = 1000000;
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!inTree[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }
        if (u == -1) break;
        inTree[u] = true;

        int neighCount = g.getNeighborCount(u);
        Edge* neighbors = g.getAdjList(u);
        for (int j = 0; j < neighCount; j++) {
            // If a negative weight is encountered, free allocated memory and delete the tree.
            if (neighbors[j].weight < 0) {
                delete[] inTree;
                delete[] key;
                delete[] parent;
                delete tree;
                throw "Negative weight edge encountered in Prim algorithm";
            }
            int v = neighbors[j].dest;
            int weight = neighbors[j].weight;
            if (!inTree[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (parent[i] != -1)
            tree->addEdge(parent[i], i, key[i]);
    }

    delete[] inTree;
    delete[] key;
    delete[] parent;
    return tree;
}

 
 // --- Kruskal's Algorithm ---
 // A simple union-find structure to help build MST.
 Graph* Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph* tree = new Graph(n);

    int totalEdges = 0;
    for (int i = 0; i < n; i++) {
        totalEdges += g.getNeighborCount(i);
    }
    totalEdges /= 2;

    struct EdgeInfo {
        int src;
        int dest;
        int weight;
    };
    EdgeInfo* edges = new EdgeInfo[totalEdges];
    int index = 0;
    for (int i = 0; i < n; i++) {
        int count = g.getNeighborCount(i);
        Edge* neighbors = g.getAdjList(i);
        for (int j = 0; j < count; j++) {
            int dest = neighbors[j].dest;
            // Check for negative weight 
            if (neighbors[j].weight < 0) {
                delete[] edges;
                delete tree;
                throw "Negative weight edge encountered in Kruskal algorithm";
            }
            if (i < dest) { // Avoid duplicates.
                edges[index].src = i;
                edges[index].dest = dest;
                edges[index].weight = neighbors[j].weight;
                index++;
            }
        }
    }

    // Sort edges by weight using bubble sort.
    for (int i = 0; i < totalEdges - 1; i++) {
        for (int j = 0; j < totalEdges - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                EdgeInfo temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    //  union-find implementation.
    class UnionFind {
    private:
        int* parent;
        int* rank;
        int size;
    public:
        UnionFind(int n) : size(n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        ~UnionFind() {
            delete[] parent;
            delete[] rank;
        }
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        void unionSets(int x, int y) {
            int xRoot = find(x);
            int yRoot = find(y);
            if (xRoot == yRoot) return;
            if (rank[xRoot] < rank[yRoot])
                parent[xRoot] = yRoot;
            else if (rank[xRoot] > rank[yRoot])
                parent[yRoot] = xRoot;
            else {
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
        }
    };

    UnionFind uf(n);
    int edgeCount = 0;
    for (int i = 0; i < totalEdges && edgeCount < n - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
            tree->addEdge(u, v, edges[i].weight);
            edgeCount++;
        }
    }

    delete[] edges;
    return tree;
}
 }

 // namespace graph
 