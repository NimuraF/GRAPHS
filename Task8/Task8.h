#pragma once
#include "../NativeClasses/CMap.h"
#include "../NativeClasses/Task.h"

class Task8 : public Task {

	struct Cell {
		int i;
		int j;
	};

	std::pair <int, int> beginCell; //Начальная вершина (в виде строки | столбца) в матрице смежности
	std::pair <int, int> endCell; //Конечная вершина (в виде строки | столбца) в матрице смежности

	double visistedPercent; //Процент посещённых клеток

public:
	/* Технические параметры таска*/
	Task8(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&, std::vector < std::pair <int, int> > &, int, std::string); //Функция для вывода в файл / на экран

	/* ФУНКЦИИ РАБОТЫ С КАРТОЙ */
	void findPath(CMap&, int); //Поиск пути
	int getRange(CMap&, std::pair <int, int>, std::pair <int, int>); //Вычисление и возврат расстояния между вершинами


	/* ЭВРИСТИКИ */
	int hManhatton(std::pair <int, int>, std::pair <int, int>); //Манхэттонское расстояние
	int hChebyshev(std::pair <int, int>, std::pair <int, int>); //Чебышева расстояние
	int hEvklid(std::pair <int, int>, std::pair <int, int>); //Евклидово расстояние
};

