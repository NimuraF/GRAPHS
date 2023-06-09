#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task11.h"



Task11::Task11(int argc, char** argv) {
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

		this->maxPairs(MyGraph);
	}
}

/* Функция для определения маиксмаильных паросочетаний */
void Task11::maxPairs(Graph& MyGraph) {

	/* Проверяем граф на ориентированность */
	if (!MyGraph.isDirected()) {

		/* Сначала все точки не окрашены */
		for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
			this->colors.push_back(0);
		}


		/* Если граф несвяззный, то сущесвует несколько способов покраски */
		for (int i = 0; i < this->colors.size(); i++) {
			if (colors[i] == 0) {
				if (!this->checkBiparate(MyGraph, i, 1)) {
					this->biparate = false;
					break;
				}
				else {
					this->biparate = true;
				}
			}
		}

		/* Копируем все рёбра в список рёбер без весов */
		this->copyAllEdges(MyGraph);

		/* Создаём источник для множества R и сток для множества B */
		for (int i = 0; i < this->colors.size(); i++) {
			if (this->colors[i] == 1) {
				this->edges.push_back(std::make_pair(MyGraph.adjencyMatrix().size(), i));
			}
			else {
				this->edges.push_back(std::make_pair(i, MyGraph.adjencyMatrix().size() + 1));
			}
		}

		std::ofstream mfile;
		mfile.open("myfile.txt");
		for (int i = 0; i < MyGraph.adjencyMatrix().size() + 2; i++) {
			for (int j = 0; j < this->edges.size(); j++) {
				if (this->edges[j].first == i) {
					mfile << this->edges[j].second + 1 << " ";
				}
			}
			mfile << std::endl;
		}

		Graph NGraph("myfile.txt", 3);

		for (int i = 0; i < NGraph.adjencyMatrix().size(); i++) {
			for (int j = 0; j < NGraph.adjencyMatrix().size(); j++) {
				std::cout << NGraph.adjencyMatrix()[i][j] << " ";
			}
			std::cout << std::endl;
		}

		//for (int i = 0; i < this->colors.size(); i++) {
		//	if (this->colors[i] == 1) {
		//		std::cout << "R" << " ";
		//	}
		//	else if (this->colors[i] == 2) {
		//		std::cout << "B" << " ";
		//	}
		//}

		//std::cout << std::endl;

		//for (int i = 0; i < this->edges.size(); i++) {
		//	std::cout << this->edges[i].first << " - " << this->edges[i].second << std::endl;
		//}


	}

}

/* Копируем все рёбра в список рёбер без весов */
void Task11::copyAllEdges(Graph& MyGraph) {
	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		this->edges.push_back(std::make_pair(MyGraph.edgesList()[i].Start, MyGraph.edgesList()[i].End));
	}
}

/* ПРОВЕРКА ГРАФА НА ДВУДОЛЬНОСТЬ */
bool Task11::checkBiparate(Graph& MyGraph, int currentVertex, int currentColor) {
	
	/* Проверяем через DFS */

	/* Красим текущую вершину в заданный цвет */
	this->colors[currentVertex] = currentColor;

	/* Проверяем через DFS */
	for (int i = 0; i < MyGraph.adjencyListWW()[currentVertex].size(); i++) {
		int neighbor = MyGraph.adjencyListWW()[currentVertex][i];
		int neighborColor = currentColor == 1 ? 2 : 1;
		if (colors[neighbor] == 0) {
			this->checkBiparate(MyGraph, neighbor, neighborColor);
		}
		else if (colors[neighbor] == currentColor) {
			return false;
		}
	}

	return true;
	
}

/* Переопределение ключей*/
void Task11::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* Парсинг флагов */
bool Task11::parseFlags(int argc, char** argv) {
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