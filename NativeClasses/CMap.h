#pragma once
class CMap {

private:

	/* ����� � ���� ���������� ������� (�������) */
	std::vector < std::vector <int> > MAP;



	bool parseMap(std::string); //������ �����

public:
	CMap(std::string);

	/* ������� ����� (������� ���������) �� ������ */
	std::vector < std::vector <int> >& getMap(); 

	/* �����������, ������������ ������ ������� � ����� */
	int Indexator(int, int);

	/* �������, ������������ ������ ���� �������� ������ */
	std::vector < std::pair <int, int > > neighbors(std::pair <int, int>);
};

