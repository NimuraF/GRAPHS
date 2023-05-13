#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task1 : public Task
{
private:
	const int INF = 10000;

	std::vector < std::vector <int> > SDM; //������� ���������� ����������
	std::vector <int> Eccentrycities; //������ ����������������
	std::vector <int> Peripheral; //������ ������������ ������
	std::vector <int> CentralVertexes; //������ ����������� ������
	int Rad; //������
	int Diametr; //�������

public:
	/* ����������� ��������� �����*/
	Task1(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* �������������� � ������ */
	void ShortestDistanceMatrix(Graph&); //������� ���������� ����������
	void VertexDegrees(Graph&); //������ �������� ������
	void Diameter(Graph&); //������� �����
	void REPC(Graph& MyGraph); //���������������, ������ � ������������ �������
};

