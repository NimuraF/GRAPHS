#pragma once
class CMap {

private:

	/* КАРТА в виде двумерного массива (матрицы) */
	std::vector < std::vector <int> > MAP;



	bool parseMap(std::string); //Парсим карту

public:
	CMap(std::string);

	/* Возврат карты (матрицы смежности) по ссылке */
	std::vector < std::vector <int> >& getMap(); 

	/* Индекстатор, возвращающий высоту вершину в точке */
	int Indexator(int, int);

	/* Функция, возвращающая список всех соседних клеток */
	std::vector < std::pair <int, int > > neighbors(std::pair <int, int>);
};

