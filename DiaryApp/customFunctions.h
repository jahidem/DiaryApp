#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include<windows.h>
#include<conio.h>
using namespace std;

string timeNow();
void setConsoleDimen(); // set the height and width of console
void setFontSize(); // set the font family,size.weight etc
void ShowConsoleCursor(bool visible);   // to show or hide console cursor
void color(int color);  // just picks a color for output on terminal
void gotoxy(int x, int y);  // moves the cursor to the position