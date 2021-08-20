#include "EntryInDiary.h"

string EntryInDiary::getmTitle()
{
	while (int(mTitle.size()) < 26) mTitle += " ";
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

string EntryInDiary::getmDate()
{
	return mDate;
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
	mTitle = "";
	for (char x : content) {
		if (mTitle.size() == 26) break;
		 mTitle += x;
	}
}

void EntryInDiary::setmId(int id)
{
	this->mId = id;
}

void EntryInDiary::print()
{
	cout << mTitle << '\n';
}

string EntryInDiary::getStringId()
{
	string tm = to_string(mId);
	while (tm.size() < 6) tm="0" + tm;
	return tm;
}
