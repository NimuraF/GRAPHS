#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task10.h"

const int INF = 1000000;

Task10::Task10(int argc, char** argv) {
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

		this->FordFalkerson(MyGraph);
	}
}

/* АЛГОРИТМ ОПРЕДЕЛЕНИЯ СТОКА И ИСТОЧНИКА */
void Task10::StockSource(Graph & MyGraph) {
	/* Определяем источник и сток */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		int sourceOutputCounter = 0;
		int sourceInputCounter = 0;
		for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
			if (i != j && MyGraph.adjencyMatrix()[j][i] != 0) {
				sourceInputCounter++;
			}
			if (i != j && MyGraph.adjencyMatrix()[i][j] != 0) {
				sourceOutputCounter++;
			}
		}
		if (sourceOutputCounter != 0 && sourceInputCounter == 0) {
			this->source = i;
		}
		if (sourceInputCounter != 0 && sourceOutputCounter == 0) {
			this->stock = i;
		}
	}
}

/* АЛГОРИТМ ФОРДА-ФАЛКЕРСОНА */
void Task10::FordFalkerson(Graph& MyGraph) {

	/* Определяем сток и источник */
	this->StockSource(MyGraph);
	
	/* Выполянем модифицированный BFS пока есть хотя бы один путь */
	while (this->BFS(MyGraph, this->source, this->stock)) {

	}
	
	/* Сортируем все полученные потоки по рёбрам */
	std::sort(this->path.begin(), this->path.end());

	/* Суммируем все потоки на ребре */
	this->sumFlows();

	/* Добавляем рёбра с 0 потоком */
	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		bool find_status = false;
		std::pair <int, int> edge;
		edge.first = MyGraph.edgesList()[i].Start;
		edge.second = MyGraph.edgesList()[i].End;
		for (int j = 0; j < this->path.size(); j++) {
			if (this->path[j].first == edge) {
				find_status = true;
			}
		}
		if (!find_status) {
			this->path.push_back(std::make_pair(edge, std::pair <int, int>(0, MyGraph.edgesList()[i].Weight)));
		}
	}

	/* Ещё раз сортируем все рёбра и потоки для красивого вывода */
	std::sort(this->path.begin(), this->path.end());

	/* Выводим инфу */
	if (!this->getOutputFlag()) {
		this->logOutput(std::cout);
	}
	else {
		std::ofstream file;
		file.open(this->getCurrentOutputPath());
		this->logOutput(file);
		file.close();
	}
}

/* ФУНКЦИЯ ВЫВОДА */
void Task10::logOutput(std::ostream & streamOut) {
	streamOut << this->maxFlow << " - maximum flow from " << this->source + 1 << " to " << this->stock + 1 << std::endl;
	for (int i = 0; i < this->path.size(); i++) {
		streamOut << path[i].first.first + 1 << " - " << path[i].first.second + 1 << " : " << path[i].second.first << "/" << path[i].second.second << std::endl;
	}
}

/* Суммируем все потоки на ребре */
void Task10::sumFlows() {
	for (int i = 0; i < this->path.size(); i++) {
		for (int j = 0; j < this->path.size(); j++) {
			if (i != j) {
				if (this->path[i].first == this->path[j].first) {
					if (this->path[i].second.second < this->path[j].second.second) {
						this->path[j].second.first += this->path[i].second.first;
						this->path.erase(this->path.begin() + i);
					}
					else {
						this->path[i].second.first += this->path[j].second.first;
						this->path.erase(this->path.begin() + j);
					}
				}
			}
		}
	}
}

/* ПОИСК В ШИРИНУ */
bool Task10::BFS(Graph& MyGraph, int start, int end) {

	/* Нашли ли мы хотя бы один путь */
	bool findPath = false;

	/* Вектор посещённых вершин */
	std::vector <bool> visited; 

	/* Изначально все вершины не посещены */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		visited.push_back(false);
	}

	/* Очередь непосещённых вершин */
	std::queue <int> q;

	/* Вектор дистанций */
	std::vector <int> prev;

	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		prev.push_back(i);
	}

	/* Устанавливаем базовые значения для стартовой вершины */
	q.push(start);
	visited[start] = true;
	prev[start] = start;

	/* Сам алгоритм DFS */
	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();

		for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
			int neighbor = j;
			if (MyGraph.adjencyMatrix()[currentVertex][neighbor] != 0 && currentVertex != neighbor) {
				if (visited[neighbor] != true) {
					q.push(neighbor);
					visited[neighbor] = true;
					prev[neighbor] = currentVertex;

					if (neighbor == this->stock) {
						findPath = true;
					}
				}
			}
		}
	}

	/* ЕСЛИ ОБНАРУЖИЛИ ХОТЯ БЫ ОДИН ПУТЬ */
	if (findPath == true) {
		int from = this->stock;
		int min = INF;
		std::vector < std::pair <int, int> > pathC;

		/* Восстанавливаем текущий путь */
		while (from != this->source) {
			if (MyGraph.adjencyMatrix()[prev[from]][from] < min && MyGraph.adjencyMatrix()[prev[from]][from] != 0) {
				min = MyGraph.adjencyMatrix()[prev[from]][from];
			}
			pathC.push_back(std::make_pair(prev[from], from));
			from = prev[from];
		}

		/* Добавляем рёбра и текущий|максимальный поток в пути */
		for (int i = 0; i < pathC.size(); i++) {
			std::pair <int, int> edgesC;
			std::pair <int, int> flowC;
			edgesC.first = pathC[i].first;
			edgesC.second = pathC[i].second;
			flowC.first = min;
			flowC.second = MyGraph.adjencyMatrix()[pathC[i].first][pathC[i].second];
			auto element = std::make_pair(edgesC, flowC);
			this->path.push_back(element);
		}

		/* Добавляем текущий максимальный поток по пути в общий максимальный поток */
		this->maxFlow += min;

		/* Создаём обратные рёбра и вычитаем максимальный поток по текущему пути */
		for (int i = 0; i < pathC.size(); i++) {
			MyGraph.adjencyMatrix()[pathC[i].first][pathC[i].second] -= min;
			MyGraph.adjencyMatrix()[pathC[i].second][pathC[i].first] = min;
		}
		return true;
	}

	return false;

}

/* Переопределение ключей*/
void Task10::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* Парсинг флагов */
bool Task10::parseFlags(int argc, char** argv) {
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