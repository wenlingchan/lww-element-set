#include <iostream>
#include <vector>
#include <string>
#include "lwwelementset.h"


using namespace std;


bool checkLookUpConsistency(const LwwElementSet& set1, const LwwElementSet& set2,
                            const vector<string>& lookUpElements)
{
    for (const string& element : lookUpElements)
        if (set1.lookUp(element) != set2.lookUp(element))
            return false;

    return true;
}


bool testIdentities(const LwwElementSet& setA, const LwwElementSet& setB, const LwwElementSet& setC,
                    const vector<string>& lookUpElements, const bool isPrint)
{
    bool isPass = true;

    if (isPrint)
        cout << "  Associativity: ";

    {
        LwwElementSet setACopy1 = setA;
        LwwElementSet setACopy2 = setA;
        LwwElementSet setBCopy = setB;

        setACopy1.merge(setB); setACopy1.merge(setC);
        setBCopy.merge(setC); setACopy2.merge(setBCopy);

        if (checkLookUpConsistency(setACopy1, setACopy2, lookUpElements))
        {
            if (isPrint)
                cout << "PASS" << endl;
        }
        else
        {
            if (isPrint)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    if (isPrint)
        cout << "  Commutativity: ";

    {
        LwwElementSet setACopy = setA;
        LwwElementSet setBCopy = setB;

        setACopy.merge(setB);
        setBCopy.merge(setA);

        if (checkLookUpConsistency(setACopy, setBCopy, lookUpElements))
        {
            if (isPrint)
                cout << "PASS" << endl;
        }
        else
        {
            if (isPrint)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    if (isPrint)
        cout << "  Idempotency: ";

    {
        LwwElementSet setACopy = setA;

        setACopy.merge(setA);

        if (checkLookUpConsistency(setACopy, setA, lookUpElements))
        {
            if (isPrint)
                cout << "PASS" << endl;
        }
        else
        {
            if (isPrint)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    return isPass;
}


bool runSimpleTest()
{
    cout << "A simple test:" << endl;

    /* Initialize a set*/
    LwwElementSet setA;
    setA.add("a");
    setA.add("b");
    setA.remove("a");

    /* Replicate */
    LwwElementSet setB = setA;
    LwwElementSet setC = setA;

    /* Local changes */
    setA.add("c");
    setB.remove("b");
    setC.add("b");

    /* CRDT tests */
    vector<string> lookUpElements;
    lookUpElements.push_back("a");
    lookUpElements.push_back("b");
    lookUpElements.push_back("c");

    return testIdentities(setA, setB, setC, lookUpElements, true);
}


bool runRandomTest()
{
    vector<string> lookUpElements;

    /* Initialize a set*/
    LwwElementSet setA;
    setA.add("a");
    lookUpElements.push_back("a");
    setA.add("b");
    lookUpElements.push_back("b");
    setA.remove("a");

    /* Replicate */
    LwwElementSet setB = setA;
    LwwElementSet setC = setA;

    /* Local changes */
    setA.add("c");
    lookUpElements.push_back("c");
    setB.remove("b");
    setC.add("b");

    /* CRDT tests */
    return testIdentities(setA, setB, setC, lookUpElements, false);
}


int main()
{
    cout << "LWW-Element-Set CRDT" << endl;
    cout << "Implemented by Wenling Chan" << endl << endl;

    /* Simple test */
    runSimpleTest();

    /* Random tests */
    {
        const int numOfTest = 1000;
        int numOfFailedTest = 0;
        cout << endl << numOfTest << " random tests:" << endl;

        for (int testIndex = 0; testIndex < numOfTest; ++testIndex)
        {
            if (runRandomTest())
                cout << ".";
            else
            {
                cout << "x";
                ++numOfFailedTest;
            }
        }
        cout << endl;

        if (numOfFailedTest > 0)
            cout << numOfFailedTest << " tests failed!" << endl;
        else
            cout << "All tests passed!" << endl;
    }

    return 0;
}
