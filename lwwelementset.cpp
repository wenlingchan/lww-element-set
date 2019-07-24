#include "lwwelementset.h"


bool LwwElementSet::lookUp(const string& element) const
{
    const auto addSetMatchedIter = addSet.find(element);
    const auto removeSetMatchedIter = removeSet.find(element);

    if (addSetMatchedIter == addSet.end()) // cannot find
        return false;

    if (removeSetMatchedIter == removeSet.end()) // cannot find
        return true;

    if (addSetMatchedIter->second >= removeSetMatchedIter->second) // compare time stamps
        return true;

    return false;
}


void LwwElementSet::add(const string& element)
{
    addSet[element] = chrono::steady_clock::now(); // update time stamp, or insert new element if not exist
}


void LwwElementSet::remove(const string& element)
{
    const auto addSetMatchedIter = addSet.find(element);

    if (addSetMatchedIter != addSet.end()) // can find
        removeSet[element] = chrono::steady_clock::now(); // update time stamp, or insert new element if not exist
}


void LwwElementSet::merge(const LwwElementSet& rhs)
{
    for (const auto& elementPair : rhs.addSet)
    {
        const auto matchedIter = addSet.find(elementPair.first);

        if (matchedIter == addSet.end()) // cannot find
            addSet.emplace(elementPair); // insert the new element
        else if (matchedIter->second < elementPair.second) // compare time stamps
            matchedIter->second = elementPair.second; // update time stamp to latest
    }

    for (const auto& elementPair : rhs.removeSet)
    {
        const auto matchedIter = removeSet.find(elementPair.first);

        if (matchedIter == removeSet.end()) // cannot find
            removeSet.emplace(elementPair); // insert the new element
        else if (matchedIter->second < elementPair.second) // compare time stamps
            matchedIter->second = elementPair.second; // update time stamp to latest
    }
}
