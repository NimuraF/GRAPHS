#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task7.h"

const int INF = 10000000;

Task7::Task7(int argc, char** argv) {
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
		this->Johnson(MyGraph);
	}
}

void Task7::Johnson(Graph& MyGraph) {
	std::vector < std::vector <int> > NewGraphEdgesList;
	int newVertex = MyGraph.adjencyMatrix().size();

	/* Копируем оригинальный граф */
	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		std::vector <int> row;
		row.push_back(MyGraph.edgesList()[i].Start);
		row.push_back(MyGraph.edgesList()[i].End);
		row.push_back(MyGraph.edgesList()[i].Weight);
		NewGraphEdgesList.push_back(row);
	}

	/* Добавляем вершину, содержащую дуги во все остальные с весом 0 */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		std::vector <int> row;
		row.push_back(newVertex);
		row.push_back(i);
		row.push_back(0);
		NewGraphEdgesList.push_back(row);
	}

	/* Вызываем алгоритм Беллмана Форда */
	if (!this->BellmanFord(MyGraph, NewGraphEdgesList)) {
		throw MException("Graph contains negative cycle!");
	}

	/* Чистим сформированный граф */
	NewGraphEdgesList.clear();

	/* Пересчитываем значения весов дуг с использованием результата hFunction, чтобы избавиться от рёбер отрицательного веса */
	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		MyGraph.edgesList()[i].Weight = MyGraph.edgesList()[i].Weight + this->hFunction[MyGraph.edgesList()[i].Start] - this->hFunction[MyGraph.edgesList()[i].End];
	}

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		for (int j = 0; j < MyGraph.edgesList().size(); j++) {
			if (MyGraph.edgesList()[j].Start == i) {
				MyGraph.adjencyMatrix()[i][MyGraph.edgesList()[j].End] = MyGraph.edgesList()[j].Weight;
			}
		}
	}

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		this->Deikstra(MyGraph, i);
	}

	for (int i = 0; i < this->AllPathsPairs.size(); i++) {
		if (AllPathsPairs[i][0] != AllPathsPairs[i][1] && AllPathsPairs[i][2] < INF / 2) {
			std::cout << this->AllPathsPairs[i][0] + 1 << " - " << this->AllPathsPairs[i][1] + 1 << " : " << this->AllPathsPairs[i][2] << std::endl;
		}
	}

}

/* АЛГОРИТМ БЕЛЛМАНА-ФОРДА */
bool Task7::BellmanFord(Graph & MyGraph, std::vector < std::vector <int> > NewGraphEdgesList) {
	/* Вектор расстояний */
	std::vector <int> distances;

	/* Изначально до всех вершин расстояние бесконечно */
	for (int i = 0; i < MyGraph.adjencyMatrix().size() + 1; i++) {
		distances.push_back(INF);
	}

	/* У начальной вершины (в нашем случае добавленной со всеми рёбрами веса 0), которая идёт последней расстояние 0 */
	distances[MyGraph.adjencyMatrix().size()] = 0;

	/* Алгоритм Беллмана-Форда*/
	for (int i = 0; i < NewGraphEdgesList.size() - 1; i++) {
		for (int j = 0; j < NewGraphEdgesList.size(); j++) {
			if (distances[NewGraphEdgesList[j][0]] != INF) {
				distances[NewGraphEdgesList[j][1]] = std::min(distances[NewGraphEdgesList[j][0]] + NewGraphEdgesList[j][2], distances[NewGraphEdgesList[j][1]]);
			}
		}
	}

	/* Делаем ещё +1 итерацию для определения циклов отрицательного веса */
	for (int j = 0; j < NewGraphEdgesList.size(); j++) {
		if (distances[NewGraphEdgesList[j][0]] != INF) {
			if (distances[NewGraphEdgesList[j][1]] > distances[NewGraphEdgesList[j][0]] + NewGraphEdgesList[j][2]) {
				this->negativeCycle = true;
				break;
			}
		}
	}

	if (this->negativeCycle != true) {
		/* Пушим всё в массив путей */
		for (int i = 0; i < distances.size(); i++) {
			this->Paths.push_back(std::pair<int, int>(i, distances[i]));
		}

		/* Пишем результаты функции h в отдельный массив */
		for (int i = 0; i < distances.size(); i++) {
			this->hFunction.push_back(this->Paths[i].second);
		}
		return true;
	}
	else {
		return false;
	}
}

/* АЛГОРИТМ ДЕЙКСТРЫ */
void Task7::Deikstra(Graph& MyGraph, int startVertex) {

	/* Вектор посещённых вершин */
	std::vector <bool> visited;

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
	distances[startVertex] = 0;

	/* Максимальное кол-во проходов равное кол-ву вершин */
	int vertexC = 0;

	/* Пока в алгоритме существует хотя бы один INF и количество проходов меньше кол-ва вершин */
	while (vertexC <= MyGraph.adjencyMatrix().size()) {
		for (int i = 0; i < distances.size(); i++) {
			if (distances[i] < INF) {
				for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
					bool find_edge = false;
					for (int z = 0; z < MyGraph.edgesList().size(); z++) {
						if (MyGraph.edgesList()[z].Start == i && MyGraph.edgesList()[z].End == j) {
							find_edge = true;
						}
					}
					if (i != j && find_edge) {
						/* Смотрим путь, если предыдущий путь короче, чем полученный текущий, то оставляем его иначе - перезаписываем*/
						distances[j] = std::min(distances[j], MyGraph.adjencyMatrix()[i][j] + distances[i]);
					}
				}
			}
		}
		vertexC++;
	}


	/* Пушим всё в массив путей */
	for (int i = 0; i < distances.size(); i++) {
		std::vector <int> row;
		row.push_back(startVertex);
		row.push_back(i);
		row.push_back(distances[i] - this->hFunction[startVertex] + this->hFunction[i]);
		this->AllPathsPairs.push_back(row);
	}

}

/* Переопределение ключей*/
void Task7::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* Парсинг флагов */
bool Task7::parseFlags(int argc, char** argv) {
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