#pragma once
class Task {
protected:
	std::string group = "M30-219Bk-21";
	std::string sname = "KIRILL GOSPODINCHIK";

	/* MAP ��� ������ */
	std::map < std::string, std::string > TaskKeys;

	/* ������� ����, ��������������� ������ �������� � ����� ������ */
	int currentFormat = 0; // 1 - ������� ���������, 2 - ������ ����, 3 - ������ ���������

	/* ���� ��� ����������� ����, ���� �������� ���������� */
	bool outputFlag = false; //false - �� �����, true - � ����

	/* ������� ���� � ����� ��� ���������� */
	std::string currentPath = "";

	/* ���� � ����� ��� ������ */
	std::string currentOutputPath = "";
	
public:
	std::string getGroup();
	std::string getSName();

	int getCurrentFormat();
	bool getOutputFlag();
	std::string getCurrentPath();
	std::string getCurrentOutputPath();

	void setCurrentFormat(int);
	void setOutputFlag(bool);
	void setCurrentPath(std::string);
	void setCurrentOutputPath(std::string);


	virtual bool parseFlags(int argc, char** argv) = 0;
	virtual void keys() = 0;

	/* ����� ������� */
	void Help();
};

