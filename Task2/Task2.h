#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task2 : public Task
{
private:
	std::vector < std::vector <int> > ConnectionComponents; //������ ��� ���������� ��������� ���������
	std::vector <bool> visited; //������ ���������� ������

public:
	/* ����������� ��������� �����*/
	Task2(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* �������������� � ������ */
	void BFS(Graph&, int); //�������� ������ � ������
	void AllComponents(Graph&); 
};

