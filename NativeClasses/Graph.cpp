#include "pch.h"
#include "Graph.h"
#include "MException.h"

Graph::Graph(std::string path, int type) {
	switch (type) {
		
	case 1: {
		if (this->parseAdjencyMatrix(path)) {
			/* �������� ������� �������������� ������� ��������� � ������ ���� � ������ ��������� */
			this->AMtoEL();
			this->AMtoAL();
			this->AMtoALWW();
		}
		else {
			throw MException("�� ������� ��������� ������� ����!");
		}
		break;
	}

	case 2: {
		if (this->parseEdgesList(path)) {
			this->ELtoAM();
			this->AMtoAL();
			this->AMtoALWW();
		}
		else {
			throw MException("�� ������� ��������� ������� ����!");
		}
		break;
	}

	case 3: {
		if (this->parseAdjencyList(path)) {
			this->ALtoEL();
			this->ELtoAM();
			this->AMtoALWW();
		}
		else {
			throw MException("�� ������� ��������� ������� ����!");
		}
		break;
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
	/* ������ ������ �� ������ ������ ���� � ���������� ���*/
	std::vector <EdgesListElement> & EL = this->EList;
	return EL;
}
std::vector <Graph::AdjencyListVertex> & Graph::adjencyList() { //���������� ������ ���������
	/* ������ ������ �� ������ c����� ��������� � ���������� ���*/
	std::vector <AdjencyListVertex>& AL = this->AList;
	return AL;
}
std::vector < std::vector <int> >& Graph::adjencyListWW() { //���������� ������ ��������� ��� �����
	std::vector < std::vector <int> > & ALWW = this->AListWW;
	return ALWW;
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
void Graph::AMtoAL() { //����� ������������� ������� ��������� -> ������ ���������
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
void Graph::AMtoALWW() { //����� ������������� ������� ��������� -> ������ ��������� ��� �����
	for (int i = 0; i < this->AMatrix.size(); i++) {
		std::vector <int> row;
		for (int j = 0; j < this->AMatrix.size(); j++) {
			if (this->AMatrix[i][j] != 0) {
				row.push_back(j);
			}
		}
		this->AListWW.push_back(row);
	}
}
void Graph::ELtoAM() { //����� ������������� ������ Ш��� -> ������� ���������
	int VC = 0;
	for (int i = 0; i < this->EList.size(); i++) {
		if (this->EList[i].Start > VC) {
			VC = this->EList[i].Start;
		}
		if (this->EList[i].End > VC) {
			VC = this->EList[i].End;
		}
	}
	VC += 1;
	for (int i = 0; i < VC; i++) {
		std::vector < std::pair <int, int> > rows;
		for (int z = 0; z < this->EList.size(); z++) {
			if (this->EList[z].Start == i) {
				rows.push_back(std::pair <int, int>(EList[z].End, EList[z].Weight));
			}
		}
		std::vector <int> row;

		/* ������� �� �������� */
		for (int j = 0; j < VC; j++) {
			row.push_back(0);
		}

		for (int p = 0; p < rows.size(); p++) {
			row[rows[p].first] = rows[p].second;
		}

		AMatrix.push_back(row);
	}
}
void Graph::ALtoEL() { //����� ������������� ������ ��������� -> ������ Ш���
	for (int i = 0; i < this->AList.size(); i++) {
		for (int j = 0; j < this->AList[i].VertexAndWeight.size(); j++) {
			//������ ��������� ����� ������ ������ ����
			EdgesListElement element;
			element.Start = i;
			element.End = this->AList[i].VertexAndWeight[j].Vertex;
			element.Weight = this->AList[i].VertexAndWeight[j].Weight;
			this->EList.push_back(element);
		}
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
int Graph::weight(int Start, int End) { //���������� ��� �����
	return this->AMatrix[Start][End];
}
std::vector <int> Graph::AdjVertexes(int Vertex) { //���������� ������ ������� ������ ��� �����

	std::vector <int> adjvertexes = adjencyListWW()[Vertex];

	return adjvertexes;
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

		return true;
	}
}
bool Graph::parseEdgesList(std::string path) {
	std::ifstream file; //������ ����� ��� ������ �� �����
	file.open(path); //��������� ����

	/* ���� ���� �� ������� �������, ������� ���������� */
	if (!file) {
		return false;
	}

	std::string data; //����� ��� ������

	while (!file.eof()) {
		getline(file, data);
		if (data != "") {
			std::vector <int> elements;
			const char* cdata = data.c_str(); //����������� � c-������
			char* elem = strtok(const_cast<char*>(cdata), " "); //��������� �� ����������� �� ������
			int i = 0;
			
			while (elem != nullptr && i < 3) { //��� �� ������� ������, �������� �� ����������� � ��������� � ������
				elements.push_back(stoi(std::string(elem)));
				elem = strtok(nullptr, " ");
				i++;
			}

			/* ���� �� ������ ��� � 3 �������, �� ����� ��� �� ��������� = 1 */
			if (elements.size() < 3) {
				Graph::EdgesListElement NewEdge;
				NewEdge.Start = elements[0] - 1;
				NewEdge.End = elements[1] - 1;
				NewEdge.Weight = 1;
				this->EList.push_back(NewEdge);
			}
			else { //� ���� ������ ���� ��� �� �������� �������
				Graph::EdgesListElement NewEdge;
				NewEdge.Start = elements[0] - 1;
				NewEdge.End = elements[1] - 1;
				NewEdge.Weight = elements[2];
				this->EList.push_back(NewEdge);
			}
		}
	}
	file.close();
}
bool Graph::parseAdjencyList(std::string path) {
	std::ifstream file; //������ ����� ��� ������ �� �����
	file.open(path); //��������� ����

	/* ���� ���� �� ������� �������, ������� ���������� */
	if (!file) {
		return false;
	}

	int rows = 0;

	std::string data; //����� ��� ������

	/* ������� ����� ���������� �����*/
	while (!file.eof()) {
		getline(file, data);
		rows++;
	}

	/* ������ ����� ��� ����������� ����������� ��������� */
	file.clear();

	/* ���������� ��������� � ������ ����� */
	file.seekg(0L, std::ios_base::beg);


	int currentVertex = 0;
	int currentRow = 0;

	while (!file.eof() && currentRow < rows - 1) {
		getline(file, data);
		std::vector <AdjencyListVertexPair> adjencyVertexes; //������ ������� ������
		const char* cdata = data.c_str(); //����������� � c-������
		char* elem = strtok(const_cast<char*>(cdata), " "); //��������� �� ����������� �� ������

		while (elem != nullptr) {
			AdjencyListVertexPair Pair;
			Pair.Vertex = atoi(elem) - 1;
			Pair.Weight = 1;
			adjencyVertexes.push_back(Pair);
			elem = strtok(nullptr, " ");
		}

		AdjencyListVertex NewRow;
		NewRow.Vertex = currentVertex;
		NewRow.VertexAndWeight = adjencyVertexes;

		this->AList.push_back(NewRow);
		currentVertex++;
		currentRow++;
	}

	file.close();

}