#pragma once
#include "../NativeClasses/Graph.h"
#include "../NativeClasses/Task.h"
class Task7 : public Task {

private:

	bool negativeCycle = false; //���� ��� ������� �������������� �����

	std::vector < std::pair <int, int> > Paths; // ������ ����� ��� �������� �����

	std::vector < std::vector <int> > AllPathsPairs; //������ ����� ����� ����� ������ ������

	std::vector <int> hFunction; //�������� ������� h(Vertex)

public:
	/* ����������� ��������� �����*/
	Task7(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;


	/* �������������� � ������ */
	void Johnson(Graph&); //�������� ��������
	bool BellmanFord(Graph&, std::vector < std::vector <int> >); //�������� ��������-�����
	void Deikstra(Graph&, int); //�������� ��������
};

