#include "lwwelementset.h"
#include <ctime>


bool LwwElementSet::lookUp(const string& element) const
{
    const auto addSetMatchedIter = m_addSet.find(element);
    const auto removeSetMatchedIter = m_removeSet.find(element);

    if (addSetMatchedIter == m_addSet.end()) // cannot find
        return false;
    else if (removeSetMatchedIter == m_removeSet.end()) // cannot find
        return true;
    else if (addSetMatchedIter->second >= removeSetMatchedIter->second) // compare time stamps
        return true;

    return false;
}


void LwwElementSet::add(const string& element)
{
    m_addSet[element] = chrono::system_clock::now(); // update time stamp, or insert new element if not exist
}


void LwwElementSet::remove(const string& element)
{
    const auto addSetMatchedIter = m_addSet.find(element);

    if (addSetMatchedIter != m_addSet.end()) // can find
        m_removeSet[element] = chrono::system_clock::now(); // update time stamp, or insert new element if not exist
}


void LwwElementSet::merge(const LwwElementSet& rhs)
{
    for (const auto& elementPair : rhs.m_addSet)
    {
        const auto matchedIter = m_addSet.find(elementPair.first);

        if (matchedIter == m_addSet.end()) // cannot find
            m_addSet.emplace(elementPair); // insert the new element
        else if (matchedIter->second < elementPair.second) // compare time stamps
            matchedIter->second = elementPair.second; // update time stamp to latest
    }

    for (const auto& elementPair : rhs.m_removeSet)
    {
        const auto matchedIter = m_removeSet.find(elementPair.first);

        if (matchedIter == m_removeSet.end()) // cannot find
            m_removeSet.emplace(elementPair); // insert the new element
        else if (matchedIter->second < elementPair.second) // compare time stamps
            matchedIter->second = elementPair.second; // update time stamp to latest
    }
}


ostream& operator<<(ostream& os, const LwwElementSet& set)
{
    using namespace chrono;

    os << "Add-set: {";

    for (const auto& elementPair : set.m_addSet)
    {
        microseconds time_since_epoch = duration_cast<microseconds>(elementPair.second.time_since_epoch());
        os << " (" << elementPair.first << ", " << time_since_epoch.count() << ")";
    }

    os << " }" << endl;
    os << "Remove-set: {";

    for (const auto& elementPair : set.m_removeSet)
    {
        microseconds time_since_epoch = duration_cast<microseconds>(elementPair.second.time_since_epoch());
        os << " (" << elementPair.first << ", " << time_since_epoch.count() << ")";
    }

    os << " }" << endl;

    return os;
}
