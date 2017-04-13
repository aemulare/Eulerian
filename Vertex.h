#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Graph;                                                               // Forward Graph class declaration (needs to use a pointer to Graph)

class Vertex
{
public:
   Vertex(Graph * const g, int number);                                    // Constructor

   int number() const { return vertexNumber; }                             // Vertex ordinal number within the graph
   string name() const;                                                    // Vertex name based on the number (a, b, c, ...)

   int edgesCount() const { return int(edges.size()); }                    // The total number of adjacent edges 
   int degree() const;                                                     // Returns the vertex degree
   bool isOddDegree() const { return degree() % 2 != 0; }                  // Determines whether the vertex has an odd degree

   bool isVisited() const { return visited; }                              // Determines whether the vertex is visited during traverse
   void visit() { visited = true; }                                        // Marks the vertex as visited
   void reset() { visited = false; }                                       // Marks the vertex as unvisited preparing it for traverse

   void addEdge(int index, int count);                                     // Adds the new edge to the vertex

   Vertex& neighborAt(int index);                                          // Gets a vertex neighbor by the specified index in the edges collection
   bool isValidNextEdge(Vertex& neighbor);
   bool isValidNeighborAt(int index) const { return edges[index] != -1; }  // Determines whether the specified neighbor is valid (number != -1)

   int reachableVerticesCount();                                           // Returns the total number of reachable vertixes from the given vertex
   void traverse();                                                        // Perform recursive traverse for the given vertex
   void printEulerTrailEdge(ostream& os);                                      // Prints the part of Euler trail part staring from the given vertex

   friend ostream& operator <<(ostream& os, Vertex& v);                    // Overridden output operator

private:
   void removeEdge(Vertex& neighbor);                                      // Removes the specified edge between the given vertex and its neighbor
   int loopsCount() const;                                                 // The total number of loops for the given vertex

   vector<int> edges;                                                      // The collection of incident edges (as numbers of neighbor vertices)
   int vertexNumber;                                                       // Vertex number using for naming (staring from 0)
   bool visited;                                                           // The flag determining whether the vertex is visited during traverse operation

   Graph * graph;                                                          // Pointer to the graph containing the vertex (needs to retrieve edges)

   static char * symbols() { return "abcdefghijklmnopqrstuvwxyz"; }        // The array of letters used to select the vertext name
};
