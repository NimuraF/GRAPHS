#pragma once
class Task {
protected:
	std::string group = "M30-219Bk-21";
	std::string sname = "KIRILL GOSPODINCHIK";

	/* MAP для ключей */
	std::map < std::string, std::string > TaskKeys;

	/* Текущий флаг, характеризующий формат хранимых в файле данных */
	int currentFormat = 0; // 1 - Матрица смежности, 2 - список рёбер, 3 - список смежности

	/* Флаг для определения того, куда выводить информацию */
	bool outputFlag = false; //false - на экран, true - в файл

	/* Текущий путь к файлу для считывания */
	std::string currentPath = "";

	/* Путь к файлу для вывода */
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

	/* Вызов справки */
	void Help();
};

