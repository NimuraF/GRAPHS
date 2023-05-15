#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task3 : public Task
{
private:
	std::vector <bool> visited; //������ ���������� ������
	std::vector <int> timeIn; //������ ��� �������� ����� ����� � �������
	std::vector <int> fUp; //������ ��� �������� ����� ����� �� ������� ������� � �������, ������� ��� ���� ������������

	int timer = 0; //���������� ���������� ������
	int currentRoot; //������� ������

	std::vector < std::pair<int, int> > Bridges; //������ ������
	std::vector <int> CutVertices; //������ �������� (����� ����������)

public:
	/* ����������� ��������� �����*/
	Task3(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* �������������� � ������ */
	void DFSB(Graph&, int startVertex, int predok = -1); //����� � ������� ��� ������
	void DFSP(Graph&, int startVertex, int predok = -1); //����� � ������� ��� ����� ���������� (��������)

	void ClearContainers(Graph&); //��������� ��������� ���������� ��� �����������

	void getBridges(Graph&); //����������� ���� ������
	void getCutVertices(Graph&); //����������� ���� ��������
};

