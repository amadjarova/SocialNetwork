#include "SocialNetwork.h"
#include <fstream>
bool SocialNetwork::isPasswordTaken(const MyString& _password) const
{
	unsigned usersCount = users.getSize();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (_password == users[i].getPassword())
		{
			return true;
		}
	}
	return false;
}

void SocialNetwork::signup()
{
	std::cout << "Enter first name: ";
	MyString firstName;
	std::cin >> firstName;
	std::cout << std::endl << "Enter last name: ";
	MyString lastName;
	std::cin >> lastName;
	std::cout << std::endl << "Enter password: ";
	MyString password;
	while (true)
	{
		std::cin >> password;
		if (isPasswordTaken(password))
		{
			std::cout << "This password is taken. Please enter new password." << std::endl;
		}
		else
		{
			break;
		}
	}
	User user(firstName, lastName, password, users.getSize());
	users.push_back(std::move(user));
	std::cout << "Success! " << std::endl;
}

Status SocialNetwork::login()
{
	while (true)
	{
		std::cout << "Name: ";
		MyString name;
		std::cin >> name;
		std::cout << std::endl << "Password: ";
		MyString password;
		std::cin >> password;
		unsigned usersCount = users.getSize();
		for (size_t i = 0; i < usersCount; i++)
		{
			if (users[i].getFirstName() == name)
			{
				if (users[i].getPassword() == password)
				{
					std::cout << "Welcome back, " << users[i].getFirstName() << " " << users[i].getLastName() << "!" << std::endl;

					return runCommands(i);
				}
			}
		}
		std::cout << "Invalid name or password. Please try again!" << std::endl;
	}
}

void SocialNetwork::saveToBinaryFile() const
{
	std::ofstream ofs("file.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!ofs.is_open())
	{
		throw "Error with opening the file.";
	}
	unsigned vectSize = users.getSize();
	ofs.write((const char*)&vectSize, sizeof(unsigned));
	for (size_t i = 0; i < vectSize; i++)
	{
		users[i].saveToBinaryFile(ofs);
	}
	list.saveToBinaryFile(ofs);
	ofs.close();
}

void SocialNetwork::readFromBinaryFile()
{
	std::ifstream ifs("file.dat", std::ios::in | std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}
	unsigned vectSize = 0;
	ifs.read((char*)&vectSize, sizeof(unsigned));
	for (size_t i = 0; i < vectSize; i++)
	{
		User current;
		current.readFromBinaryFile(ifs);
		users.push_back(std::move(current));
	}
	list.readFromBinaryFile(ifs);
	ifs.close();
}

Status SocialNetwork::openPost(unsigned userIndex, unsigned topicIndex, unsigned postIndex) 
{
	char buff[ARR_LEN];
	std::cout << "Q: " << list.topics[topicIndex].posts[postIndex].getTitle() << std::endl;
	while (true)
	{
		std::cin.getline(buff, ARR_LEN);
		char command[ARR_LEN];
		HelperFunctions::findCommand(buff, command);
		if (strcmp(command, ">p_close") == 0)
		{
			std::cout << "You just left \"" << list.topics[topicIndex].posts[postIndex].getTitle() << "\"!" << std::endl;
			return Status::RUNNING;
		}
		else if (strcmp(command, ">comments") == 0)
		{
			list.topics[topicIndex].posts[postIndex].printComments();
		}
		else if (strcmp(command, ">comment") == 0)
		{
			list.topics[topicIndex].posts[postIndex].comment(users[userIndex].getFirstName(), users[userIndex].getLastName());
			users[userIndex].points++;
		}
		else if (strcmp(command, ">reply") == 0 || strcmp(command, ">upvote") == 0 || strcmp(command, ">downvote") == 0)
		{
			if (!HelperFunctions::isNumber(buff, strlen(command) + 1, strlen(buff) - 1))
			{
				throw "The ID must be a number";
			}
			unsigned commentID = HelperFunctions::fromStrToNum(buff, strlen(command) + 1, strlen(buff) - 1);
			bool commFound = false;
			if (strcmp(command, ">reply") == 0)
			{
				list.topics[topicIndex].posts[postIndex].reply(commentID, commFound, users[userIndex].getFirstName(), users[userIndex].getLastName());
			}
			else if (strcmp(command, ">downvote") == 0)
			{
				list.topics[topicIndex].posts[postIndex].vote(commentID, CommentAction::DOWNVOTE, userIndex, commFound);
			}
			else
			{
				list.topics[topicIndex].posts[postIndex].vote(commentID, CommentAction::UPVOTE, userIndex, commFound);
			}
			if (!commFound)
			{
				throw "Comment not found.";
			}
		}
		else if (strcmp(command, ">exit") == 0)
		{
			return Status::EXIT;
		}
		else if (strcmp(command, ">logout") == 0)
		{
			std::cout << "Goodbye, " << users[userIndex].getFirstName() << " " << users[userIndex].getLastName() << "!" << std::endl;
			return Status::LOGOUT;
		}
		else
		{
			std::cout << "Invalid command." << std::endl;
		}
	}

}

Status SocialNetwork::openTopic(unsigned userIndex, unsigned topicIndex)
{
	char buff[ARR_LEN];
	std::cout << "Welcome to \"" << list.topics[topicIndex].getTitle() << "\"" << std::endl;
	while (true)
	{
		std::cin.getline(buff, ARR_LEN);
		char command[ARR_LEN];
		HelperFunctions::findCommand(buff, command);
		if (strcmp(command, ">list") == 0)
		{
			list.topics[topicIndex].printAllPostsTitleAndID();
		}
		else if (strcmp(command, ">post") == 0)
		{

			list.topics[topicIndex].post();

		}
		else if (strcmp(command, ">p_open") == 0)
		{
			unsigned postIndex;
			if (HelperFunctions::isNumber(buff, strlen(command) + 1, strlen(buff) - 1))
			{
				postIndex = HelperFunctions::fromStrToNum(buff, strlen(command) + 1, strlen(buff) - 1);
			}
			else
			{
				char postTitle[ARR_LEN];
				HelperFunctions::getSubstr(buff, postTitle, strlen(command) + 1, strlen(buff) - 1);
				postIndex = list.topics[topicIndex].findPostIndex(postTitle);
			}
			if (postIndex >= list.topics[topicIndex].posts.getSize())
			{
				std::cout << "There is no such post." << std::endl;
				continue;
			}
			switch (openPost(userIndex, topicIndex, postIndex))
			{
				case Status::LOGOUT: return Status::LOGOUT;break;
				case Status::EXIT: return Status::EXIT;break;
			}
		}
		else if (strcmp(command, ">quit") == 0)
		{
			std::cout << "You just left topic \"" << list.topics[topicIndex].getTitle() << "\"!" << std::endl;
			return Status::RUNNING;
		}
		else if (strcmp(command, ">exit") == 0)
		{
			return Status::EXIT;
		}
		else if (strcmp(command, ">logout") == 0)
		{
			std::cout << "Goodbye, " << users[userIndex].getFirstName() << " " << users[userIndex].getLastName() << "!" << std::endl;
			return Status::LOGOUT;
		}
		else
		{
			std::cout << "Invalid command." << std::endl;
		}
	}

}

Status SocialNetwork::runCommands(unsigned userIndex)
{
	std::cin.ignore();
	while (true)
	{
		char buff[ARR_LEN];
		std::cin.getline(buff, ARR_LEN);
		char command[ARR_LEN];
		HelperFunctions::findCommand(buff, command);

		if (strcmp(command, ">open") == 0)
		{
			unsigned topicIndex;
			if (HelperFunctions::isNumber(buff, strlen(command) + 1, strlen(buff) - 1))
			{
				topicIndex = HelperFunctions::fromStrToNum(buff, strlen(command) + 1, strlen(buff) - 1);
			}
			else
			{
				char topicTitle[ARR_LEN];
				HelperFunctions::getSubstr(buff, topicTitle, strlen(command) + 1, strlen(buff) - 1);
				topicIndex = list.findTopicIndex(topicTitle);
			}
			if (topicIndex >= list.topics.getSize())
			{
				std::cout << "There is no such topic." << std::endl;
				continue;
			}
			switch (openTopic(userIndex, topicIndex))
			{
				case Status::LOGOUT: return Status::LOGOUT;
				case Status::EXIT: return Status::EXIT;
			}

		}
		else if (strcmp(command, ">create") == 0)
		{
			list.createTopic(users[userIndex].getFirstName(), users[userIndex].getLastName());
		}
		else if (strcmp(command, ">search") == 0)
		{
			char searchedText[ARR_LEN];
			HelperFunctions::getSubstr(buff, searchedText, strlen(command) + 1, strlen(buff) - 1);
			list.searchTextInTopics(searchedText);
		}
		else if (strcmp(command, ">whoami") == 0)
		{
			users[userIndex].printInfo();
		}
		else if (strcmp(command, ">about") == 0)
		{
			if (!HelperFunctions::isNumber(buff, strlen(command) + 1, strlen(buff) - 1))
			{
				throw "The ID must be a number";
			}
			unsigned topicIndex = HelperFunctions::fromStrToNum(buff, strlen(command) + 1, strlen(buff) - 1);
			if (topicIndex >= list.topics.getSize())
			{
				throw "ID not found";
			}
			list.topics[topicIndex].printInfo();
		}
		else if (strcmp(command, ">exit") == 0)
		{
			return Status::EXIT;
		}
		else if (strcmp(command, ">logout") == 0)
		{
			std::cout << "Goodbye, " << users[userIndex].getFirstName() << " " << users[userIndex].getLastName() << "!" << std::endl;
			return Status::LOGOUT;
		}
		else
		{
			std::cout << "Invalid command." << std::endl;
		}

	}
}

SocialNetwork::SocialNetwork()
{
	readFromBinaryFile();
}

SocialNetwork::~SocialNetwork()
{
	saveToBinaryFile();
}
