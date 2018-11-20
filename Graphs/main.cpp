#include <iostream>
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include "Menu.h"
#include <ctime>
#include "TimeMeasure.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Menu menu;

	menu.ChooseOptionMenu();

	system("pause");
	return 0;
}
