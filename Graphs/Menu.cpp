#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::ChooseOptionMenu()
{
	string temp;
	cout << "[1] Wylosuj graf" << endl;
	cout << "[2] Wczytaj graf z pliku" << endl;
	cout << "[3] Wyjscie" << endl;
	cout << "Wybierz zadanie do uruchomienia: ";
	cin >> temp;

	option = atoi(temp.c_str()); //konwersja ze stringa na int

	switch (option)
	{
	case 1:
		system("cls");
		RandomGraphMenu();
		break;
	case 2:
		system("cls");
		ReadGraphFromFile();
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Wpisz odpowiedni numer." << endl;
		system("pause");
		system("cls");
		ChooseOptionMenu();
	}
}

void Menu::RandomGraphMenu()
{
	int vertices = 0, density = 0;

	matrix.clearGraph();
	list.clearGraph();

	while (vertices <= 1)
	{
		cout << "Podaj ilosc wierzcholkow: ";
		cin >> vertices;
	}

	int maxK = vertices * (vertices - 1);
	double minG = ceil((((double)vertices - 1) * 100) / (double)maxK);

	while (density < minG || density > 100)
	{
		cout << "Podaj gestosc conajmniej - " << minG << "%: "; cin >> density;
	}

	matrix.createGraph(vertices, (density / 100.0));
	list.createGraph(vertices, (density / 100.0));

	this->vertices = list.getVertices();
	this->edges = list.getEdges();
	this->denisty = list.getDensity();

	RandomGraph();

	if (matrix.isConnected())
	{
		system("cls");
		cout << "Wylosowany graf jest spojny" << endl;
		system("pause");
		system("cls");
		MainMenu();
	}
	else
	{
		system("cls");
		cout << "Wylosowany graf jest niespojny!" << endl;
		system("pause");
		system("cls");
		matrix.clearGraph();
		list.clearGraph();
		ChooseOptionMenu();
	}
}

void Menu::ReadGraphFromFile()
{
	matrix.readFromFile();
	list.readFromFile();

	this->vertices = list.getVertices();
	this->edges = list.getEdges();
	this->denisty = list.getDensity();

	if (matrix.isConnected())
	{
		system("cls");
		cout << "Graf z pliku jest spojny" << endl;
		system("pause");
		system("cls");
		MainMenu();
	}
	else
	{
		system("cls");
		cout << "Graf z pliku nie jest spojny!" << endl;
		system("pause");
		system("cls");
		ChooseOptionMenu();
	}
}

void Menu::MainMenu()
{
	string temp;
	cout << "Wierzcholki: " << vertices << endl;
	cout << "Krawedzie: " << edges << endl;
	cout << "Gestosc: " << denisty << "%" << endl << endl;
	cout << "[1] Wyswietl macierz incydencji" << endl;
	cout << "[2] Wyswietl liste sasiedztwa" << endl;
	cout << "[3] Prim - macierz incydencji" << endl;
	cout << "[4] Prim - lista sasiedztwa" << endl;
	cout << "[5] Dijkstra - macierz incydencji" << endl;
	cout << "[6] Dijkstra - lista sasiedztwa" << endl;
	cout << "[7] Powrot do tworzenia grafu" << endl;
	cout << "[8] Wyjscie" << endl;
	cout << "Wybierz zadanie do uruchomienia: ";
	cin >> temp;

	option = atoi(temp.c_str()); //konwersja ze stringa na int

	switch (option)
	{
	case 1:
		system("cls");
		matrix.printDirectedGraph();
		cout << endl;
		matrix.printUnDirectedGraph();
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 2:
		system("cls");
		list.printDirectedGraph();
		cout << endl;
		list.printUnDirectedGraph();
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 3:
		system("cls");
		matrix.printUnDirectedGraph();
		cout << endl;
		matrix.primMST();
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 4:
		system("cls");
		list.printUnDirectedGraph();
		cout << endl;
		list.primMST();
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 5:
		system("cls");
		matrix.printDirectedGraph();
		cout << endl;
		matrix.dijkstraSPT(chooseVertice());
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 6:
		system("cls");
		list.printDirectedGraph();
		cout << endl;
		list.dijkstraSPT(chooseVertice());
		system("pause");
		system("cls");
		MainMenu();
		break;
	case 7:
		system("cls");
		ChooseOptionMenu();
		break;
	case 8:
		exit(0);
		break;
	default:
		cout << "Wpisz odpowiedni numer." << endl;
		system("pause");
		system("cls");
		MainMenu();
	}
}

void Menu::RandomGraph()
{
	int prev = 0, j = 0, next, weight;
	std::vector<int> visited;

	visited.push_back(prev);
	
	for (int i = 0; i < vertices-1; i++)
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
		weight = rand() % 100;
		matrix.addEdge(prev, next, weight);
		list.addEdge(prev, next, weight);
		prev = next;
		visited.push_back(prev);
	}

	for (int i = vertices-1; i < edges; i++)
	{
		prev = rand() % vertices;
		next = rand() % vertices;
		while (prev == next)
		{
			next = rand() % vertices;
		}
		weight = rand() % 100;
		matrix.addEdge(prev, next, weight);
		list.addEdge(prev, next, weight);
	}
}

int Menu::chooseVertice()
{
	int source;
	cout << "Z ktorego wierzcholka szukac najkrotszych sciezek? Wierzcholki: " << 0 << " - " << (vertices-1) << " ";
	cin >> source;
	while(true)
	{
		if(source >= 0 && source <= vertices-1)
		{
			break;
		}
		cout << "Podaj prawidlowy numer wierzcholka! Wierzcholki: " << 0 << " - " << (vertices-1) << " ";
		cin >> source;
	}

	return source;
}
