#pragma once
class Graph 
{
private:

	/* ��������� ��� ������ �������� ������ ���� */
	struct EdgesListElement {
		int Start;
		int End;
		int Weight;
	};

	/* ��� ��������� ��� ������ ��������� */
	struct AdjencyListVertexPair { //��������� ������� ������
		int Vertex;
		int Weight;
	};
	struct AdjencyListVertex { //��������� ��� �������� ������� � ������� ������� � ��� ������
		int Vertex;
		std::vector <AdjencyListVertexPair> VertexAndWeight;
	};

	std::vector <std::vector<int> > AMatrix; //������� ���������
	std::vector <EdgesListElement> EList; //������ ����
	std::vector <AdjencyListVertex> AList; //������ ���������


	void ALtoAM(); //����� ��� �������������� ������ ��������� � �������
	void ELtoAM(); //����� ��� �������������� ������ ���� � ������� ���������
	void AMtoEL(); //����� ��� �������������� ������� ��������� � ������ ����
	void AMtoAL(); //����� ��� �������������� ������� ��������� � ������ ���������

	bool parseAdjencyMatrix(std::string path);
	bool parseEdgesList(std::string path);

public:

	Graph(std::string, int); //����������� ������

	/* �������, ������������ ��� ����� */
	int weight(int, int);

	/* �������, ������������, ���� �� ����� */
	bool isEdge(int, int);

	/* �������, ������������, ���� �� ���� */
	bool isArc(int, int);

	/* �������, ������������, ��������������� ���� ��� ��� */
	bool isDirected();

	/* �������, ������������ ������ ���� ����������� ������ */
	

	/* ������� ������������� � �������� �������� */
	std::vector < std::vector <int> > & adjencyMatrix(); //������� ������ �� ������� ���������
	std::vector <EdgesListElement> & edgesList(); //������� ������ ���������
	std::vector <AdjencyListVertex> & adjencyList();
};

