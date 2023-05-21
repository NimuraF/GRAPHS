#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task4.h"

Task4::Task4 (int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("Не удалось разобрать флаги!");
	}
	else {
		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		this->FindSpanningTree(MyGraph);
		this->showSpanningTreeAndWeight();
	}
}

void Task4::FindSpanningTree(Graph& MyGraph) {
	switch (this->currentAlgorithm) {

	case 1: {
		this->Kruskal(MyGraph);
		break;
	}

	case 2: {
		this->Prima(MyGraph);
		break;
	}

	case 3: {
		this->Boruvki(MyGraph);
		break;
	}

	case 4: {
		/* Время для алгоритма Крускала*/
		unsigned int start = clock();
		this->Kruskal(MyGraph);
		unsigned int end = clock();
		this->TimerKruskala = end - start;

		/* Время для алгоритма Прима */
		start = clock();
		this->Prima(MyGraph);
		end = clock();
		this->TimerPrima = end - start;

		start = clock();
		this->Boruvki(MyGraph);
		end = clock();
		this->TimerBoruvki = end - start;
		break;
	}

	}
}

/* АЛГОРИТМ КРУСКАЛА*/
void Task4::Kruskal(Graph& MyGraph) {
	
	/* Очищаем контейнеры */
	this->clearContainers();

	/* Создаём вектор вершин, в котором каждлая вершина является остовным деревом */
	std::vector <int> connections;

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		connections.push_back(i);
	}

	/* Заполняем массив номеров строк в списке рёбер и их весов */
	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		std::pair<int, int> row;
		row.first = i;
		row.second = MyGraph.edgesList()[i].Weight;
		this->allWeights.push_back(row);
	}

	/* Сортируем по уменьшению веса*/
	std::sort(allWeights.begin(), allWeights.end(), 
		[](std::pair <int, int> a, std::pair <int, int> b) {
			return a.second < b.second;
		});

	/* Алгоритм Крускала */
	for (int i = 0; i < this->allWeights.size(); i++) {
		int begin_v = MyGraph.edgesList()[this->allWeights[i].first].Start;
		int end_v = MyGraph.edgesList()[this->allWeights[i].first].End;
		int currentWeight = allWeights[i].second;
		if (connections[begin_v] != connections[end_v]) {
			this->SumEdgeWeight += currentWeight;
			this->SpanningTree.push_back(std::pair<int, int>(begin_v, end_v));
			int old_id = connections[end_v];
			int new_id = connections[begin_v];
			for (int j = 0; j < connections.size(); j++) {
				if (connections[j] == old_id) {
					connections[j] = new_id;
				}
			}
		}
	}
}

/* АЛГОРИТМ ПРИМА*/
void Task4::Prima(Graph& MyGraph) {
	
	/* Создаём соотнесённый граф */
	if (MyGraph.isDirected()) {
		this->createUndirectedGrah(MyGraph);
	}

	/* Очищаем контейнеры */
	this->clearContainers();

	std::vector <bool> used;

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		used.push_back(false);
	}
	
	used[0] = true;

	/* Алгоритм Крускала */
	while (std::count(used.begin(), used.end(), false)) {
		int min = 1000000;
		int endVertex = -1;
		int startVertex = -1;
		for (int i = 0; i < used.size(); i++) {
			if (used[i] == false) {
				for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
					if (MyGraph.adjencyMatrix()[i][j] != 0 && used[j] == true && MyGraph.adjencyMatrix()[i][j] < min) {
						min = MyGraph.adjencyMatrix()[i][j];
						endVertex = i;
						startVertex = j;
					}
				}
			}
		}
		this->SpanningTree.push_back(std::pair <int, int>(endVertex, startVertex));
		this->SumEdgeWeight += min;
		used[endVertex] = true;
	}


}

/* АЛГОРИТМ БОРУВКИ*/
void Task4::Boruvki(Graph& MyGraph) {
	
	this->clearContainers();

	/* Создаём соотнесённый граф */
	if (MyGraph.isDirected()) {
		this->createUndirectedGrah(MyGraph);
	}

	std::vector < std::vector <int> > trees;

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		std::vector <int> currentTree;
		currentTree.push_back(i);
		trees.push_back(currentTree);
	}

	

	while (trees.size() > 1) {
		for (int i = 0; i < trees.size(); i++) { //Компонента, которую берём для сравнения
			int min = 10000000;
			int ConnectionVertex = -1;
			int startVertex = -1;
			int componentNumber = -1;
			for (int j = 0; j < trees[i].size(); j++) { //Вершина внутри компоненты
				for (int z = 0; z < trees.size(); z++) { //Компонента, с которой сравниваем
					if (i != z) {
						for (int v = 0; v < trees[z].size(); v++) { //Список вершин внутри компоненты, с которой сравниваем
							if (MyGraph.adjencyMatrix()[trees[i][j]][trees[z][v]] != 0 && MyGraph.adjencyMatrix()[trees[i][j]][trees[z][v]] < min && trees[i][j] != trees[z][v]) {
								min = MyGraph.adjencyMatrix()[trees[i][j]][trees[z][v]];
								ConnectionVertex = trees[z][v];
								startVertex = trees[i][j];
								componentNumber = z;
							}
						}
					}
				}
			}
			if (min != 10000000 && ConnectionVertex != -1 && componentNumber != -1) {
				this->SpanningTree.push_back(std::pair <int, int>(startVertex, ConnectionVertex));
				for (int p = 0; p < trees[componentNumber].size(); p++) {
					trees[i].push_back(trees[componentNumber][p]);
				}
				this->SumEdgeWeight += min;
				trees[componentNumber].clear();
				trees.erase(trees.begin() + componentNumber);
				std::vector< std::vector <int> >(trees).swap(trees);
			}
		}
	}
}

/* Создание неориентированного (соотнесённого графа) из орграфа*/
void Task4::createUndirectedGrah(Graph& MyGraph) {
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
			if (MyGraph.adjencyMatrix()[i][j] != MyGraph.adjencyMatrix()[j][i] && i != j) {
				if (MyGraph.adjencyMatrix()[i][j] == 0) {
					MyGraph.adjencyMatrix()[i][j] = MyGraph.adjencyMatrix()[j][i];
				}
				else {
					MyGraph.adjencyMatrix()[j][i] = MyGraph.adjencyMatrix()[i][j];
				}
			}
		}
	}
}

/* Очистка контейнеров*/
void Task4::clearContainers() {
	this->SumEdgeWeight = 0;
	this->SpanningTree.clear();
	this->allWeights.clear();
}

/* Функция для вывода на экран или в файл */
void Task4::showSpanningTreeAndWeight() {
	if (!this->getOutputFlag()) {
		std::cout << "Minimum spanning tree:" << std::endl;
		std::cout << "[";
		for (int i = 0; i < this->SpanningTree.size(); i++) {
			std::cout << "(" << this->SpanningTree[i].first + 1 << ", " << this->SpanningTree[i].second + 1 << ")";
		}
		std::cout << "]" << std::endl;
		std::cout << "Weight of spanning tree: " << this->SumEdgeWeight << std::endl;
		if (this->currentAlgorithm == 4) {
			std::cout << "TimerKruskala = " << this->TimerKruskala << "(ms)" << std::endl;
			std::cout << "TimerPrima = " << this->TimerPrima << "(ms)" << std::endl;
			std::cout << "TimerBoruvki = " << this->TimerBoruvki << "(ms)" << std::endl;
		}
	}
	else {
		std::ofstream output;
		output.open(this->getCurrentOutputPath());
		if (output.is_open()) {
			output << "Minimum spanning tree:" << std::endl;
			output << "[";
			for (int i = 0; i < this->SpanningTree.size(); i++) {
				output << "(" << this->SpanningTree[i].first + 1 << ", " << this->SpanningTree[i].second + 1 << ")";
			}
			output << "]" << std::endl;
			output << "Weight of spanning tree: " << this->SumEdgeWeight << std::endl;
			if (this->currentAlgorithm == 4) {
				output << "TimerKruskala = " << this->TimerKruskala << "(ms)" << std::endl;
				output << "TimerPrima = " << this->TimerPrima << "(ms)" << std::endl;
				output << "TimerBoruvki = " << this->TimerBoruvki << "(ms)" << std::endl;
			}
			output.close();
		}
		else {
			throw MException("Упс, не удалось открыть файл!");
		}
	}
}

/* Переопределение ключей*/
void Task4::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-k", "Kruskal algorithm"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-p", "Prima algorithm"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-b", "Borukvi algorithm"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-s", "All algorithms (+time)"));
}

/* Парсинг флагов */
bool Task4::parseFlags(int argc, char** argv) {
	if (argc >= 4) {
		int mainFlagsC = 0;
		int algFlagsC = 0;
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

			if (strcmp(argv[i], "-k") == 0 && this->currentAlgorithm != 1) {
				this->currentAlgorithm = 1;
				algFlagsC++;
			}
			else if (strcmp(argv[i], "-p") == 0 && this->currentAlgorithm != 2) {
				this->currentAlgorithm = 2;
				algFlagsC++;
			}
			else if (strcmp(argv[i], "-b") == 0 && this->currentAlgorithm != 3) {
				this->currentAlgorithm = 3;
				algFlagsC++;
			}
			else if (strcmp(argv[i], "-s") == 0 && this->currentAlgorithm != 4) {
				this->currentAlgorithm = 4;
				algFlagsC++;
			}



			if (strcmp(argv[i], "-h") == 0) {
				this->Help();
				return false;
			}
		}

		if (mainFlagsC != 1 || this->currentPath == "" || algFlagsC != 1) {
			return false;
		}

		return true;
	}
	else {
		return false;
	}
}