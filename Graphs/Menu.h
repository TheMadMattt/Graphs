#pragma once
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"


class Menu
{
private:
	int option;
	IncidenceMatrix matrix;
	AdjacencyList list;
	int vertices, edges, denisty;
public:
	Menu();
	~Menu();
	void ChooseOptionMenu();
	void RandomGraphMenu();
	void ReadGraphFromFile();
	void MainMenu();
	void RandomGraph();
	int chooseVertice();
};

