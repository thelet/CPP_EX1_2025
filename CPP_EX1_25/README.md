# Graph Algorithms Assignment

**Email:** thelet.shevach@gmail.com

## Overview

This project implements a graph using an adjacency list and provides several classical graph algorithms in C++ without relying on the STL (except for standard I/O and basic facilities). The algorithms included are:

- **Breadth-First Search (BFS)**
- **Depth-First Search (DFS)**
- **Dijkstra's Shortest Path Algorithm** (with error checking for negative weights)
- **Prim's Minimum Spanning Tree (MST) Algorithm** (with error checking for negative weights)
- **Kruskal's Minimum Spanning Tree (MST) Algorithm** (with error checking for negative weights)

In addition, the project includes error handling to detect negative weights (which are unsupported by some algorithms) and demonstrates proper memory management, even when errors occur.


## Features


## Features

- **Graph Representation:**  
  The graph is represented as an adjacency list using dynamically allocated arrays for each vertex. Each vertex stores its neighbors as an array of `Edge` structures, where each `Edge` contains a destination vertex and a weight.

- **Graph Algorithms:**  
  The algorithms provided include BFS, DFS, Dijkstra's, Prim's, and Kruskal's. These algorithms construct spanning trees based on the original graph. In cases where negative weights are not supported (e.g., Dijkstra, Prim, and Kruskal), the algorithm throws an error and cleans up any allocated memory.

- **Error Handling and Memory Management:**  
  Functions verify input validity (vertex indices) and check for negative weights where not allowed. If an error occurs, the functions free allocated memory and throw a specific exception message.

- **Testing:**  
  Unit tests are written using the [doctest](https://github.com/onqtam/doctest) framework. The tests compare internal graph structures and check both normal and error conditions.

## Graph Output Format

The graph is printed using the `printGraph()` function defined in `Graph.cpp`. Here’s how the output is structured:

- **Line-by-Line Output:**  
  Each vertex in the graph is printed on a separate line.

- **Vertex Label:**  
  The line begins with the text `"Vertex i:"` where `i` is the vertex number (starting from 0).

- **Neighbor List:**  
  For each vertex, its list of neighbors is printed sequentially. Each neighbor is shown in the format:  
  `-> (destination, w=weight)`  
  For example, if vertex 0 has an edge to vertex 2 with a weight of 1, the output for vertex 0 will include:
  Vertex 0: -> (2, w=1)

ruby
Copy

- **Undirected Representation:**  
Since the graph is undirected, every edge appears twice in the printed output—once for each endpoint. For instance, if there is an edge between vertices 0 and 1 (weight 3), vertex 0’s line will include `"-> (1, w=3)"` and vertex 1’s line will include `"-> (0, w=3)"`.

- **Example Output:**  
```cpp
g.addEdge(0, 1, 3);
g.addEdge(0, 2, 1);
g.addEdge(1, 2, 2);
g.addEdge(2, 3, 5);
g.addEdge(3, 4, 4);

The expected output of printGraph() might be:

```rust
Vertex 0: -> (1, w=3) -> (2, w=1)
Vertex 1: -> (0, w=3) -> (2, w=2)
Vertex 2: -> (0, w=1) -> (1, w=2) -> (3, w=5)
Vertex 3: -> (2, w=5) -> (4, w=4)
Vertex 4: -> (3, w=4)

This output format allows you to clearly see which vertices are connected and with what weight, and it is used both for debugging and verifying algorithm correctness in the tests.

- **Memory Management:**  
  The project explicitly deletes all dynamic memory (for neighbor lists and temporary arrays in algorithms) to avoid leaks, and tests can be run under Valgrind to ensure that there are no memory leaks.

## Build and Run Instructions

### Requirements

- **Operating System:** Linux/Ubuntu (or another Linux distribution)
- **Compiler:** `g++` 
- **Valgrind:** For memory leak checking
- **Make:** To run the provided Makefile

### Using the Makefile

A sample Makefile is provided with targets to build the main demonstration, run the tests, perform memory leak checks using Valgrind, and clean up build artifacts.

Key targets in the Makefile:

- **Main Demonstration:**  
  ```bash
  make Main
Compiles src/main.cpp, src/Graph.cpp, and src/Algorithms.cpp into an executable named main.

Run Tests:

 ```bash
  make test
Compiles the test file tests/test.cpp (together with the source files) and runs the resulting executable. The tests are built with doctest (see #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN).

Memory Leak Check (Main):

 ```bash
  make valgrind
Runs the main executable under Valgrind with full leak checking.

Memory Leak Check (Tests):
You can add or use a target to run the tests under Valgrind if desired.

Clean Up:

 ```bash
  make clean
Removes generated executables.
