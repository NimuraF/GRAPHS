#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"

class Task6 : public Task {
private:

	int StartVertex = 0; //Стартовая вершина

	bool isNegativeEdges = false; //Флаг, отвечающий за присутствие в графе рёбер с отрицательным весом

	int currentAlgorithm = 0; //1 - Алгоритм Дейкстры, алгоритм Беллмана-Форда, алгоритм Левита

	bool negativeCycle = false; //Флаг для наличия отрицательного цикла

	std::vector < std::pair <int, int> > Paths; // Вектор путей


public:
	/* Технические параметры таска*/
	Task6(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void showPaths();
	void clearContainers();

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void chooseAlg(Graph&); //Функция выбора алгоритма
	void checkNegativeEdges(Graph&); //Функция проверки рёбер с отрицательным весом
	void Deikstra(Graph&); //Алгоритм Дейкстры
	bool BellmanFord(Graph&); //Алгоритм Беллмана-Форда
	void Levit(Graph&); //Алгоритм Левита
};

