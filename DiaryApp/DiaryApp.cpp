// DiaryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
#include<conio.h>
#include "EntryInDiary.h"
#include "AllEntrySingleton.h"

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
    cfi.dwFontSize.Y = 20;                  // Height
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

    MoveWindow(console, r.left, r.top, 800, 700, TRUE); // 800 width, 100 height
}

using namespace std;
int set[] = { 12,7,7,7 };
char counter = 0;
char key;
void initialScreen();
void showListEntry();
int main()
{  
   
    setFontSize();
    //gotoxy(0, 37); cout << AllEntrySingleton::get().ga();
    while (true) {
        setConsoleDimen();
        ShowConsoleCursor(false);
        initialScreen();
        key = _getch();
        if (key == 72) counter--;
        else if (key == 80) counter++;

        else if (key == '\r') {
            if (counter == 3) exit(0);
           else if (counter == 0) showListEntry();
            else cout << "Menu " << counter + 1 << " is open";
        }
        counter += 4, counter %= 4;
        for (int& x : set) x = 7;
        set[counter] = 12;

    }
}
void showListEntry() {
    int move = 5, listCounter = 0;
    vector<EntryInDiary> lis;
    lis = AllEntrySingleton::get().getEntryLibrary();
    for (move = 0; move < 30 && listCounter < int(lis.size()); move += 4) {
        color(8); gotoxy(42, move + 1);
        cout << "\xDA";
        for (int u = 0; u < 32; u++) cout << '\xC4';
        cout << '\xBF';
        gotoxy(42, move + 2); cout << '\xBA', color(7);
        cout << "Title: " << lis[listCounter].getmTitle();


        color(8), gotoxy(42, move + 3); cout << '\xBA', color(7);

        cout << lis[listCounter].getmContent();
        color(8), gotoxy(75, move + 2); cout << '\xBA';
        gotoxy(75, move + 3); cout << '\xBA';

        gotoxy(42, move + 4); cout << '\xC0';
        for (int u = 0; u < 32; u++) cout << '\xC4';
        cout << '\xD9'; color(7);
        listCounter++;
    }
}
void initialScreen() {
    int u; color(11); char sty = ':';
    gotoxy(0, 0); for (u = 0; u <109; u++) cout<<sty;
    color(7); gotoxy(0, 1); cout << '*'; for (u = 0; u < 39; u++) cout << '\xC4';
    cout << '*'; gotoxy(0, 2); 
    cout << "\xB3\t\t";
    color(6); cout << " My_Diary "; color(7);
    cout<<"\t\t\xB3";
    gotoxy(0, 3);cout << '*'; 
    for (u = 0; u < 39; u++) cout << '\xC4';
    cout << '*';
    color(14);
    for (u = 4; u < 33; u++) gotoxy(40, u), cout << '\xB0';
    color(7);

    gotoxy(10, 6);
    color(set[0]);
    cout << "Show List of Entry";

    gotoxy(10, 8);
    color(set[1]);
    cout << "Make New Entry";

    gotoxy(10, 10);
    color(set[2]);
    cout << "Settings";

    gotoxy(10, 12);
    color(set[3]);
    cout << "Exit";
    
}