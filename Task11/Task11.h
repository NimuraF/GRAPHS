#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task11 : public Task {
private:

	std::vector <int> colors; //����� ��� ����������� ������������ 0 - �� ��������, 1 - �������, 2 - ������

	std::vector < std::pair <int, int> > edges; //������ ���� ��� ����� (��� ���� ���� = 1)

	bool biparate; //��������� ����, ���������� �� ������������

public:
	/* ����������� ��������� �����*/
	Task11(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&); //������� ��� ������ � ���� / �� �����

	/* ������ ������ � ������ */
	bool checkBiparate(Graph&, int, int); //������� �������� ����� �� ������������
	void maxPairs(Graph&); //������� ��� ����������� ������������� �������������
	void copyAllEdges(Graph&); //�������, ���������� ��� ���� � ������ ���� ��� ����� (��� ���� ���� = 1)
};

