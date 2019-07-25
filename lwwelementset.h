#ifndef LWWELEMENTSET_H
#define LWWELEMENTSET_H

#include <unordered_map>
#include <string>
#include <chrono>
#include <iostream>


using namespace std;


class LwwElementSet
{
public:
    bool lookUp(const string& element) const;
    void add(const string& element);
    void remove(const string& element);
    void merge(const LwwElementSet& rhs);
    friend ostream& operator<<(ostream& os, const LwwElementSet& set);

private:
    unordered_map<string, chrono::system_clock::time_point> m_addSet;
    unordered_map<string, chrono::system_clock::time_point> m_removeSet;
};


#endif // LWWELEMENTSET_H
