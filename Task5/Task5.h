#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"

class Task5 : public Task {
private:
	int StartVertex = 0; //Начальная вершина
	int EndVertex = 1; //Конечная вершина

	std::vector < std::pair <int, std::pair <int, int> > > path; //Восстановленный путь
public:
	/* Технические параметры таска*/
	Task5(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;



	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void Deikstra(Graph&); //Алгоритм Дейкстры
};

