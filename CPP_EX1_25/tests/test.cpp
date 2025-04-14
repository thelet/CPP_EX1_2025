// File: tests/tests.cpp
// Email: thelet.shevach@gmail.com
// This file contains unit tests for the Graph and Algorithms classes using doctest.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"      // Use the doctest header provided by your professor
#include "Graph.h"        // Declaration of class Graph (in namespace graph)
#include "Algorithms.h"   // Declaration of class Algorithms (in namespace graph)

using namespace graph;

// Helper function to compare two Graph objects.
// Returns true if they have the same number of vertices, and for each vertex
// the same number of neighbors with exactly identical (destination, weight)
// pairs in the same order.
bool compareGraphs(const Graph& g1, const Graph& g2) {
    if(g1.getNumVertices() != g2.getNumVertices())
        return false;
    int n = g1.getNumVertices();
    for (int i = 0; i < n; i++) {
        if(g1.getNeighborCount(i) != g2.getNeighborCount(i))
            return false;
        int count = g1.getNeighborCount(i);
        Edge* list1 = g1.getAdjList(i);
        Edge* list2 = g2.getAdjList(i);
        for (int j = 0; j < count; j++) {
            if(list1[j].dest != list2[j].dest || list1[j].weight != list2[j].weight)
                return false;
        }
    }
    return true;
}

TEST_CASE("Graph basic functionality: addEdge and removeEdge") {
    // Create a graph with 3 vertices
    Graph g(3);
    
    // Add edges: 0-1 with weight 3, and 1-2 with weight 2.
    g.addEdge(0, 1, 3);
    g.addEdge(1, 2, 2);
    
    // Verify neighbor counts.
    // In an undirected graph, each added edge appears twice.
    // Vertex 0 should have 1 neighbor (vertex 1).
    CHECK(g.getNeighborCount(0) == 1);
    // Vertex 1 should have 2 neighbors (vertices 0 and 2).
    CHECK(g.getNeighborCount(1) == 2);
    // Vertex 2 should have 1 neighbor (vertex 1).
    CHECK(g.getNeighborCount(2) == 1);

    // Remove edge between 0 and 1.
    CHECK_NOTHROW(g.removeEdge(0, 1));
    // After removal, vertex 0 should have 0 neighbors.
    CHECK(g.getNeighborCount(0) == 0);
    // Vertex 1 should have only 1 neighbor now.
    CHECK(g.getNeighborCount(1) == 1);

    // Removing an edge that doesn't exist should throw an exception.
    CHECK_THROWS_AS(g.removeEdge(0, 2), const char*);
}

TEST_CASE("BFS algorithm generates correct tree structure") {
    // Build a graph with 5 vertices and several edges.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Compute the BFS tree starting from vertex 0.
    Graph* bfsTree = Algorithms::bfs(g, 0);

    // In a BFS tree starting from 0, there should be exactly 4 undirected edges.
    // Since each undirected edge appears twice (once per vertex) in our representation,
    // the total number of entries in the adjacency lists should be 8.
    int totalEdges = 0;
    for (int i = 0; i < bfsTree->getNumVertices(); i++) {
        totalEdges += bfsTree->getNeighborCount(i);
    }
    CHECK(totalEdges / 2 == 4);

    delete bfsTree;
}

TEST_CASE("DFS algorithm generates correct tree structure") {
    // Build a similar graph.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Compute the DFS tree starting from vertex 0.
    Graph* dfsTree = Algorithms::dfs(g, 0);

    // Regardless of the order chosen (which can vary), a DFS tree must have exactly 4 edges.
    int totalEdges = 0;
    for (int i = 0; i < dfsTree->getNumVertices(); i++) {
        totalEdges += dfsTree->getNeighborCount(i);
    }
    CHECK(totalEdges / 2 == 4);

    delete dfsTree;
}


TEST_CASE("BFS algorithm produces the exact expected tree structure") {
    // Build the original graph.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Compute the BFS tree starting at 0.
    Graph* bfsTree = Algorithms::bfs(g, 0);

    // Construct the expected BFS tree.
    // Expected BFS tree (undirected):
    //   Vertex 0: neighbors -> (1, 3) and (2, 1)
    //   Vertex 1: neighbors -> (0, 3)
    //   Vertex 2: neighbors -> (0, 1) and (3, 5)
    //   Vertex 3: neighbors -> (2, 5) and (4, 4)
    //   Vertex 4: neighbors -> (3, 4)
    Graph expected(5);
    expected.addEdge(0, 1, 3);
    expected.addEdge(0, 2, 1);
    expected.addEdge(2, 3, 5);
    expected.addEdge(3, 4, 4);

    // Compare graphs; they must be identical in structure and order.
    CHECK(compareGraphs(*bfsTree, expected));

    delete bfsTree;
}

TEST_CASE("DFS algorithm produces the exact expected tree structure") {
    // Build the original graph.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Compute the DFS tree starting at 0.
    Graph* dfsTree = Algorithms::dfs(g, 0);

    // Construct the expected DFS tree.
    // Assume DFS visits neighbors in the order in which they are added.
    // Expected DFS tree:
    //   From vertex 0: add edge (0,1,3).
    //   From vertex 1: since 0 is already visited, add edge (1,2,2).
    //   From vertex 2: add edge (2,3,5).
    //   From vertex 3: add edge (3,4,4).
    // Thus, the undirected DFS tree is:
    //   Vertex 0: neighbors -> (1, 3)
    //   Vertex 1: neighbors -> (0, 3) and (2, 2)
    //   Vertex 2: neighbors -> (1, 2) and (3, 5)
    //   Vertex 3: neighbors -> (2, 5) and (4, 4)
    //   Vertex 4: neighbors -> (3, 4)
    Graph expected(5);
    expected.addEdge(0, 1, 3);
    expected.addEdge(1, 2, 2);
    expected.addEdge(2, 3, 5);
    expected.addEdge(3, 4, 4);

    CHECK(compareGraphs(*dfsTree, expected));

    delete dfsTree;
}

TEST_CASE("Dijkstra's algorithm computes the shortest path tree") {
    // Build a weighted graph.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Compute the shortest path tree from vertex 0 using Dijkstra's algorithm.
    Graph* dijkstraTree = Algorithms::dijkstra(g, 0);

    // The shortest path tree should have 4 edges (undirected: total entries should be 8).
    int totalEdges = 0;
    for (int i = 0; i < dijkstraTree->getNumVertices(); i++) {
        totalEdges += dijkstraTree->getNeighborCount(i);
    }
    CHECK(totalEdges / 2 == 4);

    delete dijkstraTree;
}

TEST_CASE("Prim's and Kruskal's algorithms yield a minimum spanning tree with correct weight") {
    // Build a graph with 5 vertices.
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 4);

    // Expected MST for this graph consists of edges with weights 1, 2, 5, and 4. Total weight = 12.
    // Compute MST using Prim's algorithm.
    Graph* primTree = Algorithms::prim(g);
    int primEdges = 0, primTotalWeight = 0;
    for (int i = 0; i < primTree->getNumVertices(); i++) {
        int count = primTree->getNeighborCount(i);
        primEdges += count;
        Edge* neighbors = primTree->getAdjList(i);
        for (int j = 0; j < count; j++) {
            primTotalWeight += neighbors[j].weight;
        }
    }
    // Since each undirected edge is stored twice:
    primEdges /= 2;
    primTotalWeight /= 2;
    CHECK(primEdges == 4);
    CHECK(primTotalWeight == 12);
    delete primTree;

    // Compute MST using Kruskal's algorithm.
    Graph* kruskalTree = Algorithms::kruskal(g);
    int kruskalEdges = 0, kruskalTotalWeight = 0;
    for (int i = 0; i < kruskalTree->getNumVertices(); i++) {
        int count = kruskalTree->getNeighborCount(i);
        kruskalEdges += count;
        Edge* neighbors = kruskalTree->getAdjList(i);
        for (int j = 0; j < count; j++) {
            kruskalTotalWeight += neighbors[j].weight;
        }
    }
    kruskalEdges /= 2;
    kruskalTotalWeight /= 2;
    CHECK(kruskalEdges == 4);
    CHECK(kruskalTotalWeight == 12);
    delete kruskalTree;
}

TEST_CASE("Dijkstra error on negative weight") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, -2);  // negative weight
    CHECK_THROWS_WITH_AS(Algorithms::dijkstra(g, 0), "Negative weight edge encountered in Dijkstra algorithm", const char*);
}

TEST_CASE("Prim error on negative weight") {
    Graph g(3);
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, -3);
    CHECK_THROWS_WITH_AS(Algorithms::prim(g), "Negative weight edge encountered in Prim algorithm", const char*);
}

TEST_CASE("Kruskal error on negative weight") {
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, -1);
    CHECK_THROWS_WITH_AS(Algorithms::kruskal(g), "Negative weight edge encountered in Kruskal algorithm", const char*);
}




