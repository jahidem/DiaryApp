#include "AllEntrySingleton.h"


vector<EntryInDiary>  AllEntrySingleton::getEntryLibrary()
{
    return entryLibrary;
}

void AllEntrySingleton::addNewEntry(string content) {
    EntryInDiary newEntry;
    newEntry.setmId(++id);
    newEntry.setmContent(content);
    entryLibrary.push_back(newEntry);
}
int AllEntrySingleton::id = 0;