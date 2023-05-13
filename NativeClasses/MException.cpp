#include "pch.h"
#include "MException.h"

MException::MException(std::string errorOut) {
	this->errorOut = errorOut;
}

void MException::getErrorOut() {
	std::cout << this->errorOut << std::endl;
}
