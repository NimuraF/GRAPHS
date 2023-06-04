#include "pch.h"
#include "CMap.h"
#include "MException.h"

CMap::CMap(std::string path) {
	if (!this->parseMap(path)) {
		throw MException("Не удалось распарсить матрицу!");
	}
}


/* Возврат карты (матрицы смежности) по ссылке */
std::vector < std::vector <int> > & CMap::getMap() {
	std::vector < std::vector <int> >& Map = this->MAP;
	return Map;
}

/* Индекстатор, возвращающий высоту вершину в точке */
int CMap::Indexator(int i, int j) {
	return this->MAP[i][j];
}

/* Функция, возвращающая вектор всех соседей к полученной клетке */
std::vector < std::pair <int, int > > CMap::neighbors(std::pair <int, int> vertex) {
	std::vector < std::pair <int, int > > neighbors;

	/* Проверяем правого соседа */
	if (vertex.second != this->MAP[vertex.first].size() - 1) {
		std::pair <int, int> RightNeighbor;
		RightNeighbor.first = vertex.first;
		RightNeighbor.second = vertex.second + 1;
		neighbors.push_back(RightNeighbor);
	}

	/* Проверяем левого соседа */
	if (vertex.second != 0) {
		std::pair <int, int> LeftNeighbor;
		LeftNeighbor.first = vertex.first;
		LeftNeighbor.second = vertex.second - 1;
		neighbors.push_back(LeftNeighbor);
	}

	/* Проверяем верхнего соседа */
	if (vertex.first != 0) {
		std::pair <int, int> TopNeighbor;
		TopNeighbor.first = vertex.first - 1;
		TopNeighbor.second = vertex.second;
		neighbors.push_back(TopNeighbor);
	}

	/* Проверяем нижднего соседа */
	if (vertex.first != this->MAP.size() - 1) {
		std::pair <int, int> BotNeighbor;
		BotNeighbor.first = vertex.first + 1;
		BotNeighbor.second = vertex.second;
		neighbors.push_back(BotNeighbor);
	}

	return neighbors;
}

/* ПАРСИНГ КАРТЫ */
bool CMap::parseMap(std::string path) {
	std::ifstream file; //Создаём поток для чтения из файла
	file.open(path); //Открываем файл

	/* Если файл не удалось открыть, бросаем исключение */
	if (!file) {
		return false;
	}

	std::string data; //Буфер для строки

	while (!file.eof()) {
		getline(file, data);
		if (data != "") {
			std::vector <int> row;
			const char* cdata = data.c_str(); //Преобразуем в c-строку
			char* elem = strtok(const_cast<char*>(cdata), " "); //Разбиваем по разделителю на массив

			while (elem != nullptr) { //Идём по массиву строки, разбитой по разделителю и добавляем в вектор
				row.push_back(stoi(std::string(elem)));
				elem = strtok(nullptr, " ");
			}

			this->MAP.push_back(row);
		}
	}

	file.close();
}