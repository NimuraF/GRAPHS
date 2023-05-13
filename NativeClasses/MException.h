#pragma once
class MException 
{
private:
	std::string errorOut;

public:
	MException(std::string);
	void getErrorOut();
};