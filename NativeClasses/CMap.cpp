#include "pch.h"
#include "CMap.h"
#include "MException.h"

CMap::CMap(std::string path) {
	if (!this->parseMap(path)) {
		throw MException("�� ������� ���������� �������!");
	}
}


/* ������� ����� (������� ���������) �� ������ */
std::vector < std::vector <int> > & CMap::getMap() {
	std::vector < std::vector <int> >& Map = this->MAP;
	return Map;
}

/* �����������, ������������ ������ ������� � ����� */
int CMap::Indexator(int i, int j) {
	return this->MAP[i][j];
}

/* �������, ������������ ������ ���� ������� � ���������� ������ */
std::vector < std::pair <int, int > > CMap::neighbors(std::pair <int, int> vertex) {
	std::vector < std::pair <int, int > > neighbors;

	/* ��������� ������� ������ */
	if (vertex.second != this->MAP[vertex.first].size() - 1) {
		std::pair <int, int> RightNeighbor;
		RightNeighbor.first = vertex.first;
		RightNeighbor.second = vertex.second + 1;
		neighbors.push_back(RightNeighbor);
	}

	/* ��������� ������ ������ */
	if (vertex.second != 0) {
		std::pair <int, int> LeftNeighbor;
		LeftNeighbor.first = vertex.first;
		LeftNeighbor.second = vertex.second - 1;
		neighbors.push_back(LeftNeighbor);
	}

	/* ��������� �������� ������ */
	if (vertex.first != 0) {
		std::pair <int, int> TopNeighbor;
		TopNeighbor.first = vertex.first - 1;
		TopNeighbor.second = vertex.second;
		neighbors.push_back(TopNeighbor);
	}

	/* ��������� �������� ������ */
	if (vertex.first != this->MAP.size() - 1) {
		std::pair <int, int> BotNeighbor;
		BotNeighbor.first = vertex.first + 1;
		BotNeighbor.second = vertex.second;
		neighbors.push_back(BotNeighbor);
	}

	return neighbors;
}

/* ������� ����� */
bool CMap::parseMap(std::string path) {
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
			std::vector <int> row;
			const char* cdata = data.c_str(); //����������� � c-������
			char* elem = strtok(const_cast<char*>(cdata), " "); //��������� �� ����������� �� ������

			while (elem != nullptr) { //��� �� ������� ������, �������� �� ����������� � ��������� � ������
				row.push_back(stoi(std::string(elem)));
				elem = strtok(nullptr, " ");
			}

			this->MAP.push_back(row);
		}
	}

	file.close();
}