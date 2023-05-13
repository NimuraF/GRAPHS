#include "pch.h"
#include "parseOut.h"
#include "Graph.h"
#include "MException.h"

std::string parseOut::CountSpaces(int number) {
	int N = number;
	if (N > 0) {
		int i = 0;
		while (N > 0) {
			N /= 10;
			i++;
		}

		std::string Result(3 - i, ' ');
		return Result;
	}
	else {
		std::string Result("  ");
		return Result;
	}
}