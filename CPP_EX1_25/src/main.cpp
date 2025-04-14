/*
 * Email: thelet.shevach@gmail.com
 * File: main.cpp
 * Description: Demonstrates usage of the Graph and Algorithms classes.
 */

 #include <iostream>
 #include "Graph.h"
 #include "Algorithms.h"
 
 using namespace graph;
 
 int main() {
     std::cout << "Graph Demonstration\n" << std::endl;
 
     // Create a graph with 5 vertices and add several edges.
     Graph g(5);
     g.addEdge(0, 1, 3);
     g.addEdge(0, 2, 1);
     g.addEdge(1, 2, 2);
     g.addEdge(2, 3, 5);
     g.addEdge(3, 4, 4);
     g.addEdge(0, 4, 4);
     g.addEdge(0, 2, 4);
 
     std::cout << "Original Graph:" << std::endl;
     g.printGraph();
 
     // Remove an edge and display updated graph.
     try {
         g.removeEdge(0, 1);
         std::cout << "\nGraph after removing edge between 0 and 1:" << std::endl;
         g.printGraph();
     } catch (const char* error) {
         std::cout << "Error while removing edge: " << error << std::endl;
     }
 
     // Compute and print BFS tree starting from vertex 0.
     Graph* bfsTree = Algorithms::bfs(g, 0);
     std::cout << "\nBFS Tree (starting from vertex 0):" << std::endl;
     bfsTree->printGraph();
     delete bfsTree;
 
     // Compute and print DFS tree starting from vertex 0.
     Graph* dfsTree = Algorithms::dfs(g, 0);
     std::cout << "\nDFS Tree (starting from vertex 0):" << std::endl;
     dfsTree->printGraph();
     delete dfsTree;
 
     // Compute and print Dijkstra's shortest path tree.
     try {
         Graph* dijkstraTree = Algorithms::dijkstra(g, 0);
         std::cout << "\nDijkstra's Shortest Path Tree (from vertex 0):" << std::endl;
         dijkstraTree->printGraph();
         delete dijkstraTree;
     } catch (const char* error) {
         std::cout << "Error in Dijkstra's algorithm: " << error << std::endl;
     }
 
     // Compute and print Prim's minimum spanning tree.
     try {
         Graph* primTree = Algorithms::prim(g);
         std::cout << "\nPrim's Minimum Spanning Tree:" << std::endl;
         primTree->printGraph();
         delete primTree;
     } catch (const char* error) {
         std::cout << "Error in Prim's algorithm: " << error << std::endl;
     }
 
     // Compute and print Kruskal's minimum spanning tree.
     try {
         Graph* kruskalTree = Algorithms::kruskal(g);
         std::cout << "\nKruskal's Minimum Spanning Tree:" << std::endl;
         kruskalTree->printGraph();
         delete kruskalTree;
     } catch (const char* error) {
         std::cout << "Error in Kruskal's algorithm: " << error << std::endl;
     }
 
     // Demonstrate error handling: create a graph with a negative weight edge.
     Graph g_error(3);
     g_error.addEdge(0, 1, 5);
     g_error.addEdge(1, 2, -2); // Negative weight to cause an error.
     
     try {
         // This call should throw an exception because of the negative weight.
         Graph* errorTree = Algorithms::dijkstra(g_error, 0);
         // If no exception is thrown, print the (unexpected) tree.
         std::cout << "\nDijkstra's Tree (unexpectedly computed on graph with negative weight):" << std::endl;
         errorTree->printGraph();
         delete errorTree;
     } catch (const char* error) {
         std::cout << "\nCaught error from Dijkstra's algorithm (negative weight): " << error << std::endl;
     }
 
     return 0;
 }
 