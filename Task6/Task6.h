#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"

class Task6 : public Task {
private:

	int StartVertex = 0; //��������� �������

	bool isNegativeEdges = false; //����, ���������� �� ����������� � ����� ���� � ������������� �����

	int currentAlgorithm = 0; //1 - �������� ��������, �������� ��������-�����, �������� ������

	bool negativeCycle = false; //���� ��� ������� �������������� �����

	std::vector < std::pair <int, int> > Paths; // ������ �����


public:
	/* ����������� ��������� �����*/
	Task6(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void showPaths();
	void clearContainers();

	/* �������������� � ������ */
	void chooseAlg(Graph&); //������� ������ ���������
	void checkNegativeEdges(Graph&); //������� �������� ���� � ������������� �����
	void Deikstra(Graph&); //�������� ��������
	bool BellmanFord(Graph&); //�������� ��������-�����
	void Levit(Graph&); //�������� ������
};

