#pragma once
#include "../NativeClasses/Task.h"
#include "../NativeClasses/Graph.h"

class Task2 : public Task
{
private:
	std::vector < std::vector <int> > ConnectionComponents; //������ ��� ���������� ��������� ���������
	std::vector <bool> visited; //������ ���������� ������

	std::vector < std::vector <int> > AJListWWInvert; //��������������� ���� � ���� ������ ��������� ��� �����

	std::vector <char> used;
	std::vector <int> order; //������ ������ � ������� ��������
	std::vector <int> component; //����� ��� ������� ���������� ������� ���������

	std::vector < std::vector <int> > StrongConnectionComponents; //������ ��� �������� ��������� ������� ���������

public:
	/* ����������� ��������� �����*/
	Task2(int argc, char** argv);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* �������������� � ������ */
	void FindConnectionComponents(Graph&, int); //�������� ������ � ������
	void AllComponents(Graph&); //�������, ��� ����������� ���� ���������
	void dfs1(std::vector < std::vector <int> > &, int); //�������� ������ � �������
	void dfs2(std::vector < std::vector <int> > &, int); //�������� ������ � ������� ���������������� �����
	void FindStrongComponents(Graph&);
};

