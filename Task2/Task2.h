#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task2 : public Task
{
private:
	std::vector < std::vector <int> > ConnectionComponents; //Вектор для сохранения компонент связности
	std::vector <bool> visited; //Вектор посещённых вершин

public:
	/* Технические параметры таска*/
	Task2(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void BFS(Graph&, int); //Алгоритм поиска в ширину
	void AllComponents(Graph&); 
};

