#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task7 : public Task {

private:

	bool negativeCycle = false; //Флаг для наличия отрицательного цикла

	std::vector < std::pair <int, int> > Paths; // Вектор путей для Беллмана Форда

	std::vector < std::vector <int> > AllPathsPairs; //Вектор путей между всеми парами вершин

	std::vector <int> hFunction; //Значения функции h(Vertex)

public:
	/* Технические параметры таска*/
	Task7(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;


	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void Johnson(Graph&); //Алгоритм Джонсона
	bool BellmanFord(Graph&, std::vector < std::vector <int> >); //Алгоритм Беллмана-Форда
	void Deikstra(Graph&, int); //Алгоритм Дейкстры
};

