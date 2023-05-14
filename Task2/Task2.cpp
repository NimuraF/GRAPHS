#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task2.h"

Task2::Task2(int argc, char** argv) {
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
		AllComponents(MyGraph);
	}
}




/* ЗАДАЧИ ТАСКА НЕПОСРЕДСТВЕННОЙ РАБОТЫ С ГРАФАМИ */
void Task2::BFS(Graph& MyGraph, int startV) {
	if(!MyGraph.isDirected()) { //Если граф неориентированный

		std::queue <int> relatedVertexes; //Очередь смежных вершин
		std::vector <bool> currentVisited; //Вершины, посещённые от текущей
		for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
			currentVisited.push_back(false);
		}

		relatedVertexes.push(startV); //Забрасываем первую вершину
		currentVisited[startV] = true; //Устанавливаем текущую вершину как посещённую
		this->visited[startV] = true; //Устанавливаем текущую вершину как посещённую

		int currentVertex = startV;

		while (!relatedVertexes.empty()) {
			currentVertex = relatedVertexes.front();
			relatedVertexes.pop();
			for (int z = 0; z < MyGraph.adjencyList()[currentVertex].VertexAndWeight.size(); z++) {
				if (this->visited[MyGraph.adjencyList()[currentVertex].VertexAndWeight[z].Vertex] != true) {
					this->visited[MyGraph.adjencyList()[currentVertex].VertexAndWeight[z].Vertex] = true;
					currentVisited[MyGraph.adjencyList()[currentVertex].VertexAndWeight[z].Vertex] = true;
					relatedVertexes.push(MyGraph.adjencyList()[currentVertex].VertexAndWeight[z].Vertex);
				}
			}
		}

		std::vector <int> currentComponent;

		for (int p = 0; p < currentVisited.size(); p++) {
			if (currentVisited[p] == true) {
				currentComponent.push_back(p);
			}
		}

		this->ConnectionComponents.push_back(currentComponent);
	}
}
void Task2::AllComponents(Graph& MyGraph) {
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		this->visited.push_back(false);
	}
	
	for (int i = 0; i < this->visited.size(); i++) {
		if (this->visited[i] == false) {
			this->BFS(MyGraph, i);
		}
	}

	if (this->ConnectionComponents.size() > 1) {
		std::cout << "Graph is not connected and contains " << this->ConnectionComponents.size() << " components." << std::endl;
		std::cout << "Connected components:" << std::endl;
	}
	else {
		std::cout << "Graph is connected" << std::endl;
		std::cout << "Connected components:" << std::endl;
	}

	std::cout << "[";
	for (int i = 0; i < this->ConnectionComponents.size(); i++) {
		std::cout << "[ ";
		for (int z = 0; z < this->ConnectionComponents[i].size(); z++) {
			std::cout << this->ConnectionComponents[i][z] + 1 << " ";
		}
		std::cout << "]";
	}
	std::cout << "]";
}


/* Переопределение ключей*/
void Task2::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* Парсинг флагов */
bool Task2::parseFlags(int argc, char** argv) {
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