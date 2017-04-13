#pragma once
#include <fstream>
#include <vector>
#include "Vertex.h"
using namespace std;

class Graph
{
public:
   Graph(ifstream& ifs);         // Constructor (accepts open file stream)

   int V() const { return int(vertices.size()); }  // The total number of the graph vertices

   bool isEulerian();            // Determines whether the graph is Eulerian (has Euler circuit or path)
   bool isEulerianCircuit();     // Determines whether the graph has Euler circuit (all vertices are even)
   bool isEulerianPath();        // Determines whether the graph has Euler path (exactly two odd vertices)
   bool isConnected();           // Determines whether the graph is connected (all non-zero vertices are connected)

   Vertex& vertexAt(int index) { return vertices[index]; }     // Returns a vertex by the specified index in the vertex collection

   void resetVertices();                                       // Resets all vertices marking them as non-visited
   void printEulerTrail(ostream& os);                          // Prints Euler trail, if any

   friend ostream& operator <<(ostream& os, Graph& g);         // Overridden output operator to Print summary about the graph

private:
   vector<Vertex> vertices;               // A collection of the graph vertices
   int oddVerticesCount() const;          // The total number of odd vertices in the given graph
};
