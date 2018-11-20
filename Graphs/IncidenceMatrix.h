#pragma once
#include <vector>

using namespace std;

class IncidenceMatrix
{
private: 
	vector<vector<int>> directedGraph;
	vector<vector<int>> unDirectedGraph;
	int vertices;
	int edges;
	double density;
	int nextEdge;
public:
	IncidenceMatrix();
	~IncidenceMatrix();
	void createGraph(int vertices, int edges);
	void createGraph(int vertices, double density);
	void addEdge(int wp, int wk, int weight);
	void randomGraph();
	void clearGraph();
	void primMST();
	void dijkstraSPT(int source);
	void printDirectedGraph();
	void printUnDirectedGraph();
	bool isConnected();
	void readFromFile();
};

