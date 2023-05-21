#pragma once

#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"

class Task4 : public Task
{
private:

	int currentAlgorithm = 0; //1 - алгоритм Крускала, 2 - Алгоритм Прима, 3 - Алгоритм Борукви, 4 - Все алгроритмы + время

	std::vector < std::pair </* Номер строки в списке рёбер*/int, /* Вес ребра */int> > allWeights; //Список рёбер

	std::vector < std::pair<int, int> > SpanningTree; //Остовное древеро в виде списка рёбер //
	int SumEdgeWeight = 0; //Суммарный вес дерева

	unsigned int TimerKruskala = 0;
	unsigned int TimerPrima = 0;
	unsigned int TimerBoruvki = 0;

public:
	/* Технические параметры таска*/
	Task4(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void clearContainers(); //Очистка контейнеров таска
	void showSpanningTreeAndWeight(); //Вывод остовного дерева на экран/файл

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void FindSpanningTree(Graph&); //Вычисление остовного дерева и веса
	void createUndirectedGrah(Graph&); //Создаём соотнесённый граф (граф, где заменены дуги рёбрами)

	void Kruskal(Graph&); //Алгоритм крускала
	void Prima(Graph&); //Алгоритм Прима
	void Boruvki(Graph&); //Алгоритм Борувки
};

