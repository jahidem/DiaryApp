#pragma once
#include<iostream>
#include "EntryInDiary.h"
#include<vector>
class AllEntrySingleton
{
    static AllEntrySingleton* s_Instance;
    std::vector<EntryInDiary> entryLibrary;
    
    AllEntrySingleton();
    AllEntrySingleton(const  AllEntrySingleton&);
public:

    static AllEntrySingleton* get();
    vector<EntryInDiary> getEntryLibrary();

        
};

