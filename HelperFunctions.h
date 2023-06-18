#pragma once
#include "Vector.hpp"
#include "MyString.h"
namespace HelperFunctions
{
	//from github Angeld55
	bool isPrefix(const char* pattern, const char* text);
	//from github Angeld55
	bool searchInText(const char* text, const char* pattern);

	void findCommand(const char* str, char* command);

	bool isNumber(char* str, unsigned startIndex, unsigned endIndex);

	unsigned fromStrToNum(const char* str, unsigned startIndex, unsigned endIndex);

	void getSubstr(const char* source, char* dest, unsigned startIndex, unsigned endIndex);

	void saveMyStringToBinaryFile(std::ofstream& ofs, const MyString& str);

	void readMyStringFromBinaryFile(std::ifstream& ifs, MyString& str);
}



