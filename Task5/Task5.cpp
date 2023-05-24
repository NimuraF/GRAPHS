#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task5.h"

const int INF = 100000;

Task5::Task5(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("Не удалось разобрать флаги!");
	}
	else {
		/* ОЧИЩАЕМ ФАЙЛ ДЛЯ ЗАПИСИ ЕСЛИ ОН ЕСТЬ */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
			output.close();
		}

		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		this->Deikstra(MyGraph);
	}
}


/* АЛГОРИТМ ДЕЙКСТРЫ */
void Task5::Deikstra(Graph& MyGraph) {

	/* Вектор посещённых вершин */
	std::vector <bool> visited;

	int minindex = 0;
	int min = 0;
	/* Вектор расстояний */
	std::vector <int> distances;

	/* Изначально все вершины не посещены*/
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		visited.push_back(false);
	}

	/* Изначально до всех вершин расстояние бесконечно */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		distances.push_back(INF);
	}

	/* У начальной вершины расстояние 0 */
	distances[this->StartVertex] = 0;

	/* Максималтьное кол-во проходов равное кол-ву вершин */
	int vertexC = 0;

	/* Пока в алгоритме существует хотя бы один INF и количество проход меньше кол-ва вершин */
	while (std::count(distances.begin(), distances.end(), INF) > 0 && vertexC <= MyGraph.adjencyMatrix().size()) {
		for (int i = 0; i < distances.size(); i++) {
			if (distances[i] != INF) {
				int min = INF;
				int minV = -1;
				for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
					if (i != j && MyGraph.adjencyMatrix()[i][j] != 0) {
						/* Смотрим путь, если предыдущий путь короче, чем полученный текущий, то оставляем его иначе - перезаписываем*/
						distances[j] = std::min(distances[j], MyGraph.adjencyMatrix()[i][j] + distances[i]);
						if (MyGraph.adjencyMatrix()[i][j] < min) {
							min = MyGraph.adjencyMatrix()[i][j];
							minV = j;
						}
					}
				}
				visited[i] = true;
			}
		}
		vertexC++;
	}

	if (distances[this->EndVertex] == INF) {
		if (!this->getOutputFlag()) {
			std::cout << "There is no path between the vertices " << this->StartVertex << " and " << this->EndVertex << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			output << "There is no path between the vertices " << this->StartVertex << " and " << this->EndVertex << std::endl;
			output.close();
		}
	}
	else {
		if (!this->getOutputFlag()) {
			std::cout << "Shortest path length between " << this->StartVertex + 1 << " and " << this->EndVertex + 1 << ": " << distances[this->EndVertex] << std::endl;
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			output << "Shortest path length between " << this->StartVertex << " and " << this->EndVertex << ": " << distances[this->EndVertex] << std::endl;
			output.close();
		}
		int currentEndVertex = this->EndVertex;
		while (currentEndVertex != this->StartVertex) {
			for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
				if (distances[currentEndVertex] - MyGraph.adjencyMatrix()[i][currentEndVertex] == distances[i] && MyGraph.adjencyMatrix()[i][currentEndVertex] != 0) {
					this->path.push_back(std::pair <int, std::pair <int, int> >(i, std::pair<int, int>(currentEndVertex, MyGraph.adjencyMatrix()[i][currentEndVertex])));
					currentEndVertex = i;
				}
			}
		}

		std::reverse(this->path.begin(), this->path.end());

		if (!this->getOutputFlag()) {
			std::cout << "Path:" << std::endl << "[";
			for (int i = 0; i < this->path.size(); i++) {
				std::cout << "(" << this->path[i].first + 1 << " - " << this->path[i].second.first + 1 << " : " << this->path[i].second.second << ")";
			}
			std::cout << "]";
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			output << "Path:" << std::endl << "[";
			for (int i = 0; i < this->path.size(); i++) {
				output << "(" << this->path[i].first + 1 << " - " << this->path[i].second.first + 1 << " : " << this->path[i].second.second << ")";
			}
			output << "]";
			output.close();
		}
	}


}

/* Переопределение ключей*/
void Task5::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-n", "Start vertex"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-d", "End vertex"));
}

/* Парсинг флагов */
bool Task5::parseFlags(int argc, char** argv) {
	if (argc >= 4) {
		int mainFlagsC = 0;
		bool BeginFlag = false;
		bool EndFlag = false;
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
				else if (strcmp(argv[i], "-n") == 0) {
					this->StartVertex = std::atoi(argv[i + 1]);
					BeginFlag = true;
				}
				else if (strcmp(argv[i], "-d") == 0) {
					this->EndVertex = std::atoi(argv[i + 1]);
					EndFlag = true;
				}
			}

			if (strcmp(argv[i], "-h") == 0) {
				this->Help();
				return false;
			}
		}

		if (mainFlagsC != 1 || this->currentPath == "" || !BeginFlag || !EndFlag) {
			return false;
		}

		return true;
	}
	else {
		return false;
	}
}