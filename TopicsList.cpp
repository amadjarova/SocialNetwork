#include "TopicsList.h"

void TopicsList::searchTextInTopics(const MyString& text) const
{
	unsigned topicsCount = topics.getSize();
	for (size_t i = 0; i < topicsCount; i++)
	{
		if (HelperFunctions::searchInText(topics[i].getTitle().c_str(), text.c_str()))
		{
			topics[i].printTitleAndID();
		}
	}
}

void TopicsList::createTopic(const MyString& _authorFirstName, const MyString& _authorLastName)
{
	std::cout << "Enter topic title: ";
	char title[1024];
	std::cin.getline(title, 1024);
	std::cout << std::endl << "Enter topic description: ";
	char description[1024];
	std::cin.getline(description, 1024);
	Topic topic(title, _authorFirstName, _authorLastName, description, topics.getSize());
	topics.push_back(std::move(topic));
	std::cout << "Success!" << std::endl;
}

void TopicsList::saveToBinaryFile(std::ofstream& ofs) const
{
	unsigned topicsCount = topics.getSize();
	ofs.write((const char*)&topicsCount, sizeof(unsigned));
	for (size_t i = 0; i < topicsCount; i++)
	{
		topics[i].saveToBinaryFile(ofs);
	}
}

void TopicsList::readFromBinaryFile(std::ifstream& ifs)
{
	unsigned topicsCount = 0;
	ifs.read((char*)&topicsCount, sizeof(unsigned));
	for (size_t i = 0; i < topicsCount; i++)
	{
		Topic current;
		current.readFromBinaryFile(ifs);
		topics.push_back(std::move(current));
	}
}

unsigned TopicsList::findTopicIndex(const MyString& _topicName)
{
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (_topicName == topics[i].getTitle())
			return i;
	}
	//not found
	return topics.getSize();
}