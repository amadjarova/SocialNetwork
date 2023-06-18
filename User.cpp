#include "User.h"
const MyString& User::getPassword() const
{
	return password;
}

const MyString& User::getFirstName() const
{
	return firstName;
}

const MyString& User::getLastName() const
{
	return lastName;
}

User::User(const MyString& _firstName,const MyString& _lastName,const MyString& _password, unsigned indexInArr): firstName(_firstName), lastName(_lastName), password(_password), ID(indexInArr)
{
	
}

void User::saveToBinaryFile(std::ofstream& ofs) const
{
	HelperFunctions::saveMyStringToBinaryFile(ofs, firstName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, lastName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, password);
	ofs.write((const char*)&ID, sizeof(unsigned));
	ofs.write((const char*)&points, sizeof(unsigned));
}

void User::readFromBinaryFile(std::ifstream& ifs)
{
	HelperFunctions::readMyStringFromBinaryFile(ifs, firstName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, lastName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, password);
	ifs.read((char*)&ID, sizeof(unsigned));
	ifs.read((char*)&points, sizeof(unsigned));
}

void User::printInfo() const
{
	std::cout << ">" << firstName << " " << lastName << ", having " << points << " points. " << std::endl;

}