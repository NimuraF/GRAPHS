#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task6.h"

const int INF = 10000000;

Task6::Task6(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("�� ������� ��������� �����!");
	}
	else {
		/* ������� ���� ��� ������ ���� �� ���� */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
			output.close();
		}

		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		this->chooseAlg(MyGraph);
	}
}

/* ����������� ��������� */
void Task6::chooseAlg(Graph& MyGraph) {

	this->checkNegativeEdges(MyGraph);

	switch (this->currentAlgorithm) {

	case 1: { //������ ��������
		if (this->isNegativeEdges == true) {
			std::cout << "Graph contains negative edges! Deikstra not working!" << std::endl;
		}
		else {
			this->Deikstra(MyGraph);
		}
		break;
	}

	case 2: {
		this->BellmanFord(MyGraph);
	}

	}


	this->showPaths();
}

/* ������� ������ ����� */
void Task6::showPaths() {
	std::cout << "Shortest paths lengths:" << std::endl;
	for (int i = 0; i < this->Paths.size(); i++) {
		std::cout << this->StartVertex + 1 << " - " << this->Paths[i].first + 1 << " : " << this->Paths[i].second << std::endl;
	}
}

/* ������� ��� �������� ������� ���� � ������������� ����� */
void Task6::checkNegativeEdges(Graph& MyGraph) {
	int isN = false; //������� �� ���������� �����
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
			if (MyGraph.adjencyMatrix()[i][j] < 0) {
				this->isNegativeEdges = true;
				isN = true;
				break;
			}
		}
		if (isN) {
			break;
		}
	}
}

/* �������� ��������-�����*/
void Task6::BellmanFord(Graph& MyGraph) {

	/* ������ ���������� */
	std::vector <int> distances;

	/* ���������� �� ���� ������ ���������� ���������� */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		distances.push_back(INF);
	}

	/* � ��������� ������� ���������� 0 */
	distances[this->StartVertex] = 0;


	/* �������� ��������-�����*/
	for (int i = 0; i < MyGraph.edgesList().size() - 1; i++) {
		for (int j = 0; j < MyGraph.edgesList().size(); j++) {
			if (distances[MyGraph.edgesList()[j].Start] != INF) {
				distances[MyGraph.edgesList()[j].End] = std::min(distances[MyGraph.edgesList()[j].Start] + MyGraph.edgesList()[j].Weight, distances[MyGraph.edgesList()[j].End]);
			}
		}
	}
	
	/* ������ ��� +1 �������� ��� ����������� ������ �������������� ���� */
	for (int j = 0; j < MyGraph.edgesList().size(); j++) {
		if (distances[MyGraph.edgesList()[j].Start] != INF) {
			if (distances[MyGraph.edgesList()[j].End] > distances[MyGraph.edgesList()[j].Start] + MyGraph.edgesList()[j].Weight) {
				this->negativeCycle = true;
				break;
			}
		}
	}

	if (this->negativeCycle != true) {
		/* ����� �� � ������ ����� */
		for (int i = 0; i < distances.size(); i++) {
			this->Paths.push_back(std::pair<int, int>(i, distances[i]));
		}
	}
	else {
		std::cout << "Graph contains negative cycle" << std::endl;
	}
}

/* �������� �������� */
void Task6::Deikstra(Graph& MyGraph) {

	/* ������ ���������� ������ */
	std::vector <bool> visited;

	int minindex = 0;
	int min = 0;

	/* ������ ���������� */
	std::vector <int> distances;

	/* ���������� ��� ������� �� ��������*/
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		visited.push_back(false);
	}

	/* ���������� �� ���� ������ ���������� ���������� */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		distances.push_back(INF);
	}

	/* � ��������� ������� ���������� 0 */
	distances[this->StartVertex] = 0;

	/* ������������� ���-�� �������� ������ ���-�� ������ */
	int vertexC = 0;

	/* ���� � ��������� ���������� ���� �� ���� INF � ���������� ������ ������ ���-�� ������ */
	while (std::count(distances.begin(), distances.end(), INF) > 0 && vertexC <= MyGraph.adjencyMatrix().size()) {
		for (int i = 0; i < distances.size(); i++) {
			if (distances[i] != INF) {
				int min = INF;
				int minV = -1;
				for (int j = 0; j < MyGraph.adjencyMatrix().size(); j++) {
					if (i != j && MyGraph.adjencyMatrix()[i][j] != 0) {
						/* ������� ����, ���� ���������� ���� ������, ��� ���������� �������, �� ��������� ��� ����� - ��������������*/
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

	/* ����� �� � ������ ����� */
	for (int i = 0; i < distances.size(); i++) {
		this->Paths.push_back(std::pair<int, int>(i, distances[i]));
	}

}

/* ��������������� ������*/
void Task6::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-n", "Start vertex"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-d", "Algorithm Deikstri"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-b", "Algorithm Belmana-Forda"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-t", "Algorim Levita"));
}

/* ������� ������ */
bool Task6::parseFlags(int argc, char** argv) {
	if (argc >= 4) {
		int mainFlagsC = 0;
		int algFlagsC = 0;
		bool BeginFlag = false;
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
			}

			if (strcmp(argv[i], "-d") == 0 && this->currentAlgorithm != 1) {
				this->currentAlgorithm = 1;
				algFlagsC++;
			}
			else if (strcmp(argv[i], "-b") == 0 && this->currentAlgorithm != 2) {
				this->currentAlgorithm = 2;
				algFlagsC++;
			}
			else if (strcmp(argv[i], "-t") == 0 && this->currentAlgorithm != 3) {
				this->currentAlgorithm = 3;
				algFlagsC++;
			}

			if (strcmp(argv[i], "-h") == 0) {
				this->Help();
				return false;
			}
		}

		if (mainFlagsC != 1 || this->currentPath == "" || !BeginFlag || algFlagsC != 1) {
			return false;
		}

		return true;
	}
	else {
		return false;
	}
}