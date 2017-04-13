/***************************************************************************************************
CUNY - College of Staten Island
Spring 2016
Course: CSC 228 Discrete Mathematical Structures for Computer Science

Assignment: Given an adjacency matrix that codes for a graph, write a program that determines
			if there is an Eulerian circuit, an Eulerian path, or neither.  
			If a circuit or a path exists, state the path.

Professor: Susan Imberman
Student: Maria Romanova
***************************************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include "Graph.h"
#include <iomanip>
using namespace std;

void displayHeader();

void main()
{
	displayHeader();

   string fileName;
   string answer;
   while (true)
   {
      cout << "\n   Please enter the name of adjacency matrix file without filename extension: ";
		cin >> fileName;
      string path = "data/" + fileName + ".txt";

      ifstream matrixFile;
      matrixFile.open(path);
      if(!matrixFile)
      {
         cout << "   Cannot find file " << path << endl;
      }
      else
      {
         cout << "   You selected file: " << path << endl << endl;
         Graph graph(matrixFile);
         cout << graph;
         matrixFile.close();
      }

      cout << "\n\n   Do you want to process another file (y/n)? ";
		cin >> answer;
      if (answer != "Y" && answer != "y")
         break;
   }
}



void displayHeader()
{
	cout << endl << setfill('*') << setw(90) << "*" << "\n\n";
	cout << "   Given an adjacency matrix for undirected graph this program determines if there is:\n"
		<< "\t- Eulerian circuit,\n\t- an Eulerian path,\n\t- or neither.\n\n"
		<< "   If a circuit or a path exists, the program will display it.\n\n";
	cout << "   Note: The adjacency matrix file should be in the folder \\data, format 'txt' \n\n";
	cout << setfill('*') << setw(90) << "*" << "\n\n\n";
}