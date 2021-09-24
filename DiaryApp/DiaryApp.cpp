// DiaryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
#include<conio.h>
#include "EntryInDiary.h"   // this represnts single entry on diary
#include "AllEntrySingleton.h"  // Holds all the entryInDiary remains 
         //throughout the liftime of the application
#include<thread>
#include<mutex>
#include <map>
#include <chrono> 
#include"customFunctions.h"
using namespace std;
mutex mu;
vector<pair<string, int>> temp,temp_thread;
int set[] = { 11,7,7,7 };   // just some numbers for colors of the Menu
char counter = 0;   // indicates which item of the Menu is active
char key;   // takes keyboard inputs
bool not_new = true;
bool show(int x,int y) {
    mu.lock();
    if(temp_thread.size())
        gotoxy(3, 30), color(temp_thread[0].second), cout << temp_thread[0].first,temp_thread.clear();
    if (x != 3 || y != 30) {
        gotoxy(x, y);

        for (auto x : temp) color(x.second), cout << x.first;
        temp.clear();
    }
    mu.unlock();
    return 1;
    }
void initialScreen();   // draws the initial UI
void showListEntry();   // shows list on the right panel
void clearRightPanel(); // clear al content int the right panel 
void instructionToNav(int); // instructons on the lower left to navigate
void newEntryWindow();
void threadWork();
int main()
{  
    thread subThread(threadWork);
   
    setFontSize();
    //gotoxy(0, 37); show(AllEntrySingleton::get().ga();
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
            else if (counter == 0) showListEntry(), system("cls");
            else if (counter == 1) {
                system("cls");not_new = false;
                newEntryWindow();
                ShowConsoleCursor(false);
                system("cls"); not_new = true;
            }
            //else settings;
        }
        counter += 4, counter %= 4;
        for (int& x : set) x = 7;
        set[counter] = 11;

    }
    subThread.join();
}
void showListEntry() {
    int  listCounter = 0, nowShowing = 0;
    vector<EntryInDiary> lis;
    lis = AllEntrySingleton::get().getEntryLibrary();
    int const SZ = int(lis.size());
    if(SZ==0) temp.push_back({ "No Entry Yet" ,8}),show(50, 16);
    while (true) {
        int nwGo = listCounter, move;
        map<int, int> mp;
        color(8), instructionToNav(2);
        for (move = 1, nwGo = listCounter; move < 30 && move < 4 * SZ; move += 4, nwGo++) {
            int colorCode = 8, textColor = 8; nwGo %= SZ; mp[nwGo] = 1;
            //for (int u = 2; u < 4; u++) {//works fine for refreshing but casuses gliching
                //need to be fixed
               // gotoxy(43, move + u); for (int v = 43; v < 75; v++) show(' ';
            //}


            if (nowShowing == nwGo) colorCode = 11, textColor = 7;
            temp.push_back({ "[" ,colorCode });
            show(42, move + 1);

            temp.push_back({ lis[nwGo].getmDate(),textColor });
            temp.push_back({ "]",colorCode });
            temp.push_back({ "             #" + lis[nwGo].getStringId(),8 });
            show(43,move+1);
            
            temp.push_back({ "\xDA", colorCode });
            for (int u = 0; u < 32; u++) temp.push_back({ "\xC4",colorCode });
            show(42, move + 2);

            temp.push_back({ "\xB3",colorCode });
            temp.push_back({ lis[nwGo].getmTitle() + ". . .", textColor });
            show( 42, move + 3);

            temp.push_back({ "\xBF", colorCode });
            show(75, move + 2);

            temp.push_back({ "\xB3",colorCode });
            show(75, move + 3);

            temp.push_back({ "\xC0",colorCode });
            for (int u = 0; u < 32; u++) temp.push_back({ "\xC4", colorCode });
            temp.push_back({ "\xD9",colorCode }); 
            show(42, move + 4);
            color(7);


        }

        char keyList = _getch();
        if (keyList == 72) nowShowing--;
        else if (keyList == 80) nowShowing++;
        else if (keyList == 27)  break;
    
        nowShowing += SZ, nowShowing %= SZ;
        if (!mp[nowShowing]) {
            int tm;
            if (nowShowing == (listCounter - 1 + SZ) % SZ)
                tm = listCounter - 1;
            else tm = listCounter + 1;
            if (tm < 0)
                listCounter = max(0, listCounter - 8 + SZ), listCounter %= SZ;
            else if (tm + 7 == SZ) listCounter = 0;
            else listCounter = tm;
        }
    }
}
void initialScreen() {
    int u; char sty = ':';
    for (u = 0; u < 75; u++) temp.push_back({ string(1,sty),11 });
    show(0, 0);

    temp.push_back({ "*", 7 }); for (u = 0; u < 39; u++) temp.push_back({ "\xC4",7 });
    temp.push_back({ "*", 7 }), show(0, 1);
    temp.push_back({ "\xB3\t\t", 7 });
    temp.push_back({ " My_Diary ",6 });
    temp.push_back({ "\t\t\xB3",7 });
    show(0, 2);

    temp.push_back({ "*",7 });
    for (u = 0; u < 39; u++) temp.push_back({ "\xC4",7 });
    temp.push_back({ "*",7 });
    show(0, 3);

    for (u = 4; u < 33; u++) temp.push_back({"\xB0", 14}), show(40, u);

    temp.push_back({ "Show List of Entry",set[0] });
    show(8, 6);

    temp.push_back({ "Make New Entry",set[1] });
    show(8, 9);

    temp.push_back({ "Settings",set[2] });
    show(8, 12);

    temp.push_back({ "Exit",set[3] });
    show(8, 15);
    
}

void clearRightPanel() {
    for (int u = 1; u <= 33; u++) {
        for (int v = 42; v <= 75; v++) temp.push_back({ " ",7 }), show(u, v);
    }
}

void instructionToNav(int tip) {
    switch (tip) {
    case 1:
        temp.push_back({ "\xC9 Arrow up/down to navigate menus \xBB", 8 }), show(3, 26);
        temp.push_back({"\xC8 Enter key to select             \xBC", 8}),show(3, 27);
        break;
    case 2:
         temp.push_back({ "\xC9 Arrow up/down to navigate List  \xBB", 8 }), show(3, 26);
         temp.push_back({ "\xC8 Enter to select/ESC to quit     \xBC", 8 }), show(3, 27);
        break;
    }
}

void newEntryWindow() {
    system("cls");
    char keyNew; ShowConsoleCursor(true);
    string str = "";
    for (int u = 0; u <= 75; u++) temp.push_back({ ":",11 });
    show(0, 0);
    for (int u = 3; u <= 30; u++) temp.push_back({ ":",11 });
    temp.push_back({ "Press Esc to quit",7 });
    for (int u = 44; u <= 74; u++) temp.push_back({":",11});
    show(0, 1);
    int row = 2;
    gotoxy(0, row);
    while (true) {
        keyNew=_getch();
         //scanf_s("%c", &keyNew,1);
        if (keyNew == 8) {
            temp.push_back({ string(1,keyNew) + " " + string(1,keyNew),7 });
            if (int(str.size())) str.pop_back();
        }
        else if (keyNew == 27) {
            AllEntrySingleton::get().addNewEntry(str); break;
        }
        else if (keyNew == 13) gotoxy(0, ++row), str += keyNew;

        else if (32 <= keyNew && keyNew <= 126) str += keyNew, temp.push_back({ string(1,keyNew),7 });
    }
}

void threadWork() {
    int qa = 0;
    
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (not_new) {
            COORD cord = get_console_cursor();
            temp_thread.push_back({ formatted_time_date(),3 });
            show(3, 30);
            set_console_cursor(cord);
        }
    }
}