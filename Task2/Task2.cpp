#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/parseOut.h"
#include "Task2.h"

Task2::Task2(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("�� ������� ��������� �����!");
	}
	else {
		/* ��������� ���� ��� ������ ���� �� ���� */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
		}

		Graph MyGraph(this->getCurrentPath(), this->getCurrentFormat());
		AllComponents(MyGraph);
	}
}




/* ������ ����� ���������������� ������ � ������� */
void Task2::FindConnectionComponents(Graph& MyGraph, int startV) { //���� ���������� ��������� � ����������������� ����� ����� ����� � ������
	std::queue <int> relatedVertexes; //������� ������� ������
	std::vector <bool> currentVisited; //�������, ���������� �� �������
	for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
		currentVisited.push_back(false);
	}

	relatedVertexes.push(startV); //����������� ������ �������
	currentVisited[startV] = true; //������������� ������� ������� ��� ����������
	this->visited[startV] = true; //������������� ������� ������� ��� ����������

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
void Task2::AllComponents(Graph& MyGraph) {
	if (!MyGraph.isDirected()) {
		for (int i = 0; i < MyGraph.adjencyMatrix().size(); i++) {
			this->visited.push_back(false);
		}

		for (int i = 0; i < this->visited.size(); i++) {
			if (this->visited[i] == false) {
				this->FindConnectionComponents(MyGraph, i);
			}
		}

		/* ����� ������������������ ����� (�������������, ������ ��������� �������) */
		if (!this->getOutputFlag()) {
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
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				if (this->ConnectionComponents.size() > 1) {
					output << "Graph is not connected and contains " << this->ConnectionComponents.size() << " components." << std::endl;
					output << "Connected components:" << std::endl;
				}
				else {
					output << "Graph is connected" << std::endl;
					output << "Connected components:" << std::endl;
				}
				output << "[";
				for (int i = 0; i < this->ConnectionComponents.size(); i++) {
					output << "[ ";
					for (int z = 0; z < this->ConnectionComponents[i].size(); z++) {
						output << this->ConnectionComponents[i][z] + 1 << " ";
					}
					output << "]";
				}
				output << "]";
			}
			else {
				throw MException("�� ������� ������� ���� ��� ������!");
			}
		}
	}
	else {
		std::vector < std::vector <int> > nonDirected = MyGraph.adjencyMatrix();

		/* ����������� ������� ��������� */
		for (int i = 0; i < nonDirected.size(); i++) {
			for (int j = 0; j < nonDirected.size(); j++) {
				if (nonDirected[i][j] != nonDirected[j][i] && j != i) {
					if (nonDirected[i][j] > nonDirected[j][i]) {
						nonDirected[j][i] = nonDirected[i][j];
					}
					else {
						nonDirected[i][j] = nonDirected[j][i];
					}
				}
			}
		}

		/* �������� �� � ������ ��������� ���� */
		std::ofstream tempfile;
		tempfile.open("new_file.txt");

		for (int i = 0; i < nonDirected.size(); i++) {
			for (int j = 0; j < nonDirected.size(); j++) {
				tempfile << nonDirected[i][j] << " ";
			}
			tempfile << std::endl;
		}

		/* �������� �� ������ ���������� ����� ����� ��������������� ���� */
		Graph TempGraph("new_file.txt", 1);

		tempfile.close();
		/* ������ ��������� ���� */
		std::remove("new_file.txt");

		/* ���������� ������� ������� ��� ����������� ��������� ������ ��������� ������� */
		this->AllComponents(TempGraph);

		/* �������� ������� ������ ������� ��������� ��������� */
		this->FindStrongComponents(MyGraph);

		/* ������� ���������� ������� ���������*/
		if (!this->getOutputFlag()) {
			if (this->StrongConnectionComponents.size() > 1) {
				std::cout << "\nDigraph is weakly connected and contains " << this->StrongConnectionComponents.size() << " strongly connected components." << std::endl;
				std::cout << "Strongly connected components:" << std::endl;
			}
			else {
				std::cout << "\nDigraph is strongly connected." << std::endl;
				std::cout << "Strongly connected components:" << std::endl;
			}
			std::cout << "[";
			for (int i = 0; i < this->StrongConnectionComponents.size(); i++) {
				std::cout << "[ ";
				for (int z = 0; z < this->StrongConnectionComponents[i].size(); z++) {
					std::cout << this->StrongConnectionComponents[i][z] + 1 << " ";
				}
				std::cout << "]";
			}
			std::cout << "]";
		}
		else {
			std::ofstream output;
			output.open(this->getCurrentOutputPath(), std::ios::app);
			if (output.is_open()) {
				if (this->StrongConnectionComponents.size() > 1) {
					output << "\nDigraph is weakly connected and contains " << this->StrongConnectionComponents.size() << " strongly connected components." << std::endl;
					output << "Strongly connected components:" << std::endl;
				}
				else {
					output << "\nDigraph is strongly connected." << std::endl;
					output << "Strongly connected components:" << std::endl;
				}
				output << "[";
				for (int i = 0; i < this->StrongConnectionComponents.size(); i++) {
					output << "[ ";
					for (int z = 0; z < this->StrongConnectionComponents[i].size(); z++) {
						output << this->StrongConnectionComponents[i][z] + 1 << " ";
					}
					output << "]";
				}
				output << "]";
			}
			else {
				throw MException("�� ������� ������� ���� ��� ������!");
			}
		}
	}
}
void Task2::dfs1(std::vector < std::vector <int> > & g, int v) { //����� � �������
	this->used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i)
		if (!this->used[g[v][i]])
			dfs1(g, g[v][i]);
	order.push_back(v);
}
void Task2::dfs2(std::vector < std::vector <int> > & gr, int v) { //����� � ������� ���������������� �����
	this->used[v] = true;
	component.push_back(v);
	for (size_t i = 0; i < gr[v].size(); ++i)
		if (!this->used[gr[v][i]])
			dfs2(gr, gr[v][i]);
}
void Task2::FindStrongComponents(Graph& MyGraph) { //����� ������� ��������� ��������� �������

	/* ��������� ����� ������� � ������� �����, ������� ���������� ������� � ������� ���������� ������� ������, �.�. ��������� ������ order. */
	used.assign(MyGraph.adjencyList().size(), false);
	for (int i = 0; i < MyGraph.adjencyList().size(); ++i) {
		if (!this->used[i]) {
			dfs1(MyGraph.adjencyListWW(), i);
		}
	}


	/* ������ ��������������� ���� */
	for (int i = 0; i < MyGraph.adjencyList().size(); ++i) {
		std::vector <int> edge;
		this->AJListWWInvert.push_back(edge);
	}

	for (int i = 0; i < MyGraph.edgesList().size(); i++) {
		this->AJListWWInvert[MyGraph.edgesList()[i].End].push_back(MyGraph.edgesList()[i].Start);
	}
	/* ����� �������� ���������������� ����� */


	/*��������� ����� ������� � ������� / ������ ����� ����� � �������, ������������ ������� order (� ������, � �������� �������,
	�.�. � ������� ���������� ������� ������). ������ ��������� ������, ����������� � ���������� ���������� ������� ������, 
	� ����� ��������� ����������� ������� ���������.*/
	used.assign(MyGraph.adjencyList().size(), false);
	for (int i = 0; i < MyGraph.adjencyList().size(); ++i) {
		int v = order[MyGraph.adjencyList().size() - 1 - i];
		if (!this->used[v]) {
			dfs2(this->AJListWWInvert, v);
			std::sort(this->component.begin(), this->component.end());
			this->StrongConnectionComponents.push_back(this->component);
			this->component.clear();
		}
	}
}

/* ��������������� ������*/
void Task2::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-e", "edges_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-l", "adjacency_list_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "adjacency_matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* ������� ������ */
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