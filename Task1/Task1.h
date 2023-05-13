#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task1 : public Task
{
private:
	const int INF = 10000;

	std::vector < std::vector <int> > SDM; //Матрица кратчайших расстояний
	std::vector <int> Eccentrycities; //Вектор эксцентриситетов
	std::vector <int> Peripheral; //Вектор периферийных вершин
	std::vector <int> CentralVertexes; //Вектор центральных вершин
	int Rad; //Радиус
	int Diametr; //Диаметр

public:
	/* Технические параметры таска*/
	Task1(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* ВЗАИМОДЕЙСТВИЕ С ГРАФОМ */
	void ShortestDistanceMatrix(Graph&); //Матрица кратчайших расстояний
	void VertexDegrees(Graph&); //Вектор степеней вершин
	void Diameter(Graph&); //Диаметр графа
	void REPC(Graph& MyGraph); //Эксцентриситеты, радиус и перефирийные вершины
};

