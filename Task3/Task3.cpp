#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task3.h"

Task3::Task3(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("�� ������� ��������� �����!");
	}
	else {
		/* ��������� ���� ��� ������ ���� �� ���� */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
			output.close();
		}

		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		this->getBridges(MyGraph);
		this->getCutVertices(MyGraph);
	}
}

/* ����� � ������� ��� ����������� ������! */
void Task3::DFSB(Graph& MyGraph, int startVertex, int predok) {
	/* ������������� ��������� ������� ��� ���������� */
	this->visited[startVertex] = true;

	this->timer++;

	timeIn[startVertex] = this->timer;
	fUp[startVertex] = this->timer;

	/* ������� ��� ������� �� ��������� �������*/
	for (int i = 0; i < MyGraph.adjencyListWW()[startVertex].size(); i++) {
		/* ���������� �������, � �������� ��� */
		int potomok = MyGraph.adjencyListWW()[startVertex][i];

		/* ���� ����� ������� � ������, �� ���������� ��� �������� */
		if (potomok == predok) {
			continue;
		}

		/* ���� ������� ��� �������, �� ������ ���������� ����� ����� */
		if (this->visited[potomok]) {
			this->fUp[startVertex] = std::min(this->fUp[startVertex], this->timeIn[potomok]);
		}
		else {
			this->DFSB(MyGraph, potomok, startVertex);
			this->fUp[startVertex] = std::min(this->fUp[startVertex], this->fUp[potomok]);
			if (fUp[potomok] > timeIn[startVertex]) {
				this->Bridges.push_back(std::pair <int, int>(startVertex, potomok));
			}
		}
	}
}

/* ����� � ������� ��� ����� ����������! */
void Task3::DFSP(Graph& MyGraph, int startVertex, int predok) {

	/*�������� �� ���������� ����������� � �����*/
	int cnt = 0;

	/* ������������� ��������� ������� ��� ���������� */
	this->visited[startVertex] = true;

	this->timer++;

	timeIn[startVertex] = this->timer;
	fUp[startVertex] = this->timer;

	/* ������� ��� ������� �� ��������� �������*/
	for (int i = 0; i < MyGraph.adjencyListWW()[startVertex].size(); i++) {

		/* ���������� �������, � �������� ��� */
		int potomok = MyGraph.adjencyListWW()[startVertex][i];

		/* ���� ����� ������� � ������, �� ���������� ��� �������� */
		if (potomok == predok) {
			continue;
		}

		/* ���� ������� ��� �������, �� ������ ���������� ����� ����� */
		if (this->visited[potomok]) {
			this->fUp[startVertex] = std::min(this->fUp[startVertex], this->timeIn[potomok]);
		}
		else {
			/* ���� ��� ��������� �����, �� ����������� ���-�� �����������*/
			if (startVertex == this->currentRoot) {
				cnt++;
			}
			this->DFSP(MyGraph, potomok, startVertex);
			this->fUp[startVertex] = std::min(this->fUp[startVertex], this->fUp[potomok]);
			if (this->currentRoot != startVertex && timeIn[startVertex] <= fUp[potomok]) {
				this->CutVertices.push_back(startVertex);
			}
		}
	}

	/* ���������� ������, ���� � ���� ������, ��� 1 ��������� */
	if (cnt > 1 && startVertex == this->currentRoot) {
		this->CutVertices.push_back(startVertex);
	}
}

/* ����� ������ */
void Task3::getBridges(Graph& MyGraph) {

	this->ClearContainers(MyGraph);

	/* �������� ����� � ������� ��� ���� ������������ ������ */
	for (int i = 0; i < this->visited.size(); i++) {
		if (!this->visited[i]) {
			this->DFSB(MyGraph, i);
		}
	}

	if (!this->getOutputFlag()) {
		std::cout << "Bridges:" << std::endl;
		std::cout << "[";
		for (int i = 0; i < this->Bridges.size(); i++) {
			std::cout << "(" << this->Bridges[i].first + 1 << " - " << this->Bridges[i].second + 1 << ")";
		}
		std::cout << "]" << std::endl;
	}
	else {
		std::ofstream output;
		output.open(this->getCurrentOutputPath(), std::ios::app);
		if (output.is_open()) {
			output << "Bridges:" << std::endl;
			output << "[";
			for (int i = 0; i < this->Bridges.size(); i++) {
				output << "(" << this->Bridges[i].first + 1 << " - " << this->Bridges[i].second + 1 << ")";
			}
			output << "]" << std::endl;
		}
		else {
			throw MException("���, �� ������� ��������� ����!");
		}
	}

}

/* ����� �������� (����� ����������) */
void Task3::getCutVertices(Graph& MyGraph) {

	this->ClearContainers(MyGraph);

	for (int i = 0; i < this->visited.size(); i++) {
		if (!this->visited[i]) {
			this->currentRoot = i;
			this->DFSP(MyGraph, i);
		}
	}

	/* ������� �������� ���������� ��������� */
	std::sort(this->CutVertices.begin(), this->CutVertices.end());
	this->CutVertices.resize(std::unique(this->CutVertices.begin(), this->CutVertices.end()) - this->CutVertices.begin());

	if (!this->getOutputFlag()) {
		std::cout << "Cut Vertices :" << std::endl;
		std::cout << "["; 
		for (int i = 0; i < this->CutVertices.size(); i++) {
			std::cout << "[" << this->CutVertices[i] + 1 << "]";
		}
		std::cout << "]" << std::endl;
	}
	else {
		std::ofstream output;
		output.open(this->getCurrentOutputPath(), std::ios::app);
		if (output.is_open()) {
			output << "Cut Vertices :" << std::endl;
			output << "[";
			for (int i = 0; i < this->CutVertices.size(); i++) {
				output << "[" << this->CutVertices[i] + 1 << "]";
			}
			output << "]" << std::endl;
		}
		else {
			throw MException("���, �� ������� ��������� ����!");
		}
	}

}

void Task3::ClearContainers(Graph& MyGraph) {

	this->visited.clear();
	this->timeIn.clear();
	this->fUp.clear();

	/* ���������� ������ ������ ������ */
	this->timer = 0;

	/* ��������� ��� ������� false, ��� ��� �� � ��� �� ���� */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		this->visited.push_back(false);
	}

	/* ��������� ����� ����� � ������� �� ��������� � 0 ��� ������ ������� */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		this->timeIn.push_back(0);
	}

	/* ��������� ������ ��� �������� ����� ����� �� ������� ������� � �������, ������� ��� ���� ������������ �� ��������� � 0 */
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		this->fUp.push_back(0);
	}
}

/* ��������������� ������*/
void Task3::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* ������� ������ */
bool Task3::parseFlags(int argc, char** argv) {
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