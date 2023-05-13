#pragma once
class Graph 
{
private:

	/* Структура для одного элемента списка рёбер */
	struct EdgesListElement {
		int Start;
		int End;
		int Weight;
	};

	/* Две структуры для списка смежности */
	struct AdjencyListVertexPair { //Структура смежных вершин
		int Vertex;
		int Weight;
	};
	struct AdjencyListVertex { //Структура для хранения вершины и вектора смежных с ней вершин
		int Vertex;
		std::vector <AdjencyListVertexPair> VertexAndWeight;
	};

	std::vector <std::vector<int> > AMatrix; //Матрица смежности
	std::vector <EdgesListElement> EList; //Список рёбер
	std::vector <AdjencyListVertex> AList; //Список смежности


	void ALtoAM(); //Метод для преобразования списка смежности в матрицу
	void ELtoAM(); //Метод для преобразования списка ребёр в матрицу смежности
	void AMtoEL(); //Метод для преобразования матрицы смежности в список рёбер
	void AMtoAL(); //Метод для преобразования матрицы смежности в список смежности

	bool parseAdjencyMatrix(std::string path);
	bool parseEdgesList(std::string path);

public:

	Graph(std::string, int); //Конструктор класса

	/* Функция, возвращающая вес ребра */
	int weight(int, int);

	/* Функция, определяющая, есть ли ребро */
	bool isEdge(int, int);

	/* Функция, определяющая, есть ли дуга */
	bool isArc(int, int);

	/* Функция, определяющая, ориентированный граф или нет */
	bool isDirected();

	/* Функция, возвращающая список всех инцидентных вершин */
	

	/* ФУНКЦИИ ПРЕДСТАВЛЕНИЯ И ВОЗВРАТА ЗНАЧЕНИЙ */
	std::vector < std::vector <int> > & adjencyMatrix(); //Вернуть ссылку на матрицу смежности
	std::vector <EdgesListElement> & edgesList(); //Вернуть список смежности
	std::vector <AdjencyListVertex> & adjencyList();
};

