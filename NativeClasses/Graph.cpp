#include "pch.h"
#include "Graph.h"
#include "MException.h"

Graph::Graph(std::string path, int type) {
	switch (type) {
		
	case 1: {
		if (this->parseAdjencyMatrix(path)) {

		}
		else {
			throw MException("�� ������� ��������� ������� ����!");
		}
	}

	}
}


/* ������� ������������ ������������� ����� */
std::vector < std::vector <int> > & Graph::adjencyMatrix() { //���������� ������� ���������
	/* ������ ������ �� ������ ������� ��������� � ���������� ���*/
	std::vector < std::vector <int> >& AM = this->AMatrix;
	return AM;
}
std::vector <Graph::EdgesListElement> & Graph::edgesList() { //��������� ������ Ш���
	/* ������� ������ ���� �� �����*/
	for (int i = 0; i < this->EList.size(); i++) {
		std::cout << EList[i].Start << " " << EList[i].End << " " << EList[i].Weight << std::endl;
	}
	/* ������ ������ �� ������ ������� ���������� � ���������� ���*/
	std::vector <EdgesListElement> & EL = this->EList;
	return EL;
}
std::vector <Graph::AdjencyListVertex> & Graph::adjencyList() { //���������� ������ ���������
	for (int i = 0; i < this->AList.size(); i++) {
		std::cout << this->AList[i].Vertex << " - ";
		for (int j = 0; j < this->AList[i].VertexAndWeight.size(); j++) {
			std::cout << "[" << this->AList[i].VertexAndWeight[j].Vertex << ", " << this->AList[i].VertexAndWeight[j].Weight << "] ";
		}
		std::cout << std::endl;
	}
	std::vector <AdjencyListVertex>& AL = this->AList;
	return AL;
}


/* ���������� ������� ����� ������������� */
void Graph::AMtoEL() { //����� ������������� ������� ��������� -> ������ Ш���
	for (int i = 0; i < this->AMatrix.size(); i++) {
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				EdgesListElement row;
				row.Start = i; //��������� ��������� ����� (1 �������)
				row.End = j; //��������� �������� �������, � ������� ���� �����
				row.Weight = this->AMatrix[i][j]; //��������� � 3 ������� ��� ����� ����� ����
				this->EList.push_back(row);
			}
		}
	}
}
void Graph::AMtoAL() {
	for (int i = 0; i < this->AMatrix.size(); i++) {
		AdjencyListVertex Vertex;
		Vertex.Vertex = i;
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				AdjencyListVertexPair Pair;
				Pair.Vertex = j;
				Pair.Weight = this->AMatrix[i][j];
				Vertex.VertexAndWeight.push_back(Pair);
			}
		}
		this->AList.push_back(Vertex);
	}
}


/* �������� ������� ����� */
bool Graph::isDirected() { //�������, ������������ true, ���� ���� ��������������� � false - ���� ���
	for (int i = 0; i < this->AMatrix.size(); i++) {
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != this->AMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}
bool Graph::isEdge(int Start, int End) { //�������� ������������� �����
	if (this->AMatrix[Start][End] != 0 || this->AMatrix[End][Start] != 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Graph::isArc(int Start, int End) { //���������, ���� �� ����� ��������� ����
	if (this->AMatrix[Start][End] != 0) {
		return true;
	}
	else {
		return false;
	}
}


/* ���������� ������� �������� */
bool Graph::parseAdjencyMatrix(std::string path) {
	std::ifstream file; //������ ����� ��� ������ �� �����
	file.open(path); //��������� ����

	/* ���� ���� �� ������� �������, ������� ���������� */
	if (!file) {
		return false;
	}


	std::string data; //����� ��� ������
	int buffer; //����� ��� �����
	int rows = 0; // ���������� �����
	int elements = 0; //���������� ���������

	/* ������� ���������� �� ������� � ������� �� ���-��, ������ ������ ���������� */
	while (!file.eof()) {
		getline(file, data);
		if (data != "") {
			rows++;
		}
	}

	/* ������ ����� ��� ����������� ����������� ��������� */
	file.clear();

	/* ���������� ��������� � ������ ����� */
	file.seekg(0L, std::ios_base::beg);

	/* ���������� �� ���� ��������� � ������� �� ���������� */
	while (!file.eof()) {
		file >> buffer;
		elements++;
	}

	/* ����� ���������� ��������� �� ������, ��� ��� ��� � ���������� ����� ������������� � ��� �������� (� ������ ������ ������) */
	file.clear();
	file.seekg(0L, std::ios_base::beg);

	/*
	��������� ������� �� ���� ����, ��� ��� ���������� (������� ��������� ������� ���� ����������),
	��� ����� �������� ���-�� ����� � ������� � ���������� � ����������� ����������� ���������
	*/
	if (elements - 1 != rows * rows) {
		/* ��������� ���������� � ������ */
		file.close();
		return false;
	}
	else {
		/* ��������� ���������� ������ ���� ��������� */
		int step = 0;
		int* AllElements = new int[elements - 1];

		//���������� ��� �������� �� ����� � ���� ���������� ������
		while (!file.eof()) {
			file >> AllElements[step];
			step++;
		}

		int step2 = 0;

		/* ������������ ������ �� ����������� ������� � ��������� */
		for (int x = 0; x < rows; x++) {
			std::vector <int> row;
			for (int y = 0; y < rows; y++) {
				row.push_back(AllElements[step2]);
				step2++;
			}
			this->AMatrix.push_back(row);
		}

		/* ��������� ���������� � ������ */
		file.close();

		/* ������ ������ �� ����������� ������� */
		delete[] AllElements;

		/* �������� ������� �������������� ������� ��������� � ������ ���� � ������ ��������� */
		this->AMtoEL();
		this->AMtoAL();

		return true;
	}
}
bool Graph::parseEdgesList(std::string path) {
	return false;
}