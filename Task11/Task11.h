#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task11 : public Task {
private:

	std::vector <int> colors; //Цвета для определения двудольности 0 - не окрашена, 1 - красный, 2 - черный

	std::vector < std::pair <int, int> > edges; //Список рёбер без весов (вес всех рёбер = 1)

	bool biparate; //Булевский флаг, отвчеающий за двудольность

public:
	/* Технические параметры таска*/
	Task11(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&); //Функция для вывода в файл / на экран

	/* МЕТОДЫ РАБОТЫ С ГРАФОМ */
	bool checkBiparate(Graph&, int, int); //Функция проверки графа на двудольность
	void maxPairs(Graph&); //Функция для определения маиксмаильных паросочетаний
	void copyAllEdges(Graph&); //Функция, копирующая все рёбра в список рёбер без весов (вес всех рёбер = 1)
};

