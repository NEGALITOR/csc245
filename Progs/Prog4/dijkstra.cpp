#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <climits>

#include "queue.h"
#include "graph.h"
#include "HashTable.h"

using namespace std;

struct VertexType
{
	string name;
	string prev;
	int dist;
	bool marked;
};

void buildGraph(Graph<string>& dijGraph, VertexType verts[], string cities[], string file, int& numVerts, int& numEdges);
void dijkstra(Graph<string>& dijGraph, VertexType verts[], string cities[], int numVerts);
bool checkArray(string cities[], string city, int numVerts);
bool checkMarked(VertexType verts[], int numVerts);
int getCityIndex(string city, VertexType verts[], int numVerts);
void menu(string cities[], int numVerts);
void printR(VertexType verts[], int loc);

//Main
int main(int argc, char* argv[])
{
	if (argc == 1 || argc > 2)
	{
		cout << "The command line inputs were not correct.\nPlease try again." << endl;
		exit(0);

	}
	string file = argv[1];

	Graph<string> dijGraph(50);
	VertexType verts[50];
	string cities[50];
	int numVerts = 0, numEdges = 0;


	buildGraph(dijGraph, verts, cities, file, numVerts, numEdges);
	menu(cities, numVerts);
	dijkstra(dijGraph, verts, cities, numVerts);

}

//Builds the graph from the file by utilizing a delimeter of ; to sift through the data
void buildGraph(Graph<string>& dijGraph, VertexType verts[], string cities[], string file, int& numVerts, int& numEdges)
{
	VertexType vertOne, vertTwo;
	string cityOne, cityTwo, line, nCityOne, nCityTwo;
	int weight;

	ifstream inFile;
	inFile.open(file.c_str());

	if (!inFile)
	{
		cout << "The command line inputs were not correct.\nPlease try again." << endl;
		exit(0);
	}

	while (inFile.peek() != EOF)
	{
		getline(inFile, cityOne, ';');

		if (checkArray(cities, cityOne, numVerts) == false)
		{
			dijGraph.AddVertex(cityOne);
			cities[numVerts] = cityOne;
			nCityOne = cities[numVerts];

			vertOne.name = nCityOne;
			vertOne.dist = INT_MAX;
			vertOne.marked = false;

			verts[numVerts] = vertOne;
			numVerts++;

		}

		getline(inFile, cityTwo, ';');

		if (checkArray(cities, cityTwo, numVerts) == false)
		{
			dijGraph.AddVertex(cityTwo);
			cities[numVerts] = cityTwo;
			nCityTwo = cities[numVerts];

			vertTwo.name = nCityTwo;
			vertTwo.dist = INT_MAX;
			vertTwo.marked = false;

			verts[numVerts] = vertTwo;
			numVerts++;

		}
		getline(inFile, line);
		weight = atoi(line.c_str());
		dijGraph.AddEdge(cityOne, cityTwo, weight);
		numEdges++;

	}



}

//Performs Dijkstras to evaluate the data by utilizing a queue
void dijkstra(Graph<string>& dijGraph, VertexType verts[], string cities[], int numVerts)
{
	Queue <string> q;
	string startVert;
	int startI = 0, prevI = 0, adjI = 0, totalDist = 0, minI = 0, min = 0;

	cout << "Please input your starting vertex: ";
	getline(cin, startVert);

	while (checkArray(cities, startVert, numVerts) == false)
	{
		cout << "Starting location does not exist..." << endl;
		cout << "Please input your starting vertex: ";

		getline(cin, startVert);

	}

	cout << "\n-----------------------------------------------------------------------\n" << endl;
	cout << setw(14) << "Vertex" << setw(18) << "Distance" << setw(16) << "Previous\n" << endl;

	startI = getCityIndex(startVert, verts, numVerts);
	verts[startI].marked = true;
	verts[startI].dist = 0;
	verts[startI].prev = "N/A";

	printR(verts, startI);

	prevI = startI;

	while (checkMarked(verts, numVerts) == false)
	{
		dijGraph.GetToVertices(verts[prevI].name, q);
		while (!(q.isEmpty()))
		{
			string name = q.getFront();

			adjI = getCityIndex(name, verts, numVerts);
			totalDist = verts[prevI].dist + dijGraph.WeightIs(verts[prevI].name, verts[adjI].name);

			if (verts[adjI].marked == false && totalDist < verts[adjI].dist)
			{
				verts[adjI].dist = totalDist;
				verts[adjI].prev = verts[prevI].name;

			}
			q.dequeue();

		}

		min = INT_MAX;

		for (int i = 0; i < numVerts; i++)
		{
			VertexType distance = verts[i];
			if (distance.dist <= min && !distance.marked)
			{
				min = distance.dist;
				minI = i;

			}

		}
		prevI = minI;
		verts[prevI].marked = true;
		printR(verts, prevI);

	}

	cout << "\n-----------------------------------------------------------------------\n" << endl;

}

//Checks cities array if the city already exists
bool checkArray(string cities[], string city, int numVerts)
{
	bool found = false;

	for (int i = 0; i < numVerts; i++)
	{
		if (cities[i] == city)
			found = true;

	}
	return found;

}

//Checks the VertexType to see if city has already been marked
bool checkMarked(VertexType verts[], int numVerts)
{
	bool mark = true;

	for (int i = 0; i < numVerts; i++)
	{
		if (verts[i].marked == false)
			mark = false;

	}
	return mark;

}

//Gets the city location in the VertexType
int getCityIndex(string city, VertexType verts[], int numVerts)
{
	int index;

	for (int i = 0; i < numVerts; i++)
	{
		if (verts[i].name == city)
			index = i;

	}
	return index;

}

//Initializes the GUI
void menu(string cities[], int numVerts)
{
	int count = 0;
	cout << endl;
	cout << "^^^^^^^^^^^^^^^^	DIJKSTRA'S ALGORITHM	^^^^^^^^^^^^^^^^ " << endl;
	cout << "\nA Weighted Graph Has Been Built For These " << numVerts << " Vertices: " << endl;
	cout << endl;

	string temp = cities[0];

	for (int i = 1; i < numVerts; i++)
	{
		temp = cities[i];
		int j = 0;

		for (j = i; j > 0; j--)
			if (temp < cities[j - 1])
				cities[j] = cities[j - 1];
			else break;
		cities[j] = temp;

	}

	for (int i = 0; i <= numVerts; i++)
	{
		cout << setw(18) << cities[i];
		count++;

		if (count == 3)
		{
			cout << endl;
			count = 0;

		}

	}
	cout << "\n\n";

}

//Prints the table based on distance not being INT_Max and above -1
void printR(VertexType verts[], int loc)
{

	if (verts[loc].dist != INT_MAX && verts[loc].dist >= 0)
		cout << setw(14) << verts[loc].name << setw(18) << verts[loc].dist << setw(16) << verts[loc].prev << endl;
	else
		cout << setw(14) << verts[loc].name << setw(18) << "Not On Path" << setw(16) << "N/A" << endl;

}


