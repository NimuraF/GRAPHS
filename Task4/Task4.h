#pragma once

#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"

class Task4 : public Task
{
private:

	int currentAlgorithm = 0; //1 - �������� ��������, 2 - �������� �����, 3 - �������� �������, 4 - ��� ���������� + �����

	std::vector < std::pair </* ����� ������ � ������ ����*/int, /* ��� ����� */int> > allWeights; //������ ����

	std::vector < std::pair<int, int> > SpanningTree; //�������� ������� � ���� ������ ���� //
	int SumEdgeWeight = 0; //��������� ��� ������

	unsigned int TimerKruskala = 0;
	unsigned int TimerPrima = 0;
	unsigned int TimerBoruvki = 0;

public:
	/* ����������� ��������� �����*/
	Task4(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void clearContainers(); //������� ����������� �����
	void showSpanningTreeAndWeight(); //����� ��������� ������ �� �����/����

	/* �������������� � ������ */
	void FindSpanningTree(Graph&); //���������� ��������� ������ � ����
	void createUndirectedGrah(Graph&); //������ ����������� ���� (����, ��� �������� ���� ������)

	void Kruskal(Graph&); //�������� ��������
	void Prima(Graph&); //�������� �����
	void Boruvki(Graph&); //�������� �������
};

