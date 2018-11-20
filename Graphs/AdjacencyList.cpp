#include "AdjacencyList.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>


AdjacencyList::AdjacencyList()
{
	this->vertices = 0;
	this->density = 0;
	this->edges = 0;
}


AdjacencyList::~AdjacencyList()
{
	directedGraph.clear();
	unDirectedGraph.clear();
	this->vertices = 0;
	this->edges = 0;
	this->density = 0;
}

void AdjacencyList::createGraph(int vertices, int edges)
{
	this->vertices = vertices;
	this->edges = edges;
	this->density = 1.0*edges / (vertices*(vertices - 1));

	directedGraph.resize(vertices, list<pair<int,int>>(0));
	unDirectedGraph.resize(vertices, list<pair<int,int>>(0));
}

void AdjacencyList::createGraph(int vertices, double density)
{
	this->vertices = vertices;
	this->density = density;
	this->edges = (density * (vertices - 1) * vertices);

	directedGraph.resize(vertices, list<pair<int,int>>(0));
	unDirectedGraph.resize(vertices, list<pair<int,int>>(0));
}

void AdjacencyList::addEdge(int wp, int wk, int weight)
{
	directedGraph[wp].push_back(make_pair(wk, weight));

	unDirectedGraph[wp].push_back(make_pair(wk, weight));
	unDirectedGraph[wk].push_back(make_pair(wp, weight));
}

void AdjacencyList::randomGraph()
{
	int prev = 0, j = 0, next, weight;
	std::vector<int> visited;

	visited.push_back(prev);

	for (int i = 0; i < vertices - 1; i++)
	{
		next = rand() % (vertices);
		while (j < visited.size())
		{
			if (next == visited[j])
			{
				next = (next + 1) % vertices;
				j = 0;
			}
			else
				j++;
		}
		j = 0;
		weight = rand() % 99 + 1;
		addEdge(prev, next, weight);
		prev = next;
		visited.push_back(prev);
	}

	for (int i = vertices - 1; i < edges; i++)
	{
		prev = rand() % vertices;
		next = rand() % vertices;
		while (prev == next)
		{
			next = rand() % vertices;
		}
		weight = rand() % 99 + 1;
		addEdge(prev, next, weight);
	}
}

void AdjacencyList::clearGraph()
{
	directedGraph.clear();
	unDirectedGraph.clear();
	this->vertices = 0;
	this->edges = 0;
	this->density = 0;
}

void AdjacencyList::primMST()
{
	int source = 0; //pierwszy wierzcholek
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queue;

	int minWeight = 0;

	//vector kluczy, zainicjalizowany nieskonczonoscia
	vector<int> key(vertices, INT_MAX);

	//MST
	vector<int> parent(vertices, -1);

	//sciezka wierzcholkow MST
	vector<bool> inMST(vertices, false);

	queue.push(make_pair(0, source));
	key[source] = 0;

	while (!queue.empty())
	{
		int vertex = queue.top().second;
		queue.pop();

		inMST[vertex] = true;

		for (auto it = unDirectedGraph[vertex].begin(); it != unDirectedGraph[vertex].end(); ++it)
		{
			int v = it->first;
			int weight = it->second;

			if (!inMST[v] && key[v] > weight)
			{
				key[v] = weight;
				queue.push(make_pair(key[v], v));
				parent[v] = vertex;
			}
		}
	}
	
	for (int i = 1; i < vertices; i++)
	{
		cout << parent[i] << " - " << i << endl;
		minWeight += key[i];
	}
	cout << "Minimalna waga: " << minWeight << endl;
	
}

void AdjacencyList::dijkstraSPT(int source)
{
	priority_queue< pair<int, int>, vector <pair<int, int>>, greater<> > queue;

	vector<int> distance(vertices, INT_MAX);
	vector<int> path(vertices);
	vector<int> prev(vertices, -1);
	vector<bool> visited(vertices, false);


	queue.push(make_pair(0, source));
	distance[source] = 0;

	while (!queue.empty())
	{
		int vertex = queue.top().second;
		queue.pop();
		visited[vertex] = true;

		for (auto it = directedGraph[vertex].begin(); it != directedGraph[vertex].end(); ++it)
		{
			int v = it->first;
			int weight = it->second;

			if (!visited[v] && distance[v] > distance[vertex] + weight)
			{
				distance[v] = distance[vertex] + weight;
				prev[v] = vertex;
				queue.push(make_pair(distance[v], v));
			}
		}
	}
	
	int iterator = 0;
	for (int i = 0; i < vertices; i++)
	{
		cout << i << ": ";
		for (int j = i; j > -1; j = prev[j])
		{
			path[iterator++] = j;
		}

		while (iterator)
		{
			cout << path[--iterator] << " ";
		}
		if(distance[i] == INT_MAX)
		{
			cout << setw(15) << "Odleglosc: - " << endl;
		}
		else 
		{
			cout << setw(15) << "Odleglosc: " << distance[i] << endl;
		}
	}
	
}

void AdjacencyList::printDirectedGraph()
{
	cout << "Graf skierowany" << endl << endl;

	for (int i = 0; i < directedGraph.size(); i++)
	{
		cout << i;
		auto it = directedGraph[i].begin();
		while (it != directedGraph[i].end()) {
			cout << " -> " << it->first << ":" << it->second;
			++it;
		}
		cout << endl;
	}
}

void AdjacencyList::printUnDirectedGraph()
{
	cout << "Graf nieskierowany" << endl << endl;

	for (int i = 0; i < unDirectedGraph.size(); ++i) {

		int adjNodes = unDirectedGraph[i].size();
		cout << i;

		if (adjNodes > 0) {
			auto it = unDirectedGraph[i].begin();
			while (it != unDirectedGraph[i].end()) {
				cout << " -> " << (*it).first << ":" << (*it).second;
				++it;
			}
		}
		else {
			cout << "BRAK";
		}

		cout << endl;
	}
}

void AdjacencyList::readFromFile()
{
	ifstream file;
	file.open("graph.txt", ios::in);

	clearGraph();

	if (file.good()) {
		file >> edges >> vertices;
		createGraph(vertices, edges);
		while (!file.eof())
		{
			int wp, wk, weight;
			file >> wp >> wk >> weight;
			addEdge(wp, wk, weight);
		}

		cout << "Dane zostaly wczytane prawidlowo " << endl;

	}
	else
	{
		cout << "Nie udalo sie otworzyc pliku" << endl;
	}

	file.close();
}

int AdjacencyList::getVertices()
{
	return vertices;
}

int AdjacencyList::getEdges()
{
	return edges;
}

float AdjacencyList::getDensity()
{
	return density * 100;
}
