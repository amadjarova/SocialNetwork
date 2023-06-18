#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Comment.h"
#include "HelperFunctions.h"
#include <fstream>
class Post
{
	MyString title;
	MyString content;
	unsigned ID;
	Vector<Comment> comments;
	unsigned allCommCount = 0; //used for comments ID
	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
public:
	Post() = default;
	Post(const MyString& _title, const MyString& _content,unsigned _ID);
	void printTitleAndID() const;
	const MyString& getTitle() const;
	unsigned getID() const;
	void comment(const MyString& userFirstName, const MyString& userSecondName);
	void printComments() const;
	void reply(unsigned ID, bool& found, const MyString& authorFirstName, const MyString& authorLastName);
	void vote(unsigned _ID, const CommentAction& voteType, unsigned userID, bool& commFound);
	friend class Topic;
};

