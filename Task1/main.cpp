#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "Task1.h"

using namespace std;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "russian");

	try {
		Task1 MyTask(argc, argv);
	}
	catch (MException error) {
		error.getErrorOut();
		cout << "Программа завершает своё исполнение!" << endl;
		return -1;
	}

	//string ap = "tests/matrix_t1_001.txt";
	//Graph MyGraph(ap, 1);
	//MyGraph.adjencyMatrix();
	//cout << endl;
	//MyGraph.edgesList();
	//cout << endl;
	//MyGraph.adjencyList();
	return 15;
}