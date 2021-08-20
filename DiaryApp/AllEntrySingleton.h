#pragma once
#include<iostream>
#include "EntryInDiary.h"
#include<vector>
class AllEntrySingleton
{   
private:
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
    vector<EntryInDiary> getEntryLibrary()
    {
        for (int u = 0; u < 20; u++) {
            EntryInDiary newEntry;
            newEntry.setmId(u);
            newEntry.setmContent("kisu elsdfg gf fg fdg g fdg fdg fdgfg  ghghgh");
            entryLibrary.push_back(newEntry);
        }
        return entryLibrary;
    }
    int ga() {
        return 9;
    }

        
};

