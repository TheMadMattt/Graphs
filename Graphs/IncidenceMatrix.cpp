#include "IncidenceMatrix.h"
#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>


IncidenceMatrix::IncidenceMatrix()
{
	this->vertices = 0;
	this->edges = 0;
	this->density = 0;
	this->nextEdge = 0;
}

IncidenceMatrix::~IncidenceMatrix()
{
	directedGraph.clear();
	unDirectedGraph.clear();
	this->vertices = 0;
	this->edges = 0;
	this->density = 0;
	this->nextEdge = 0;
}

void IncidenceMatrix::createGraph(int vertices, int edges)
{
	this->vertices = vertices;
	this->edges = edges;
	this->density = 1.0*edges / (vertices*(vertices - 1));

	//graf skierowany
	directedGraph.resize(vertices + 1, vector<int>(edges,0));

	//graf nieskierowany
	unDirectedGraph.resize(vertices + 1, vector<int>(edges,0));
}

void IncidenceMatrix::createGraph(int vertices, double density)
{
	this->vertices = vertices;
	this->density = density;
	this->edges = (density * (vertices - 1) * vertices);

	//graf skierowany
	directedGraph.resize(vertices + 1, vector<int>(edges,0));

	//graf nieskierowany
	unDirectedGraph.resize(vertices + 1, vector<int>(edges,0));
}

void IncidenceMatrix::addEdge(int wp, int wk, int weight)
{
	directedGraph[vertices][nextEdge] = weight;
	unDirectedGraph[vertices][nextEdge] = weight;

	directedGraph[wp][nextEdge] = 1;
	directedGraph[wk][nextEdge] = -1;

	unDirectedGraph[wp][nextEdge] = 1;
	unDirectedGraph[wk][nextEdge] = 1;

	if (nextEdge < edges)
	{
		nextEdge++;
	}
}

void IncidenceMatrix::randomGraph()
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

void IncidenceMatrix::clearGraph()
{
	directedGraph.clear();
	unDirectedGraph.clear();
	this->vertices = 0;
	this->edges = 0;
	this->density = 0;
	this->nextEdge = 0;
}

void IncidenceMatrix::primMST()
{
	int source = 0; //pierwszy wierzcholek
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queue;

	int minWeight = 0, u;

	//vector wag, zainicjalizowany nieskonczonoscia
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

		for (int i = 0; i < edges; i++)
		{
			if (unDirectedGraph[vertex][i] != 0)
			{
				for (int j = 0; j < vertices; j++)
				{
					if (unDirectedGraph[j][i] != 0)
					{
						int weight = unDirectedGraph[vertices][i];
						if (!inMST[j] && key[j] > weight)
						{
							key[j] = weight;
							queue.push(make_pair(key[j], j));
							parent[j] = vertex;
						}
					}
				}
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

void IncidenceMatrix::dijkstraSPT(int source)
{
	priority_queue< pair<int, int>, vector <pair<int, int>>, greater<> > queue;

	//calkowity waga sciezki
	vector<int> distance(vertices, INT_MAX);

	//sciezka od wektora poczatkowego 
	vector<int> path(vertices);

	//kontener potrzebny do odtworzenia sciezki
	vector<int> prev(vertices, -1);

	//odwiedzone wierzcholki
	vector<bool> visited(vertices, false);

	queue.push(make_pair(0, source));
	distance[source] = 0;

	while (!queue.empty())
	{
		int vertex = queue.top().second;
		queue.pop();
		visited[vertex] = true;

		for (int i = 0; i < edges; i++)
		{
			if (directedGraph[vertex][i] == 1)
			{
				for (int j = 0; j < vertices; j++)
				{
					if (directedGraph[j][i] == -1)
					{
						int weight = directedGraph[vertices][i];
						if (!visited[j] && distance[j] > distance[vertex] + weight)
						{
							distance[j] = distance[vertex] + weight;
							prev[j] = vertex;
							queue.push(make_pair(distance[j], j));
						}
					}
				}
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
		if (distance[i] == INT_MAX)
		{
			cout << setw(15) << "Odleglosc: - " << endl;
		}
		else
		{
			cout << setw(15) << "Odleglosc: " << distance[i] << endl;
		}
	}
	
}

void IncidenceMatrix::printDirectedGraph()
{
	cout << "Graf skierowany" << endl << endl;
	cout << "      ";
	for (int i = 0; i < edges; i++)
	{
		cout << setw(4) << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertices; i++)
	{
		cout << setw(6) << i;
		for (int j = 0; j < edges; j++)
		{
			cout << setw(4) << directedGraph[i][j];
		}
		cout << endl;
	}
	cout << endl << "Waga: ";
	for (int i = 0; i < edges; i++)
	{
		cout << setw(4) << directedGraph[vertices][i];
	}
	cout << endl;
}

void IncidenceMatrix::printUnDirectedGraph()
{
	cout << "Graf nieskierowany" << endl << endl;
	cout << "      ";
	for (int i = 0; i < edges; i++)
	{
		cout << setw(4) << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertices; i++)
	{
		cout << setw(6) << i;
		for (int j = 0; j < edges; j++)
		{
			cout << setw(4) << unDirectedGraph[i][j];
		}
		cout << endl;
	}
	cout << endl << "Waga: ";
	for (int i = 0; i < edges; i++)
	{
		cout << setw(4) << unDirectedGraph[vertices][i];
	}
	cout << endl;
}

bool IncidenceMatrix::isConnected()
{
	int vc = 0, v, u;
	vector<bool> visited(vertices, false);

	priority_queue<int, std::vector<int>, greater<>> queue;

	queue.push(0);
	visited[0] = true;

	while (!queue.empty())
	{
		v = queue.top();
		queue.pop();
		vc++;
		for (int i = 0; i < edges; i++)
		{
			if (unDirectedGraph[v][i] != 0)
			{
				for (int j = 0; j < vertices; j++)
				{
					u = unDirectedGraph[j][i];
					if (u != 0)
					{
						if (!visited[j])
						{
							visited[j] = true;
							queue.push(j);
						}
					}
				}
			}
		}
	}

	return vc == vertices;
}

void IncidenceMatrix::readFromFile()
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

