#include "AllEntrySingleton.h"

AllEntrySingleton* AllEntrySingleton::s_Instance=nullptr;

AllEntrySingleton* AllEntrySingleton::get()
{
    return s_Instance;
}

vector<EntryInDiary> AllEntrySingleton::getEntryLibrary()
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
