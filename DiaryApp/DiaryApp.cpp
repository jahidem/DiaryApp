// DiaryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
#include<conio.h>
#include "EntryInDiary.h"

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x,int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void ShowConsoleCursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void setFontSize() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 18;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_BOLD;
   // std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    //std::cout << "Font: Consolas, Size: 18\n";
}
void setConsoleDimen() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 800, 600, TRUE); // 800 width, 100 height
}

using namespace std;
int set[] = { 12,7,7 };
char counter = 0;
char key;
void initialScreen();

int main()
{
    EntryInDiary ma; gotoxy(10, 11);
    ma.hi();
   // setConsoleDimen();
    setFontSize();
    
    while (true) {
        ShowConsoleCursor(false);
        initialScreen();
        key = _getch();
        if (key == 72) counter--;
        else if (key == 80) counter++;

        else if (key == '\r') {
            cout << "Menu " << counter + 1 << " is open";
        }
        counter += 3, counter %= 3;
        for(int &x:set) x=7;
        set[counter] = 12;


    }
}

void initialScreen() {
    int u; color(11); char sty = ':';
    gotoxy(0, 0); for (u = 0; u <109; u++) cout<<sty;
    color(7); gotoxy(0, 1); cout << '*'; for (u = 0; u < 39; u++) cout << '\xC4';
    cout << '*'; gotoxy(0, 2); cout <<"\xB3\t\tMy_Diary\t\t\xB3";
    gotoxy(0, 3);cout << '*'; 
    for (u = 0; u < 39; u++) cout << '\xC4';
    cout << '*';
    for(u=4;u<36;u++) gotoxy(40,u),cout<<'\xB0';
    gotoxy(0, 36); 
    color(11); for (u = 0; u <109; u++) cout <<sty;

    gotoxy(10, 6);
    color(set[0]);
    cout << "1. Show List of Entry";

    gotoxy(10, 7);
    color(set[1]);
    cout << "2. Activity Graph";

    gotoxy(10, 8);
    color(set[2]);
    cout << "3. Make New Entry";
    cout << flush;
}