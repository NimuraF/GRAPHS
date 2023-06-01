#include "pch.h"
#include "Graph.h"
#include "MException.h"

Graph::Graph(std::string path, int type) {
	switch (type) {
		
	case 1: {
		if (this->parseAdjencyMatrix(path)) {
			/* Вызываем функцию преобразования матрицы смежности в список рёбер и список смежности */
			this->AMtoEL();
			this->AMtoAL();
			this->AMtoALWW();
		}
		else {
			throw MException("Не удалось корректно открыть файл!");
		}
		break;
	}

	case 2: {
		if (this->parseEdgesList(path)) {
			this->ELtoAM();
			this->AMtoAL();
			this->AMtoALWW();
		}
		else {
			throw MException("Не удалось корректно открыть файл!");
		}
		break;
	}

	case 3: {
		if (this->parseAdjencyList(path)) {
			this->ALtoEL();
			this->ELtoAM();
			this->AMtoALWW();
		}
		else {
			throw MException("Не удалось корректно открыть файл!");
		}
		break;
	}

	}
}


/* ФУНКЦИИ ВОЗВРАЩАЮЩИЕ ПРЕДСТАВЛЕНИЯ ГРАФА */
std::vector < std::vector <int> > & Graph::adjencyMatrix() { //Возвращает МАТРИЦУ СМЕЖНОСТИ
	/* Создаём ссылку на вектор матрицы смежности и возвращаем его*/
	std::vector < std::vector <int> >& AM = this->AMatrix;
	return AM;
}
std::vector <Graph::EdgesListElement> & Graph::edgesList() { //Возвращет СПИСОК РЁБЕР
	/* Создаём ссылку на вектор списка рёбер и возвращаем его*/
	std::vector <EdgesListElement> & EL = this->EList;
	return EL;
}
std::vector <Graph::AdjencyListVertex> & Graph::adjencyList() { //Возвращает СПИСОК СМЕЖНОСТИ
	/* Создаём ссылку на вектор cписка смежности и возвращаем его*/
	std::vector <AdjencyListVertex>& AL = this->AList;
	return AL;
}
std::vector < std::vector <int> >& Graph::adjencyListWW() { //Возвращает СПИСОК СМЕЖНОСТИ БЕЗ ВЕСОВ
	std::vector < std::vector <int> > & ALWW = this->AListWW;
	return ALWW;
}


/* РЕАЛИЗАЦИЯ ФУНКЦИЙ СМЕНЫ ПРЕДСТАВЛЕНИЙ */
void Graph::AMtoEL() { //Смена представления МАТРИЦА СМЕЖНОСТИ -> СПИСОК РЁБЕР
	for (int i = 0; i < this->AMatrix.size(); i++) {
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				EdgesListElement row;
				row.Start = i; //Добавляем начальную точку (1 вершину)
				row.End = j; //Добавляем конечную вершину, с которой есть связь
				row.Weight = this->AMatrix[i][j]; //Добавляем в 3 колонку вес ребра между ними
				this->EList.push_back(row);
			}
		}
	}
}
void Graph::AMtoAL() { //Смена представления МАТРИЦА СМЕЖНОСТИ -> СПИСОК СМЕЖНОСТИ
	for (int i = 0; i < this->AMatrix.size(); i++) {
		AdjencyListVertex Vertex;
		Vertex.Vertex = i;
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				AdjencyListVertexPair Pair;
				Pair.Vertex = j;
				Pair.Weight = this->AMatrix[i][j];
				Vertex.VertexAndWeight.push_back(Pair);
			}
		}
		this->AList.push_back(Vertex);
	}
}
void Graph::AMtoALWW() { //Смена представления МАТРИЦА СМЕЖНОСТИ -> СПИСОК СМЕЖНОСТИ БЕЗ ВЕСОВ
	for (int i = 0; i < this->AMatrix.size(); i++) {
		std::vector <int> row;
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				row.push_back(j);
			}
		}
		this->AListWW.push_back(row);
	}
}
void Graph::ELtoAM() { //Смена представления СПИСОК РЁБЕР -> МАТРИЦА СМЕЖНОСТИ
	int VC = 0;
	for (int i = 0; i < this->EList.size(); i++) {
		if (this->EList[i].Start > VC) {
			VC = this->EList[i].Start;
		}
		if (this->EList[i].End > VC) {
			VC = this->EList[i].End;
		}
	}
	VC += 1;
	for (int i = 0; i < VC; i++) {
		std::vector < std::pair <int, int> > rows;
		for (int z = 0; z < this->EList.size(); z++) {
			if (this->EList[z].Start == i) {
				rows.push_back(std::pair <int, int>(EList[z].End, EList[z].Weight));
			}
		}
		std::vector <int> row;

		/* Сначала всё зануляем */
		for (int j = 0; j < VC; j++) {
			row.push_back(0);
		}

		for (int p = 0; p < rows.size(); p++) {
			row[rows[p].first] = rows[p].second;
		}

		AMatrix.push_back(row);
	}
}
void Graph::ALtoEL() { //Смена представления СПИСОК СМЕЖНОСТИ -> СПИСОК РЁБЕР
	for (int i = 0; i < this->AList.size(); i++) {
		for (int j = 0; j < this->AList[i].VertexAndWeight.size(); j++) {
			//Создаём структуру одной строки списка рёбер
			EdgesListElement element;
			element.Start = i;
			element.End = this->AList[i].VertexAndWeight[j].Vertex;
			element.Weight = this->AList[i].VertexAndWeight[j].Weight;
			this->EList.push_back(element);
		}
	}
}


/* ОСНОВНЫЕ ФУНКЦИИ ГРАФА */
bool Graph::isDirected() { //Функция, возвращающая true, если граф ориентированный и false - если нет
	for (int i = 0; i < this->AMatrix.size(); i++) {
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != this->AMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}
bool Graph::isEdge(int Start, int End) { //Проверка существования ребра
	if (this->AMatrix[Start][End] != 0 || this->AMatrix[End][Start] != 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Graph::isArc(int Start, int End) { //Проверяет, есть ли между вершинами дуга
	if (this->AMatrix[Start][End] != 0) {
		return true;
	}
	else {
		return false;
	}
}
int Graph::weight(int Start, int End) { //Возвращает вес ребра
	return this->AMatrix[Start][End];
}
std::vector <int> Graph::AdjVertexes(int Vertex) { //Возвращает вектор смежных вершин без весов

	std::vector <int> adjvertexes = adjencyListWW()[Vertex];

	return adjvertexes;
}


/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ПАРСИНГА */
bool Graph::parseAdjencyMatrix(std::string path) {
	std::ifstream file; //Создаём поток для чтения из файла
	file.open(path); //Открываем файл

	/* Если файл не удалось открыть, бросаем исключение */
	if (!file) {
		return false;
	}


	std::string data; //Буфер для строки
	int buffer; //Буфер для чисел
	int rows = 0; // Количество строк
	int elements = 0; //Количество элементов

	/* Сначала проходимся по строкам и считаем их кол-во, пустые строки пропускаем */
	while (!file.eof()) {
		getline(file, data);
		if (data != "") {
			rows++;
		}
	}

	/* Чистим флаги для правильного перемещения указателя */
	file.clear();

	/* Перемещаем указатель в начало файла */
	file.seekg(0L, std::ios_base::beg);

	/* Проходимся по всем элементам и считаем их количество */
	while (!file.eof()) {
		file >> buffer;
		elements++;
	}

	/* Снова сбрасываем указатель на начало, так как нам в дальнейшем может потребоваться с ним работать (в случае верных данных) */
	file.clear();
	file.seekg(0L, std::ios_base::beg);

	/*
	Проверяем матрицу на факт того, что она квадратная (матрица смежности обязана быть квадратной),
	для этого возводим кол-во строк в квадрат и сравниваем с посчитанным количеством элементов
	*/
	if (elements - 1 != rows * rows) {
		/* Закрываем соединение с файлом */
		file.close();
		return false;
	}
	else {
		/* Формируем одномерный массив всех элементов */
		int step = 0;
		int* AllElements = new int[elements - 1];

		//Записываем все элементы из файла в этот одномерный массив
		while (!file.eof()) {
			file >> AllElements[step];
			step++;
		}

		int step2 = 0;

		/* Переписываем данные из одномерного массива в двумерный */
		for (int x = 0; x < rows; x++) {
			std::vector <int> row;
			for (int y = 0; y < rows; y++) {
				row.push_back(AllElements[step2]);
				step2++;
			}
			this->AMatrix.push_back(row);
		}

		/* Закрываем соединение с файлом */
		file.close();

		/* Чистим память от одномерного массива */
		delete[] AllElements;

		return true;
	}
}
bool Graph::parseEdgesList(std::string path) {
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
			std::vector <int> elements;
			const char* cdata = data.c_str(); //Преобразуем в c-строку
			char* elem = strtok(const_cast<char*>(cdata), " "); //Разбиваем по разделителю на массив
			int i = 0;
			
			while (elem != nullptr && i < 3) { //Идём по массиву строки, разбитой по разделителю и добавляем в вектор
				elements.push_back(stoi(std::string(elem)));
				elem = strtok(nullptr, " ");
				i++;
			}

			/* Если не указан вес в 3 столбце, то задаём его по умолчанию = 1 */
			if (elements.size() < 3) {
				Graph::EdgesListElement NewEdge;
				NewEdge.Start = elements[0] - 1;
				NewEdge.End = elements[1] - 1;
				NewEdge.Weight = 1;
				this->EList.push_back(NewEdge);
			}
			else { //В ином случае берём вес из третьего столбца
				Graph::EdgesListElement NewEdge;
				NewEdge.Start = elements[0] - 1;
				NewEdge.End = elements[1] - 1;
				NewEdge.Weight = elements[2];
				this->EList.push_back(NewEdge);
			}
		}
	}
	file.close();
}
bool Graph::parseAdjencyList(std::string path) {
	std::ifstream file; //Создаём поток для чтения из файла
	file.open(path); //Открываем файл

	/* Если файл не удалось открыть, бросаем исключение */
	if (!file) {
		return false;
	}

	int rows = 0;

	std::string data; //Буфер для данных

	/* Смотрим общее количество строк*/
	while (!file.eof()) {
		getline(file, data);
		rows++;
	}

	/* Чистим флаги для правильного перемещения указателя */
	file.clear();

	/* Перемещаем указатель в начало файла */
	file.seekg(0L, std::ios_base::beg);


	int currentVertex = 0;
	int currentRow = 0;

	while (!file.eof() && currentRow < rows - 1) {
		getline(file, data);
		std::vector <AdjencyListVertexPair> adjencyVertexes; //Вектор смежных вершин
		const char* cdata = data.c_str(); //Преобразуем в c-строку
		char* elem = strtok(const_cast<char*>(cdata), " "); //Разбиваем по разделителю на массив

		while (elem != nullptr) {
			AdjencyListVertexPair Pair;
			Pair.Vertex = atoi(elem) - 1;
			Pair.Weight = 1;
			adjencyVertexes.push_back(Pair);
			elem = strtok(nullptr, " ");
		}

		AdjencyListVertex NewRow;
		NewRow.Vertex = currentVertex;
		NewRow.VertexAndWeight = adjencyVertexes;

		this->AList.push_back(NewRow);
		currentVertex++;
		currentRow++;
	}

	file.close();

}