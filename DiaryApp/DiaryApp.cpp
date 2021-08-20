// DiaryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
#include<conio.h>
#include "EntryInDiary.h"   // this represnts single entry on diary
#include "AllEntrySingleton.h"  // Holds all the entryInDiary remains 
         //throughout the liftime of the application
#include <map>
#include"customFunctions.h"
using namespace std;
int set[] = { 12,7,7,7 };   // just some numbers for colors of the Menu
char counter = 0;   // indicates which item of the Menu is active
char key;   // takes keyboard inputs
void clrWholeScreen();
void initialScreen();   // draws the initial UI
void showListEntry();   // shows list on the right panel
void clearRightPanel(); // clear al content int the right panel 
void instructionToNav(int); // instructons on the lower left to navigate
void newEntryWindow();

int main()
{  
   
    setFontSize();
    //gotoxy(0, 37); cout << AllEntrySingleton::get().ga();
    while (true) {
        setConsoleDimen();
        ShowConsoleCursor(false);
        initialScreen();
        color(8); instructionToNav(1);
        key = _getch();
        if (key == 72) counter--;
        else if (key == 80) counter++;

        else if (key == '\r') {
            if (counter == 3) exit(0);
            else if (counter == 0) showListEntry();
            else if (counter == 1) {
                newEntryWindow();
                ShowConsoleCursor(false);
                clrWholeScreen();
            }
            else cout << "Menu " << counter + 1 << " is open";
        }
        counter += 4, counter %= 4;
        for (int& x : set) x = 7;
        set[counter] = 12;

    }
}
void showListEntry() {
    int  listCounter = 0,nowShowing=0;
    vector<EntryInDiary> lis;
    lis = AllEntrySingleton::get().getEntryLibrary();
    int const SZ = int(lis.size());
    while (true) {
        int nwGo = listCounter,move;
        map<int, int> mp;
        color(8), instructionToNav(2); 
        for (move = 1,nwGo=listCounter; move < 30&&move<4*SZ; move += 4,nwGo++) {
            int colorCode = 8,textColor=8; nwGo %= SZ; mp[nwGo] = 1;
            //for (int u = 2; u < 4; u++) {//works fine for refreshing but casuses gliching
                //need to be fixed
               // gotoxy(43, move + u); for (int v = 43; v < 75; v++) cout << ' ';
            //}
            

            if (nowShowing == nwGo) colorCode = 12,textColor=7;
            color(colorCode); gotoxy(42, move + 1);
            //cout << "\xDA";
            //for (int u = 0; u < 32; u++) cout << '\xC4';
            //cout << '\xBF';

            cout << '\xBA', color(textColor);
            cout << lis[nwGo].getmDate() << "             ID:" << lis[nwGo].getStringId();
            color(colorCode), cout<< '\xBA';
            gotoxy(42, move + 2); cout << '\xBA';
            


            gotoxy(42, move + 3); cout << '\xBA', color(textColor);

            cout <<lis[nwGo].getmTitle()<<". . .";
            color(colorCode), gotoxy(75, move + 2); cout << '\xBA';
            gotoxy(75, move + 3); cout << '\xBA';

            gotoxy(42, move + 4); cout << '\xC0';
            color(colorCode); for (int u = 0; u < 32; u++) cout << '\xC4';
            cout << '\xD9'; color(7);
            
          
        }
        
        char keyList = _getch();
        if (keyList == 72) nowShowing--;
        else if (keyList == 80) nowShowing++;
        else if (keyList == 27) {
            clearRightPanel(); break;
        }
        nowShowing +=SZ, nowShowing %= SZ;
        if (!mp[nowShowing]) {
            int tm;
            if (nowShowing == (listCounter - 1 + SZ) % SZ)
                tm=listCounter-1;
            else tm=listCounter+1;
            if (tm < 0)
                listCounter = max(0, listCounter - 8 + SZ), listCounter %= SZ;
            else if (tm+7== SZ) listCounter = 0;
            else listCounter = tm;
        }
    }
    
}
void initialScreen() {
    int u; color(11); char sty = ':';
    gotoxy(0, 0); for (u = 0; u <75; u++) cout<<sty;
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

    gotoxy(8, 6);
    color(set[0]);
    cout << "Show List of Entry";

    gotoxy(8, 8);
    color(set[1]);
    cout << "Make New Entry";

    gotoxy(8, 10);
    color(set[2]);
    cout << "Settings";

    gotoxy(8, 12);
    color(set[3]);
    cout << "Exit";
    
}

void clearRightPanel() {
    for (int u = 1; u <= 32; u++) {
        for (int v = 42; v <= 75; v++) gotoxy(v, u), cout << ' ';
    }
}

void instructionToNav(int tip) {
    switch (tip) {
    case 1:
        gotoxy(3,29),cout << "\xC9 Arrow up/down to navigate menus \xBB";
        gotoxy(3,30),cout << "\xC8 Enter key to select             \xBC";
        break;
    case 2:
        gotoxy(3, 29), cout << "\xC9 Arrow up/down to navigate List  \xBB";
        gotoxy(3, 30), cout << "\xC8 Enter to select/ESC to quit     \xBC";
        break;
    }
}

void newEntryWindow() {
    clrWholeScreen();
    char keyNew; ShowConsoleCursor(true);
    string str = "";
     color(11);
    gotoxy(0, 0); for (int u = 0; u <= 75; u++) cout <<':';
    gotoxy(0, 1); for (int u = 3; u <= 30; u++) cout << ':';
    color(7),cout<<"Pres Esc to quit",color(11);
    for (int u = 44; u <= 75; u++) cout << ':';
    color(7); gotoxy(0, 2);
    while (true) {
        keyNew=_getch();
         //scanf_s("%c", &keyNew,1);
        if (keyNew == 8) {
            cout << keyNew << ' ' << keyNew;
            if (int(str.size())) str.pop_back();
        }
        else if (keyNew == 27) {
            break;
        }
        //else if (keyNew == '\n') cout << str << '\n';
        else str += keyNew,cout<<keyNew;
    }
}

void clrWholeScreen() {
    
    for (int u = 0; u < 109; u++) {
        for (int v = 0; v < 76; v++) gotoxy(v,u),cout << ' ';
    }
}