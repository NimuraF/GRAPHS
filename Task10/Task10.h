#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task10 : public Task {
private:
	int maxFlow = 0; //������������ �����

	int source = 3; //��������
	int stock = 27; //����

	std::vector < std::pair < /* ����� */ std::pair <int, int>, /* ������� | ������������ ����� */ std::pair <int, int> > > path; //���� � ����������� ������ � ������� ��������

public:
	/* ����������� ��������� �����*/
	Task10(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&); //������� ��� ������ � ���� / �� �����

	/* ������ ������ � ������ */
	void FordFalkerson(Graph&); //�������� ����-����������
	bool BFS(Graph&, int, int); //������� BFS, ����������������� ��� �����-����������
	void StockSource(Graph&); //�������� ��� ����������� ����� � ������
	void sumFlows(); //������� ��� ������������ ������� �� ������ �����
};

