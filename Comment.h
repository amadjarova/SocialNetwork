#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"
enum class CommentAction
{
	DOWNVOTE,
	UPVOTE,
	REPLY
};
class Comment
{
	MyString authorFirstName;
	MyString authorLastName;
	MyString commentText;
	unsigned ID;
	Vector<unsigned> usersDownvoteID;
	Vector<unsigned> usersUpvoteID;
	Vector<SharedPtr<Comment>> comments;
	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
public:
	Comment() = default;
	Comment(const MyString _authorFirstName, const MyString& authorLastName, const MyString& content, unsigned _ID);
	void printComment(unsigned nestingLevel) const;
	void comment(const MyString& authorFirstName, const MyString& authorLastName, unsigned& allCommsCount);
	void searchCommentToReply(unsigned _ID, const MyString& authorFirstName, const MyString& authorLastName, bool& foundComment, unsigned& _allCommCount);
	void searchCommToVote(unsigned _ID, bool& commFound, unsigned userID, const CommentAction& voteType);
	void vote(unsigned userID, const CommentAction& voteType);
	friend class Post;
};

