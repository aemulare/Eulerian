#include "Graph.h"

// Constructor
Graph::Graph(ifstream& ifs)
{
	// read in the matrix from file
   vector<int> matrix;
   int matrix_element;
   while (ifs >> matrix_element)
      matrix.push_back(matrix_element);

   // calculate the number of vertices
   int v = static_cast<int>(sqrt(matrix.size()));

   
   for (int i = 0; i < v; i++)
   {
	   // create vertex object
      Vertex vertex(this, i);

	  // add vertex to collection of the graph's vertices
      vertices.push_back(vertex);

	  // build a connection between vertex and its neighbors
      for (int j = 0; j < v; j++)
         vertices[i].addEdge(j, matrix[i*v + j]);
   }
}


// Label all vertices as unvisited
void Graph::resetVertices()
{
   for (int i = 0; i < V(); i++)
      vertices[i].reset();
}


// Print summary for the given graph
ostream& operator <<(ostream& os, Graph& g)
{
   os << "   Number of vertices \tV = " << g.V() << endl;
   os << "   Connected: \t\t" << (g.isConnected() ? "YES" : "NO") << endl;
   os << "   Euler Circuit: \t" << (g.isEulerianCircuit() ? "YES" : "NO") << endl;
   os << "   Euler Path: \t\t" << (g.isEulerianPath() ? "YES" : "NO") << endl;
  

   if (g.isEulerian())
      g.printEulerTrail(os);

   return os;
}

// Determine the starting point for Euler trail (path or circuit)
// Print either the Euler Path or Circuit as a sequence of edges (e.g. a-b b-c c-a)
void Graph::printEulerTrail(ostream& os)
{
   int startIndex = 0;

   // start an Euler path from the first odd vertex 
   // otherwise, start an Euler circuit from the first even vertex
   for (int i = 0; i < V(); i++)
   {
      if (vertices[i].isOddDegree())
      {
         startIndex = i;
         break;
      }
   }

   os << endl;

   // print header
   if(isEulerianPath())
	 os << "   Euler Path:" << endl << endl;
   if (isEulerianCircuit())
	 os << "   Euler Circuit:" << endl << endl;

   // print trail
   vertexAt(startIndex).printEulerTrailEdge(os);
   os << endl;
}



// Returns the number of odd vertices from the graph
// Iterates through the all vertices collection and count odd vertices
int Graph::oddVerticesCount() const
{
   int odd = 0;
   for (int i = 0; i < V(); i++)
      if (vertices[i].isOddDegree())
         odd++;

   return odd;
}



// Determines whether the graph has Euler path (exactly two odd vertices)
bool Graph::isEulerianPath()
{
   return isConnected() && oddVerticesCount() == 2;
}



// Determines whether the graph has Euler circuit (all vertices are even)
bool Graph::isEulerianCircuit()
{
   return isConnected() && oddVerticesCount() == 0;
}



// Determines whether the graph is Euler or semi-Euler (has Euler circuit or path)
bool Graph::isEulerian()
{
   return isEulerianCircuit() || isEulerianPath();
}



// Determines whether the graph contains all vertices with non-zero degree connected
bool Graph::isConnected()
{
   resetVertices();
   int i;
   for (i = 0; i < V(); i++)
      if (vertices[i].degree() > 0)
         break;

   if (i == V())
      return false;

   vertices[i].traverse();

   for (i = 0; i < V(); i++)
      if (!vertices[i].isVisited() && vertices[i].degree() > 0)
         return false;

   return true;
}
