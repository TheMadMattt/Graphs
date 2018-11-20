#pragma once
#include <list>
#include <vector>

using namespace std;


class AdjacencyList
{
private:
	vector<list<pair<int,int>>> directedGraph;
	vector<list<pair<int,int>>> unDirectedGraph;
	int vertices;
	float density;
	int edges;
public:
	AdjacencyList();
	~AdjacencyList();
	void createGraph(int vertices, int edges);
	void createGraph(int vertices, double density);
	void addEdge(int wp, int wk, int weight);
	void randomGraph();
	void clearGraph();
	void primMST();
	void dijkstraSPT(int source);
	void printDirectedGraph();
	void printUnDirectedGraph();
	void readFromFile();
	int getVertices();
	int getEdges();
	float getDensity();
};

