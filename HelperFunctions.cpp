#include "HelperFunctions.h"
#include <fstream>
bool HelperFunctions::isPrefix(const char* pattern, const char* text)
{
	while (*text != '\0' && *pattern != '\0')
	{
		if (*text != *pattern)
			return false;
		text++;
		pattern++;
	}
	return *pattern == '\0';
}

bool HelperFunctions::searchInText(const char* text, const char* pattern)
{
	size_t textLen = strlen(text);
	size_t patternLen = strlen(pattern);
	while (patternLen <= textLen)
	{
		if (isPrefix(pattern, text))
			return true;
		text++; //подминаваме първия символ
		textLen--;
	}
	return false;
}

void HelperFunctions::findCommand(const char* str, char* command)
{
	unsigned commandIndex = 0;
	while (*str != '\0' && *str != ' ')
	{
		command[commandIndex++] = *str;
		str++;
	}
	command[commandIndex] = '\0';
}

bool HelperFunctions::isNumber(char* str, unsigned startIndex, unsigned endIndex)
{
	for (size_t i = startIndex; i <= endIndex; i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return false;
		}
	}
	return true;
}

unsigned HelperFunctions::fromStrToNum(const char* str, unsigned startIndex, unsigned endIndex)
{
	unsigned num = 0;
	for (size_t i = startIndex; i <= endIndex; i++)
	{
		num += str[i] - '0';
		num *= 10;
	}
	num /= 10;
	return num;
}

void HelperFunctions::getSubstr(const char* source, char* dest, unsigned startIndex, unsigned endIndex)
{
	unsigned destIndex = 0;
	for (size_t i = startIndex; i <= endIndex; i++)
	{
		dest[destIndex++] = source[i];
	}
	dest[destIndex] = '\0';
}

void HelperFunctions::saveMyStringToBinaryFile(std::ofstream& ofs, const MyString& str)
{
	unsigned size = str.length();
	ofs.write((const char*)&size, sizeof(unsigned));
	ofs.write(str.c_str(), size);
}

void HelperFunctions::readMyStringFromBinaryFile(std::ifstream& ifs, MyString& str)
{
	unsigned size=0;
	ifs.read((char*)&size, sizeof(unsigned));
	char* data = new char[size + 1];
	ifs.read(data, size);
	data[size] = '\0';
	str = MyString(data);
	delete[] data;
}