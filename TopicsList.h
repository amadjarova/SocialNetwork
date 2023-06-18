#pragma once
#include "Vector.hpp"
#include "Topic.h"
#include "HelperFunctions.h"
#include "MyString.h"
#include "Post.h"
class TopicsList
{
	Vector<Topic> topics;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
public:
	void searchTextInTopics(const MyString& _text) const;
	void createTopic(const MyString& _authorFirstName, const MyString& _authorLastName);
	unsigned findTopicIndex(const MyString& _topicName);
	friend class SocialNetwork;
};

