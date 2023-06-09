#pragma once
#include "../NativeClasses/CMap.h"
#include "../NativeClasses/Task.h"

class Task8 : public Task {

	struct Cell {
		int i;
		int j;
	};

	std::pair <int, int> beginCell; //��������� ������� (� ���� ������ | �������) � ������� ���������
	std::pair <int, int> endCell; //�������� ������� (� ���� ������ | �������) � ������� ���������

	double visistedPercent; //������� ���������� ������

public:
	/* ����������� ��������� �����*/
	Task8(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;
	void logOutput(std::ostream&, std::vector < std::pair <int, int> > &, int, std::string); //������� ��� ������ � ���� / �� �����

	/* ������� ������ � ������ */
	void findPath(CMap&, int); //����� ����
	int getRange(CMap&, std::pair <int, int>, std::pair <int, int>); //���������� � ������� ���������� ����� ���������


	/* ��������� */
	int hManhatton(std::pair <int, int>, std::pair <int, int>); //������������� ����������
	int hChebyshev(std::pair <int, int>, std::pair <int, int>); //�������� ����������
	int hEvklid(std::pair <int, int>, std::pair <int, int>); //��������� ����������
};

