#pragma once
#include<iostream>
#include "EntryInDiary.h"
#include<vector>
class AllEntrySingleton
{
    AllEntrySingleton();
    ~AllEntrySingleton();
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
            newEntry.setmTitle("Title " + to_string(u + 1));
            newEntry.setmId(u);
            newEntry.setmContent("Content number" + to_string(u));
            entryLibrary.push_back(newEntry);
        }
        return entryLibrary;
    }
    int ga() {
        return 9;
    }

        
};

