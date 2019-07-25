#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
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
                    const vector<string>& lookUpElements, const bool verbose)
{
    bool isPass = true;

    if (verbose)
        cout << "Associativity test: ";

    {
        LwwElementSet setACopy1 = setA;
        LwwElementSet setACopy2 = setA;
        LwwElementSet setBCopy = setB;

        setACopy1.merge(setB); setACopy1.merge(setC);
        setBCopy.merge(setC); setACopy2.merge(setBCopy);

        if (checkLookUpConsistency(setACopy1, setACopy2, lookUpElements))
        {
            if (verbose)
                cout << "PASS" << endl;
        }
        else
        {
            if (verbose)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    if (verbose)
        cout << "Commutativity test: ";

    {
        LwwElementSet setACopy = setA;
        LwwElementSet setBCopy = setB;

        setACopy.merge(setB);
        setBCopy.merge(setA);

        if (checkLookUpConsistency(setACopy, setBCopy, lookUpElements))
        {
            if (verbose)
                cout << "PASS" << endl;
        }
        else
        {
            if (verbose)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    if (verbose)
        cout << "Idempotency test: ";

    {
        LwwElementSet setACopy = setA;

        setACopy.merge(setA);

        if (checkLookUpConsistency(setACopy, setA, lookUpElements))
        {
            if (verbose)
                cout << "PASS" << endl;
        }
        else
        {
            if (verbose)
                cout << "FAIL" << endl;
            isPass = false;
        }
    }

    return isPass;
}


bool runSimpleTest()
{
    cout << "A simple test:" << endl << endl;

    /* Initialize a set */
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
    setC.add("a");

    /* Test look up */
    cout << "Set A:" << endl << setA;
    cout << "Look up 'a', 'b', 'c' results: "
         << setA.lookUp("a") << ", " << setA.lookUp("b") << ", " << setA.lookUp("c") << endl << endl;

    cout << "Set B:" << endl << setB;
    cout << "Look up 'a', 'b', 'c' results: "
         << setB.lookUp("a") << ", " << setB.lookUp("b") << ", " << setB.lookUp("c") << endl << endl;

    cout << "Set C:" << endl << setC;
    cout << "Look up 'a', 'b', 'c' results: "
         << setC.lookUp("a") << ", " << setC.lookUp("b") << ", " << setC.lookUp("c") << endl << endl;

    /* CRDT tests */
    vector<string> lookUpElements;
    lookUpElements.push_back("a");
    lookUpElements.push_back("b");
    lookUpElements.push_back("c");

    return testIdentities(setA, setB, setC, lookUpElements, true);
}


bool runRandomTest()
{
    const int numOfElements = 10;
    const int numOfOperations = 4;

    /* Initialize a set of elements to be used */
    vector<string> lookUpElements(numOfElements);

    for (auto& element : lookUpElements)
        element = to_string(rand());

    /* Randomly initialize a set */
    LwwElementSet setA;

    for (int i = 0; i < numOfOperations; ++i)
        if (rand() % 2)
            setA.add(lookUpElements[rand() % numOfElements]);
        else
            setA.remove(lookUpElements[rand() % numOfElements]);

    /* Replicate */
    LwwElementSet setB = setA;
    LwwElementSet setC = setA;

    /* Local random changes */
    for (int i = 0; i < numOfOperations; ++i)
    {
        if (rand() % 2)
            setA.add(lookUpElements[rand() % numOfElements]);
        else
            setA.remove(lookUpElements[rand() % numOfElements]);

        if (rand() % 2)
            setB.add(lookUpElements[rand() % numOfElements]);
        else
            setB.remove(lookUpElements[rand() % numOfElements]);

        if (rand() % 2)
            setC.add(lookUpElements[rand() % numOfElements]);
        else
            setC.remove(lookUpElements[rand() % numOfElements]);
    }

    /* CRDT tests */
    return testIdentities(setA, setB, setC, lookUpElements, false);
}
