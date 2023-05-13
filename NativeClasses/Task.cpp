#include "pch.h"
#include "Task.h"

std::string Task::getGroup() {
	return this->group;
}

std::string Task::getSName() {
	return this->sname;
}

void Task::Help() {
	std::cout << "Student - " << this->getSName() << std::endl;
	std::cout << "Group - " << this->getGroup() << std::endl;
	std::cout << "Available keys:" << std::endl;
	for (auto& key : this->TaskKeys) {
		std::cout << key.first << " - " << key.second << std::endl;
	}
}

int Task::getCurrentFormat() {
	return this->currentFormat;
}

bool Task::getOutputFlag() {
	return this->outputFlag;
}

std::string Task::getCurrentPath() {
	return this->currentPath;
}

std::string Task::getCurrentOutputPath() {
	return this->currentOutputPath;
}

void Task::setCurrentFormat(int currentFormat) {
	this->currentFormat = currentFormat;
}

void Task::setOutputFlag(bool currentOutputFlag) {
	this->outputFlag = currentOutputFlag;
}

void Task::setCurrentPath(std::string path) {
	this->currentPath = path;
}

void Task::setCurrentOutputPath(std::string path) {
	this->currentOutputPath = path;
}