#pragma once
#include "Vector.hpp"
#include "User.h"
#include "HelperFunctions.h"
#include "TopicsList.h"
#include "Topic.h"

const unsigned ARR_LEN = 1024;

enum class Status
{
	RUNNING,
	EXIT,
	LOGOUT
};

class SocialNetwork
{
	Vector<User> users;
	TopicsList list;
	
	bool isPasswordTaken(const MyString& _password) const;
	Status runCommands(unsigned userIndex);
	void readFromBinaryFile();
	void saveToBinaryFile()const;
public:
	SocialNetwork();
	~SocialNetwork();
	void signup();
	Status login();

};

