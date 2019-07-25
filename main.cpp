#include <iostream>


using namespace std;


bool runSimpleTest();
bool runRandomTest();


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
        cout << endl << numOfTest << " random tests ('.' = PASS; 'x' = FAIL):" << endl;

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
            cout << numOfFailedTest << " tests are failed!" << endl;
        else
            cout << "All tests are passed!" << endl;
    }

    return 0;
}
