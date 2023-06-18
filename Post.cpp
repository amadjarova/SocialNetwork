#include "Post.h"

void Post::printTitleAndID() const
{
	std::cout << ">>" << title << " {id: " << ID << " }" << std::endl;
}

const MyString& Post::getTitle() const
{
	return title;
}

unsigned Post::getID() const
{
	return ID;
}
 
void Post::comment(const MyString& authorFirstName, const MyString& authorLastName)
{
	std::cout << ">Say something: ";
	char commentText[1024];
	std::cin.getline(commentText, 1024);
	Comment comm(authorFirstName, authorLastName, commentText, allCommCount);
	comments.push_back(comm);
	std::cout << "Posted! " << std::endl;
	allCommCount++;
}

Post::Post(const MyString& _title, const MyString& _content, unsigned _ID) :title(_title), content(_content), ID(_ID)
{

}

void Post::saveToBinaryFile(std::ofstream& ofs) const
{
	HelperFunctions::saveMyStringToBinaryFile(ofs, title);
	HelperFunctions::saveMyStringToBinaryFile(ofs, content);
	ofs.write((const char*)&ID, sizeof(unsigned));
	ofs.write((const char*)&allCommCount, sizeof(unsigned));
	unsigned commentsCount = comments.getSize();
	ofs.write((const char*)&commentsCount, sizeof(unsigned));
	for (size_t i = 0; i < commentsCount; i++)
	{
		comments[i].saveToBinaryFile(ofs);
	}
}

void Post::readFromBinaryFile(std::ifstream& ifs)
{
	HelperFunctions::readMyStringFromBinaryFile(ifs, title);
	HelperFunctions::readMyStringFromBinaryFile(ifs, content);
	ifs.read((char*)&ID, sizeof(unsigned));
	ifs.read((char*)&allCommCount, sizeof(unsigned));
	unsigned commentsCount = 0;
	ifs.read((char*)&commentsCount, sizeof(unsigned));
	for (size_t i = 0; i < commentsCount; i++)
	{
		Comment current;
		current.readFromBinaryFile(ifs);
		comments.push_back(current);
	}
}

void Post::printComments() const
{
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		comments[i].printComment(0);
	}
}

void Post::reply(unsigned _ID, bool& found, const MyString& authorFirstName, const MyString& authorLastName)
{
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		if (comments[i].ID == _ID)
		{
			comments[i].comment(authorFirstName, authorLastName,allCommCount);
			found = true;
			break;
		}
		else
		{
			comments[i].searchCommentToReply(_ID, authorFirstName, authorLastName, found, allCommCount);
		}
		if (found)
		{
			break;
		}
	}
}

void Post::vote(unsigned _ID, const CommentAction& voteType, unsigned userID, bool& commFound)
{
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			if (comments[i].ID == _ID)
			{
				comments[i].vote(userID, voteType);
				commFound = true;
				break;
			}
			else
			{
				comments[i].searchCommToVote(_ID, commFound, userID, voteType);
			}
			if (commFound)
			{
				break;
			}
		}
}