#pragma once
#include<iostream>
#include "EntryInDiary.h"
#include<vector>
class AllEntrySingleton
{   
private:
    static int id;
    AllEntrySingleton() {};
    vector<EntryInDiary> entryLibrary;
public:
    AllEntrySingleton(const AllEntrySingleton&) = delete;
    AllEntrySingleton(AllEntrySingleton&&) = delete;
    AllEntrySingleton& operator=(const AllEntrySingleton&) = delete;
    AllEntrySingleton& operator=(AllEntrySingleton&&) = delete;

    static AllEntrySingleton& get()
    {
        static AllEntrySingleton instance;
        return instance;
    }
    vector<EntryInDiary> getEntryLibrary();
    void addNewEntry(string);
        
};

