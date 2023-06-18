#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "Topic.h"
class User
{
	MyString firstName;
	MyString lastName;
	MyString password;
	unsigned ID;
	unsigned points=0;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
	const MyString& getPassword() const;
public:
	User(const MyString& _firstName,const MyString& _lastName,const MyString& _password, unsigned indexInArr);
	User() = default;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	void printInfo() const;
	friend class SocialNetwork;
	friend class Comment;
};

