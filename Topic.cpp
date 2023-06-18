#include "Topic.h"

Topic::Topic(const MyString& _title,const MyString& _creatorFirstName,const MyString& _creatorLastName,const MyString& _description, unsigned indexInArr):title(_title), creatorFirstName(_creatorFirstName), creatorLastName(_creatorLastName), description(_description), ID(indexInArr), posts(4)
{
	
}

void Topic::printTitleAndID() const
{
	std::cout << "-" << title << "{id:" << ID << "}\n";
}

const MyString& Topic::getTitle() const
{
	return title;
}

void Topic::printAllPostsTitleAndID() const
{
	for (size_t i = 0; i < posts.getSize(); i++)
	{
		posts[i].printTitleAndID();
	}
}

unsigned Topic::getID() const
{
	return ID;
}

void Topic::saveToBinaryFile(std::ofstream& ofs) const
{
	HelperFunctions::saveMyStringToBinaryFile(ofs, title);
	HelperFunctions::saveMyStringToBinaryFile(ofs, creatorFirstName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, creatorLastName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, description);
	ofs.write((const char*)&ID, sizeof(unsigned));
	unsigned postsCount = posts.getSize();
	ofs.write((const char*)&postsCount, sizeof(unsigned));
	for (size_t i = 0; i < postsCount; i++)
	{
		posts[i].saveToBinaryFile(ofs);
	}
}

void Topic::readFromBinaryFile(std::ifstream& ifs)
{
	HelperFunctions::readMyStringFromBinaryFile(ifs, title);
	HelperFunctions::readMyStringFromBinaryFile(ifs, creatorFirstName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, creatorLastName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, description);
	ifs.read((char*)&ID, sizeof(unsigned));
	unsigned postsCount = 0;
	ifs.read((char*)&postsCount, sizeof(unsigned));
	for (size_t i = 0; i < postsCount; i++)
	{
		Post current;
		current.readFromBinaryFile(ifs);
		posts.push_back(current);
	}
}

unsigned Topic::findPostIndex(const MyString& postTitle)
{
	for (size_t i = 0; i < posts.getSize(); i++)
	{
		if (posts[i].getTitle() == postTitle)
			return i;
	}
	//not found
	return posts.getSize();
}

void Topic::post()
{
	std::cout << "Enter post title: ";
	char postTitle[1024];
	std::cin.getline(postTitle, 1024);
	std::cout << std::endl << "Enter post content: ";
	char postContent[1024];
	std::cin.getline(postContent, 1024);
	unsigned index = posts.getSize();

	Post post(postTitle, postContent, index);
	posts.push_back(std::move(post));
	std::cout << "Success!"<<std::endl;
}

void Topic::printInfo()const
{
	std::cout << ">>Name: " << title << std::endl;
	std::cout << ">>Description: " << description << std::endl;
	std::cout << ">>Created by: " << creatorFirstName << " " << creatorLastName << std::endl;
	std::cout << ">>Questions asked: " << posts.getSize() << std::endl;
}