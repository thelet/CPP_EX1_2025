/*
 * Email: thelet.shevach@gmail.com
 * File: Algorithms.h
 * Description: Declaration of the Algorithms class within the namespace graph.
 */

 #ifndef ALGORITHMS_H
 #define ALGORITHMS_H
 
 #include "Graph.h"
 
 namespace graph {
 
 class Algorithms {
 public:
     // Returns a pointer to a new Graph representing a BFS tree starting from src.
     static Graph* bfs(const Graph& graph, int src);
     
     // Returns a pointer to a new Graph representing a DFS tree starting from src.
     static Graph* dfs(const Graph& graph, int src);
     
     // Returns a pointer to a new Graph representing the shortest paths tree using Dijkstra's algorithm.
     static Graph* dijkstra(const Graph& graph, int src);
     
     // Returns a pointer to a new Graph representing the Minimum Spanning Tree using Prim's algorithm.
     static Graph* prim(const Graph& graph);
     
     // Returns a pointer to a new Graph representing the Minimum Spanning Tree using Kruskal's algorithm.
     static Graph* kruskal(const Graph& graph);
 };
 
 } // namespace graph
 
 #endif // ALGORITHMS_H
 