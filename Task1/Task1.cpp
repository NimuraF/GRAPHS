#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task1.h"

Task1::Task1(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("Не удалось разобрать флаги!");
	}
	else {
		
		/* ПРОВЕРЯЕМ ФАЙЛ ДЛЯ ЗАПИСИ ЕСЛИ ОН ЕСТЬ */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
		}

		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		this->VertexDegrees(MyGraph);
		this->ShortestDistanceMatrix(MyGraph);
		this->Diameter(MyGraph);
		this->REPC(MyGraph);
	}
}


/* ЗАДАЧИ ТАСКА НЕПОСРЕДСТВЕННОЙ РАБОТЫ С ГРАФАМИ */
void Task1::ShortestDistanceMatrix(Graph& MyGraph) { //Матрица кратчайших расстояний
	/* Создаём двумерный вектор для матрицы кратчайших расстояний из матрицы смежности оригинального графа*/
	std::vector < std::vector <int> > shortestDistanceMatrix = MyGraph.adjencyMatrix();

	/* Преобразуем матрицу в корректную для обработки */
	for (int i = 0; i < shortestDistanceMatrix.size(); i++) {
		for (int j = 0; j < shortestDistanceMatrix.size(); j++) {
			if (shortestDistanceMatrix[i][j] == 0 && i != j) { //Если ребро не в себя и = 0, то заменяем на INF
				shortestDistanceMatrix[i][j] = INF;
			}
		}
	}

	/* Алгоритм Флойда-Уоршелла */
	for (int k = 0; k < shortestDistanceMatrix.size(); k++) {
		for (int i = 0; i < shortestDistanceMatrix.size(); i++) {
			for (int j = 0; j < shortestDistanceMatrix.size(); j++) {
				shortestDistanceMatrix[i][j] = std::min(shortestDistanceMatrix[i][j], shortestDistanceMatrix[i][k] + shortestDistanceMatrix[k][j]);
			}
		}
	}

	if (!this->outputFlag) {
		std::cout << "Distancies:" << std::endl;
		for (int x = 0; x < shortestDistanceMatrix.size(); x++) {
			std::cout << "[ ";
			for (int y = 0; y < shortestDistanceMatrix.size(); y++) {
				if (shortestDistanceMatrix[x][y] != INF) {
					std::cout << parseOut::CountSpaces(shortestDistanceMatrix[x][y]) << shortestDistanceMatrix[x][y] << " ";
				}
				else {
					std::cout << "INF ";
				}
			}
			std::cout << "]" << std::endl;
		}
	}
	else {
		std::ofstream output;
		output.open(this->getCurrentOutputPath(), std::ios::app);
		if (output.is_open()) {
			output << "Distancies:" << std::endl;
			for (int x = 0; x < shortestDistanceMatrix.size(); x++) {
				output << "[ ";
				for (int y = 0; y < shortestDistanceMatrix.size(); y++) {
					if (shortestDistanceMatrix[x][y] != INF) {
						output << parseOut::CountSpaces(shortestDistanceMatrix[x][y]) << shortestDistanceMatrix[x][y] << " ";
					}
					else {
						output << "INF ";
					}
				}
				output << "]" << std::endl;
			}
		}
		else {
			throw MException("Не удалось открыть файл для записи!");
		}
		output.close();
	}

	/* Записываем матрицу кратчайших расстояний для последующей помощи в расчётах*/
	this->SDM = shortestDistanceMatrix;
}
void Task1::VertexDegrees(Graph& MyGraph) { //Вектор степеней вершин
	int Z = 0;
	int mSize = MyGraph.adjencyMatrix().size();

	if (!MyGraph.isDirected()) { //Если граф неориентированный
		std::vector <int> VERTEX_DEGREES; /* Вектор вершин для неориентированного */
		for (int i = 0; i < mSize; i++) {
			Z = 0;
			for (int j = 0; j < mSize; j++) {
				if (MyGraph.adjencyMatrix()[i][j] != 0) {
					Z++;
				}
			}
			VERTEX_DEGREES.push_back(Z);
		}

		if (!this->getOutputFlag()) {
			std::cout << "DEG = [ ";
			for (int i = 0; i < VERTEX_DEGREES.size(); i++) {
				std::cout << VERTEX_DEGREES[i] << " ";
			}
			std::cout << "]" << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				output << "DEG = [ ";
				for (int i = 0; i < VERTEX_DEGREES.size(); i++) {
					output << VERTEX_DEGREES[i] << " ";
				}
				output << "]" << std::endl;
			}
		}
	}
	else { //Если граф ориентированный

		std::vector <int> VERTEX_DEGREES_PLUS; /* Вектор вершин для ориентированного (+) */
		std::vector <int> VERTEX_DEGREES_MINUS; /* Вектор вершин для ориентированного (-) */

		/* Считаем - */
		for (int i = 0; i < mSize; i++) {
			Z = 0;
			for (int j = 0; j < mSize; j++) {
				if (MyGraph.isArc(i, j)) {
					Z++;
				}
			}
			VERTEX_DEGREES_MINUS.push_back(Z);
		}

		/* Считаем + */
		int V = 0;
		for (int i = 0; i < mSize; i++) {
			V = 0;
			for (int j = 0; j < mSize; j++) {
				if (MyGraph.isArc(j, i)) {
					V++;
				}
			}
			VERTEX_DEGREES_PLUS.push_back(V);
		}

		if (!this->outputFlag) {
			/* Выводим для плюса (+) */
			std::cout << "deg+ = [ ";
			for (int i = 0; i < VERTEX_DEGREES_PLUS.size(); i++) {
				std::cout << VERTEX_DEGREES_PLUS[i] << " ";
			}
			std::cout << "]" << std::endl;

			/* Выводим для минуса (-) */
			std::cout << "deg- = [ ";
			for (int i = 0; i < VERTEX_DEGREES_MINUS.size(); i++) {
				std::cout << VERTEX_DEGREES_MINUS[i] << " ";
			}
			std::cout << "]" << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				/* Выводим для плюса (+) */
				output << "deg+ = [ ";
				for (int i = 0; i < VERTEX_DEGREES_PLUS.size(); i++) {
					output << VERTEX_DEGREES_PLUS[i] << " ";
				}
				output << "]" << std::endl;

				/* Выводим для минуса (-) */
				output << "deg- = [ ";
				for (int i = 0; i < VERTEX_DEGREES_MINUS.size(); i++) {
					output << VERTEX_DEGREES_MINUS[i] << " ";
				}
				output << "]" << std::endl;
				output.close();
			}
			else {
				throw MException("Не удалось открыть файл для записи!");
			}
		}
	}

}
void Task1::Diameter(Graph& MyGraph) {
	int diameter = this->SDM[0][0];
	for (int i = 0; i < this->SDM.size(); i++) {
		for (int j = 0; j < this->SDM.size(); j++) {
			if (this->SDM[i][j] > diameter) {
				diameter = this->SDM[i][j];
			}
		}
	}
	this->Diametr = diameter;
}
void Task1::REPC(Graph& MyGraph) {

	/* СЧИТАЕМ ЭКСЦЕНТРИСТЕТЫ, РАДИУС И ПЕРИФЕРИЙНЫЕ ВЕРШИНЫ */
	int radius = INF + 10;
	bool infEccentricity = false;
	for (int i = 0; i < this->SDM.size(); i++) {
		int max = 0;
		for (int j = 0; j < this->SDM.size(); j++) {
			if (this->SDM[i][j] > max) {
				max = this->SDM[i][j];
			}
		}
		if (max == INF) {
			infEccentricity = true;
		}
		this->Eccentrycities.push_back(max);
		if (max == this->Diametr) {
			this->Peripheral.push_back(i);
		}
		if (max < radius) {
			radius = max;
		}
	}
	this->Rad = radius;

	/* ОПРЕДЕЛЯЕМ МНОЖЕСТВО ЦЕНТРАЛЬНЫХ ВЕРШИН */
	for (int i = 0; i < Eccentrycities.size(); i++) {
		if (Eccentrycities[i] == this->Rad) {
			this->CentralVertexes.push_back(i);
		}
	}



	/* ВЫВОДИМ ЭКСЦЕНСТРИСИТЕТЫ */
	if (infEccentricity == false) {
		if (!this->getOutputFlag()) {
			std::cout << "Eccentricity:" << std::endl << "[ ";
			for (int i = 0; i < Eccentrycities.size(); i++) {
				std::cout << Eccentrycities[i] << " ";
			}
			std::cout << "]" << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				output << "Eccentricity:" << std::endl << "[ ";
				for (int i = 0; i < Eccentrycities.size(); i++) {
					output << Eccentrycities[i] << " ";
				}
				output << "]" << std::endl;
			}
			else {
				throw MException("Не удалось открыть файл для записи!");
			}
		}
	}

	/* ВЫВОДИМ ДИАМЕТР */
	if (this->Diametr != INF) {
		if (!this->getOutputFlag()) {
			std::cout << "D = " << this->Diametr << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				output << "D = " << this->Diametr << std::endl;
			}
			else {
				throw MException("Не удаётся открыть файл для записи!");
			}
		}
	}


	/* ВЫВОДИМ РАДИУС, МНОЖЕСТВО ПЕРЕФИРИЙНЫХ И ЦЕНТРАЛЬНЫХ ВЕРШИН */
	if (infEccentricity == false) {
		if (!this->getOutputFlag()) {
			//Радиус
			std::cout << "R = " << this->Rad << std::endl;

			//Центральные
			std::cout << "Z = " << "[ ";
			for (int i = 0; i < this->CentralVertexes.size(); i++) {
				std::cout << this->CentralVertexes[i] << " ";
			}
			std::cout << "]" << std::endl;

			//Перефирийные
			std::cout << "P = " << "[ ";
			for (int i = 0; i < this->Peripheral.size(); i++) {
				std::cout << this->Peripheral[i] << " ";
			}
			std::cout << "]" << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				output << "R = " << this->Rad << std::endl;

				//Центральные
				output << "Z = " << "[ ";
				for (int i = 0; i < this->CentralVertexes.size(); i++) {
					output << this->CentralVertexes[i] << " ";
				}
				output << "]" << std::endl;

				//Перефирийные
				output << "P = " << "[ ";
				for (int i = 0; i < this->Peripheral.size(); i++) {
					output << this->Peripheral[i] << " ";
				}
				output << "]" << std::endl;
			}
			else {
				throw MException("Не удалось открыть файл для записи!");
			}
		}
	}
	
	
}

/* Переопределение ключей*/
void Task1::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* Парсинг флагов */
bool Task1::parseFlags(int argc, char** argv) {
	if (argc >= 2) {
		int mainFlagsC = 0;
		for (int i = 1; i < argc; i++) {
			if (i != argc - 1) {
				if (strcmp(argv[i], "-m") == 0 && this->currentFormat != 1) {
					this->currentFormat = 1;
					this->currentPath = argv[i + 1];
					mainFlagsC++;
				}
				else if (strcmp(argv[i], "-e") == 0 && this->currentFormat != 2) {
					this->currentFormat = 2;
					this->currentPath = argv[i + 1];
					mainFlagsC++;
				}
				else if (strcmp(argv[i], "-l") == 0 && this->currentFormat != 3) {
					this->currentFormat = 3;
					this->currentPath = argv[i + 1];
					mainFlagsC++;
				}
				else if (strcmp(argv[i], "-o") == 0 && this->outputFlag != true) {
					this->outputFlag = true;
					this->currentOutputPath = argv[i + 1];
				}
			}

			if (strcmp(argv[i], "-h") == 0) {
				this->Help();
				return false;
			}
		}

		if (mainFlagsC != 1 || this->currentPath == "") {
			return false;
		}

		return true;
	}
	else {
		return false;
	}
}