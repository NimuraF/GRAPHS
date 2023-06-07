#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task10 : public Task {
private:
	int maxFlow = 0; //Максимальный поток

	int source = 3; //Источник
	int stock = 27; //Сток

	std::vector < std::pair < /* Ребро */ std::pair <int, int>, /* Текущий | Максимальный поток */ std::pair <int, int> > > path; //Пути с одинаковыми рёбрами и разными потоками

public:
	/* Технические параметры таска*/
	Task10(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&); //Функция для вывода в файл / на экран

	/* МЕТОДЫ РАБОТЫ С ГРАФОМ */
	void FordFalkerson(Graph&); //Алгоритм Фолд-Фалкерсона
	bool BFS(Graph&, int, int); //Алгортм BFS, мордифицированный для Форда-Фалкерсона
	void StockSource(Graph&); //Алгоритм для определения Стока и истока
	void sumFlows(); //Функция для суммирования потоков по одному ребру
};

