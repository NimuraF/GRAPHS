#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task2 : public Task
{
private:
	std::vector < std::vector <int> > ConnectionComponents; //Вектор для сохранения компонент связности
	std::vector <bool> visited; //Вектор посещённых вершин

	std::vector < std::vector <int> > AJListWWInvert; //Инвертированный граф в виде списка смежности без весов

	std::vector <char> used;
	std::vector <int> order; //Список вершин в порядке убывания
	std::vector <int> component; //Буфер для текущей компоненты СИЛЬНОЙ связности

	std::vector < std::vector <int> > StrongConnectionComponents; //Вектор для хранения компонент сильной связности

public:
	/* Технические параметры таска*/
	Task2(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void FindConnectionComponents(Graph&, int); //Алгоритм поиска в ширину
	void AllComponents(Graph&); //Функция, для определения всех компонент
	void dfs1(std::vector < std::vector <int> > &, int); //Алгоритм поиска в глубину
	void dfs2(std::vector < std::vector <int> > &, int); //Алгоритм поиска в глубину инвертированного графа
	void FindStrongComponents(Graph&);
};

