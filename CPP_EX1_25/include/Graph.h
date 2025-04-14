/*
 * Email: thelet.shevach@gmail.com
 * File: Graph.h
 * Description: Declaration of the Graph class within the namespace graph.
 */

#ifndef GRAPH_H
#define GRAPH_H

namespace graph {

struct Edge {
    int dest;
    int weight;
};

class Graph {
private:
    int numVertices;       // Fixed number of vertices.
    Edge** adjLists;       // Dynamic array for each vertex’s neighbor list.
    int* neighborCount;    // Current number of neighbors for each vertex.
    int* neighborCapacity; // Capacity of each neighbor array.
    
    // Helper functions.
    void addEdgeHelper(int src, int dest, int weight);
    bool removeEdgeHelper(int src, int dest);
    
public:
    // Constructor and destructor.
    Graph(int numVertices);
    ~Graph();
    
    // Public methods.
    void addEdge(int src, int dest, int weight = 1);
    void removeEdge(int src, int dest);
    void printGraph();
    
    // Getters – used for algorithms.
    int getNumVertices() const;
    Edge* getAdjList(int vertex) const;
    int getNeighborCount(int vertex) const;

};

} // namespace graph

#endif // GRAPH_H
