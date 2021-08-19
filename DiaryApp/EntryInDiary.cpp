#include "EntryInDiary.h"

string EntryInDiary::getmTitle()
{
	return mTitle;
}

string EntryInDiary::getmContent()
{
	return mContent;
}

int EntryInDiary::getmId()
{
	return mId;
}

void EntryInDiary::hi()
{
	cout<<" ";
}

void EntryInDiary::setmTitle(string title)
{
	this->mTitle = title;
}

void EntryInDiary::setmContent(string content)
{
	this->mContent = content;
}

void EntryInDiary::setmId(int id)
{
	this->mId = id;
}

void EntryInDiary::print()
{
	cout << mTitle << '\n';
}
