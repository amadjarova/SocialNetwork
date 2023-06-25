
#include "Comment.h"
#include "HelperFunctions.h"
#include <fstream>
Comment::Comment(const MyString _authorFirstName, const MyString& _authorLastName, const MyString& _content, unsigned _ID) :authorFirstName(_authorFirstName), authorLastName(_authorLastName), commentText(_content), ID(_ID)
{

}

void Comment::printComment(unsigned nestingLevel) const
{
	for (size_t i = 0; i <= nestingLevel; ++i)
	{
		std::cout << "  ";
	}

	std::cout << ">> " << commentText << "{id: " << ID << "} ";
	if (usersUpvoteID.getSize() > 0)
	{
		std::cout << "{upvote: " << usersUpvoteID.getSize() << "} ";
	}
	if (usersDownvoteID.getSize() > 0)
	{
		std::cout << "{downvote: " << usersDownvoteID.getSize() << "} ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		comments[i]->printComment(nestingLevel + 1);
	}
}

void Comment::saveToBinaryFile(std::ofstream& ofs) const
{
	size_t usersDownvoteIDSize = usersDownvoteID.getSize();
	size_t usersUpvoteIDSize = usersUpvoteID.getSize();
	size_t numberOfComments = comments.getSize();

	HelperFunctions::saveMyStringToBinaryFile(ofs, authorFirstName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, authorLastName);
	HelperFunctions::saveMyStringToBinaryFile(ofs, commentText);
	ofs.write((const char*)&ID, sizeof(ID));

	ofs.write((const char*)&usersDownvoteIDSize, sizeof(usersDownvoteIDSize));
	for (size_t i = 0; i < usersDownvoteIDSize; ++i) {
		unsigned currentID = usersDownvoteID[i];
		ofs.write((const char*)&currentID, sizeof(unsigned));
	}

	ofs.write((const char*)&usersUpvoteIDSize, sizeof(usersUpvoteIDSize));
	for (size_t i = 0; i < usersUpvoteIDSize; ++i) {
		unsigned currentID=usersUpvoteID[i];
		ofs.write((const char*)&currentID, sizeof(unsigned));
	}

	ofs.write((const char*)&numberOfComments, sizeof(numberOfComments));

	for (size_t i = 0; i < numberOfComments; ++i) {
		comments[i]->saveToBinaryFile(ofs);
	}

}

void Comment::readFromBinaryFile(std::ifstream& ifs)
{
	size_t usersDownvoteIDSize = 0;
	size_t usersUpvoteIDSize = 0;
	size_t numberOfComments = 0;

	HelperFunctions::readMyStringFromBinaryFile(ifs, authorFirstName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, authorLastName);
	HelperFunctions::readMyStringFromBinaryFile(ifs, commentText);
	ifs.read((char*)&ID, sizeof(ID));

	ifs.read((char*)&usersDownvoteIDSize, sizeof(usersDownvoteIDSize));
	for (size_t i = 0; i < usersDownvoteIDSize; ++i) {
		unsigned _ID;
		ifs.read((char*)&_ID, sizeof(unsigned));
		usersDownvoteID.push_back(_ID);
	}

	ifs.read((char*)&usersUpvoteIDSize, sizeof(usersUpvoteIDSize));
	for (size_t i = 0; i < usersUpvoteIDSize; ++i) {
		unsigned _ID;
		ifs.read((char*)&_ID, sizeof(unsigned));
		usersUpvoteID.push_back(_ID);
	}
	ifs.read((char*)&numberOfComments, sizeof(numberOfComments));

	for (size_t i = 0; i < numberOfComments; ++i)
	{
		SharedPtr<Comment> a(new Comment());
		a->readFromBinaryFile(ifs);
		comments.push_back(std::move(a));
	}

}

void Comment::comment(const MyString& authorFirstName, const MyString& authorLastName, unsigned& allCommsCount)
{
	std::cout << ">Say something: ";
	char commentText[1024];
	std::cin.getline(commentText, 1024);
	SharedPtr<Comment> comm(new Comment(authorFirstName, authorLastName, commentText, allCommsCount));
	comments.push_back(std::move(comm));
	std::cout << "Posted! " << std::endl;
	allCommsCount++;
}

void Comment::searchCommentToReply(unsigned _ID, const MyString& authorFirstName, const MyString& authorLastName, bool& foundComm, unsigned& allCommentsCount)
{
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		if (comments[i]->ID == _ID)
		{
			foundComm = true;
			comments[i]->comment(authorFirstName, authorLastName, allCommentsCount);
			break;
		}
		else
		{
			comments[i]->searchCommentToReply(_ID, authorFirstName, authorLastName, foundComm, allCommentsCount);
		}
		if (foundComm)
		{
			break;
		}
	}
}

void Comment::searchCommToVote(unsigned _ID, bool& commFound, unsigned userID, const CommentAction& voteType)
{
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		if (comments[i]->ID == _ID)
		{
			commFound = true;
			comments[i]->vote(userID, voteType);
			break;
		}
		else
		{
			comments[i]->searchCommToVote(_ID, commFound, userID, voteType);
		}
		if (commFound)
		{
			break;
		}
	}

}

void Comment::vote(unsigned userID, const CommentAction& voteType)
{
	bool IDFound = false;
	for (size_t i = 0; i < usersDownvoteID.getSize(); i++)
	{
		if (usersDownvoteID[i] == userID)
		{
			if (voteType == CommentAction::DOWNVOTE)
			{
				IDFound = true;
				usersDownvoteID.erase(i);
				break;
			}
			else
			{
				IDFound = true;
				usersDownvoteID.erase(i);
				usersUpvoteID.push_back(userID);
				break;
			}
		}

	}
	if (!IDFound)
	{
		for (size_t i = 0; i < usersUpvoteID.getSize(); i++)
		{
			if (usersUpvoteID[i] == userID)
			{
				IDFound = true;
				if (voteType == CommentAction::DOWNVOTE)
				{
					usersUpvoteID.erase(i);
					usersDownvoteID.push_back(userID);
					break;
				}
				else
				{
					usersUpvoteID.erase(i);
					break;
				}
			}
		}
	}
	if (!IDFound)
	{
		if (voteType == CommentAction::UPVOTE)
		{
			usersUpvoteID.push_back(userID);
		}
		else if (voteType == CommentAction::DOWNVOTE)
		{
			usersDownvoteID.push_back(userID);
		}
	}
}