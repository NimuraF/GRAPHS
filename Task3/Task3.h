#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task3 : public Task
{
private:
	std::vector <bool> visited; //Вектор посещённых вершин
	std::vector <int> timeIn; //Вектор для хранения такта входа в вершину
	std::vector <int> fUp; //Вектор для хранения такта входа из текущей вершину в вершину, которая уже была использована

	int timer = 0; //Глобальное количество тактов
	int currentRoot; //Текущий корень

	std::vector < std::pair<int, int> > Bridges; //Вектор мостов
	std::vector <int> CutVertices; //Вектор шарниров (точек сочленения)

public:
	/* Технические параметры таска*/
	Task3(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void DFSB(Graph&, int startVertex, int predok = -1); //Поиск в глубину для мостов
	void DFSP(Graph&, int startVertex, int predok = -1); //Поиск в глубину для точек сочленения (шарниров)

	void ClearContainers(Graph&); //Установка стартовых параметров для контейнеров

	void getBridges(Graph&); //Определение всех мостов
	void getCutVertices(Graph&); //Определение всех шарниров
};

