#include "Vertex.h"
#include "Graph.h"
#include <string>

// Constructor
// Accepts the integer sequential number used as a vertex naming
Vertex::Vertex(Graph * const g, int number)
{
   vertexNumber = number;        // Each vertex has sequential number starting from zero
   visited = false;              // It is not visited initially
   graph = g;
}



// Vertex name based on the number
// If number of vertices <= 26, vertices names are English letters
// otherwise, vertices names are v1, v2, v3...
string Vertex::name() const
{
   if (graph->V() <= 26)
   {
      char letter = symbols()[vertexNumber];
      string name(1, letter);
      return name;
   }
   return "v" + to_string(vertexNumber);
}



// Gets a vertex neighbor by the specified index in the edges collection
Vertex& Vertex::neighborAt(int index)
{
   return graph->vertexAt(edges[index]);
}



// Adds the new incident edge to the vertex.
// neighborNumber: neighbor vertex number which this vertex is connected to.
// count: the total number of edges incident with the given vertex and its neighbor.
void Vertex::addEdge(int neighborNumber, int count)
{
   for (int i = 0; i < count; i++)
      edges.push_back(neighborNumber);
}



// Removes the specified edge between the given vertex and its neighbor
void Vertex::removeEdge(Vertex& neighbor)
{
   for (int i = 0; i < edgesCount(); i++)
   {
      if (edges[i] == neighbor.number())     // Finds the number of the specified vertex in the edges collection
      {
         edges[i] = -1;                      // Marks the found neighbor as invalid
         break;
      }
   }
}



// Returns the vertex degree
int Vertex::degree() const
{
   return int(edges.size()) + loopsCount();        // Determined as number of edges + number of loops
}



// Returns the number of loops for the given vertex
int Vertex::loopsCount() const
{
   int count = 0;
   for (int i = 0; i < edgesCount(); i++)
   {
      if (number() == edges[i])
         count++;
   }
   return count;
}



// Returns the total number of reachable vertixes from the given vertex
int Vertex::reachableVerticesCount()
{
   visit();
   int count = 1;
   for (int i = 0; i < edgesCount(); i++)
   {
      if (isValidNeighborAt(i))
      {
         Vertex& neighbor = neighborAt(i);
         if (!neighbor.isVisited())
            count += neighbor.reachableVerticesCount();
      }
   }
   return count;
}



void Vertex::traverse()
{
   visit();
   for (int i = 0; i < edgesCount(); i++)
   {
      Vertex& neighbord = neighborAt(i);
      if (!neighbord.isVisited())
         neighbord.traverse();
   }
}


// Print segments of Euler trail as sequence of edges (e.g. a-b b-c c-a)
void Vertex::printEulerTrailEdge(ostream& os)
{
   for(int i = 0; i < edgesCount(); i++)
   {
      if (isValidNeighborAt(i))
      {
         Vertex& neighbor = neighborAt(i);
         if (isValidNextEdge(neighbor))
         {
            os << name() << "-" << neighbor.name() << "  ";
            removeEdge(neighbor);
            neighbor.removeEdge(*this);
            neighbor.printEulerTrailEdge(os);
         }
      }
   }
}



// Checks whether the edge between the given vertex and specified one is considered
// as the valid next edge for Euler trail
bool Vertex::isValidNextEdge(Vertex& neighbor)
{
   int count = 0;
   for (int i = 0; i < edgesCount(); i++)          // Counts all valid neighbors
   {
      if (isValidNeighborAt(i))
         count++;
   }
   if (count == 1)                                 // If only one valid neighbor exists - nothing more to select
      return true;
                                                   // Verifies that the edge is not a bridge
   graph->resetVertices();
   int count1 = reachableVerticesCount();

   removeEdge(neighbor);
   graph->resetVertices();
   int count2 = reachableVerticesCount();
   addEdge(neighbor.number(), 1);
   return count1 <= count2;
}



// Overridden output operator for Vertex class (used for testing).
ostream& operator <<(ostream& os, Vertex& v)
{
   os << v.name() << ":";
   for (int i = 0; i < v.edgesCount(); i++)
      os << " " << v.neighborAt(i).name();
   return os;
}
