#pragma once
#include "MyString.h"
#include "Post.h"
#include "Vector.hpp"
#include "HelperFunctions.h"
#include <vector>
class Topic
{
	MyString title;
	MyString creatorFirstName;
	MyString creatorLastName;
	MyString description;
	unsigned ID;
	Vector<Post> posts;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

public:
	Topic() = default;
	Topic(const MyString& _title, const MyString& _creatorFirstName,const MyString& _creatorLastName, const MyString& _description, unsigned indexInArr);
	void printTitleAndID() const;
	const MyString& getTitle() const;
	unsigned getID() const;
	void printAllPostsTitleAndID() const;
	unsigned findPostIndex(const MyString& postTitle);
	void post();
	void printInfo()const;
	friend class TopicsList;
	friend class SocialNetwork;
};

