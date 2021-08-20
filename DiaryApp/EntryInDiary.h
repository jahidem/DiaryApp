#pragma once
#include<iostream>
#include <string>
#include"customFunctions.h"
using namespace std;

class EntryInDiary 
{
	string mTitle;
	string mContent;
	string mDate;
	int mId;
	public:
		EntryInDiary() {
			mDate =timeNow();
			mTitle = "";		
		}
		string getmTitle();
		string getmContent();
		int getmId();
		string getmDate();
		void hi();
		void setmTitle(string );
		void setmContent(string);
		void setmId(int);
		void print();
		string getStringId();
};

