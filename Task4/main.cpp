#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "Task4.h"

using namespace std;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "russian");

	try {
		Task4 MyTask(argc, argv);
	}
	catch (MException error) {
		error.getErrorOut();
		cout << "Программа завершает своё исполнение!" << endl;
		return -1;
	}
	return 15;
}