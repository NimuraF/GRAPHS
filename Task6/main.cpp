#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "Task6.h"

using namespace std;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "russian");

	try {
		Task6 MyTask(argc, argv);
	}
	catch (MException error) {
		error.getErrorOut();
		cout << "��������� ��������� ��� ����������!" << endl;
		return -1;
	}
	return 15;
}