#pragma once
#include<iostream>
#include <string>

using namespace std;

class EntryInDiary 
{
	string mTitle;
	string mContent;
	int mId;
	public:
		string getmTitle();
		string getmContent();
		int getmId();
		void hi();
		void setmTitle(string );
		void setmContent(string);
		void setmId(int);
		void print();
};

