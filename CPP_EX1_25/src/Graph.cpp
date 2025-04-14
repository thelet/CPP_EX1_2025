/*
 * Email: thelet.shevach@gmail.com
 * File: Graph.cpp
 * Description: Implementation of the Graph class within the namespace graph.
 */

#include <cstdio>
#include "Graph.h"

namespace graph {

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjLists = new Edge*[numVertices];
    neighborCount = new int[numVertices];
    neighborCapacity = new int[numVertices];
    // Initialize each vertex’s neighbor array with an initial capacity.
    for (int i = 0; i < numVertices; i++) {
        neighborCount[i] = 0;
        neighborCapacity[i] = 2;
        adjLists[i] = new Edge[neighborCapacity[i]];
    }
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete[] adjLists[i];
    }
    delete[] adjLists;
    delete[] neighborCount;
    delete[] neighborCapacity;
}

void Graph::addEdgeHelper(int src, int dest, int weight) {
    // Do nothing if the edge already exists.
    for (int i = 0; i < neighborCount[src]; i++) {
        if (adjLists[src][i].dest == dest)
            return;
    }
    // Resize the neighbor array if needed.
    if (neighborCount[src] >= neighborCapacity[src]) {
        int newCap = neighborCapacity[src] * 2;
        Edge* newArr = new Edge[newCap];
        for (int i = 0; i < neighborCount[src]; i++) {
            newArr[i] = adjLists[src][i];
        }
        delete[] adjLists[src];
        adjLists[src] = newArr;
        neighborCapacity[src] = newCap;
    }
    // Add the new edge.
    adjLists[src][neighborCount[src]].dest = dest;
    adjLists[src][neighborCount[src]].weight = weight;
    neighborCount[src]++;
}

bool Graph::removeEdgeHelper(int src, int dest) {
    int index = -1;
    for (int i = 0; i < neighborCount[src]; i++) {
        if (adjLists[src][i].dest == dest) {
            index = i;
            break;
        }
    }
    if (index == -1)
        return false;
    // Shift remaining edges left.
    for (int i = index; i < neighborCount[src] - 1; i++) {
        adjLists[src][i] = adjLists[src][i + 1];
    }
    neighborCount[src]--;
    return true;
}

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
        printf("Error: vertex out of range\n");
        return;
    }
    // Add for both endpoints (undirected graph).
    addEdgeHelper(src, dest, weight);
    if (src != dest)
        addEdgeHelper(dest, src, weight);
}

void Graph::removeEdge(int src, int dest) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
        printf("Error: vertex out of range\n");
        return;
    }
    bool removed = removeEdgeHelper(src, dest);
    if (!removed)
        throw "Edge does not exist";
    removed = removeEdgeHelper(dest, src);
    if (!removed)
        throw "Edge does not exist in mirror";
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d:", i);
        for (int j = 0; j < neighborCount[i]; j++) {
            printf(" -> (%d, w=%d)", adjLists[i][j].dest, adjLists[i][j].weight);
        }
        printf("\n");
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

Edge* Graph::getAdjList(int vertex) const {
    if (vertex < 0 || vertex >= numVertices) 
        return nullptr;
    return adjLists[vertex];
}

int Graph::getNeighborCount(int vertex) const {
    if (vertex < 0 || vertex >= numVertices)
        return -1;
    return neighborCount[vertex];
}

} // namespace graph
