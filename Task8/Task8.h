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

public:
	/* ����������� ��������� �����*/
	Task8(int, char**);
	void keys() override;
	bool parseFlags(int argc, char** argv) override;

	/* ������� ������ � ������ */
	void findPath(CMap&); //����� ����
	int getRange(CMap&, std::pair <int, int>, std::pair <int, int>); //���������� � ������� ���������� ����� ���������


	/* ��������� */
	int hManhatton(std::pair <int, int>, std::pair <int, int>); //������������� ����������
};

