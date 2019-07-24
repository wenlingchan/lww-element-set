#ifndef LWWELEMENTSET_H
#define LWWELEMENTSET_H

#include <unordered_map>
#include <string>
#include <chrono>


using namespace std;


class LwwElementSet
{
public:
    LwwElementSet() = default;
    ~LwwElementSet() = default;
    bool lookUp(const string& element) const;
    void add(const string& element);
    void remove(const string& element);
    void merge(const LwwElementSet& rhs);

private:
    unordered_map<string, chrono::steady_clock::time_point> addSet;
    unordered_map<string, chrono::steady_clock::time_point> removeSet;
};


#endif // LWWELEMENTSET_H
