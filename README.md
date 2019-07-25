#LLW-Element-Set Implementation

This project is a C++ implementation of the LLW-Element-Set (Last-Write-Wins-Element-Set) CRDT (Conflict-free Replicated Data Type).
The LLW-Element-Set is defined in ```lwwelementset.h``` and ```lwwelementset.cpp```.
The test cases are defined in ```test.cpp```. There are a simple test case for preliminary testing and a random test for massive random testing.
The ```main.cpp``` calls the test cases.

##Build

```bash
cd /path/to/lww-element-set-master/
qmake -makefile
make
```

##Run

```bash
./LwwElementSet
```

##Output

The output should be like this:

```
LWW-Element-Set CRDT
Implemented by Wenling Chan

A simple test:

Set A:
Add-set: { (b, 1564069610324829) (c, 1564069610324836) (a, 1564069610324828) }
Remove-set: { (a, 1564069610324830) }
Look up 'a', 'b', 'c' results: 0, 1, 1

Set B:
Add-set: { (a, 1564069610324828) (b, 1564069610324829) }
Remove-set: { (b, 1564069610324836) (a, 1564069610324830) }
Look up 'a', 'b', 'c' results: 0, 0, 0

Set C:
Add-set: { (a, 1564069610324836) (b, 1564069610324829) }
Remove-set: { (a, 1564069610324830) }
Look up 'a', 'b', 'c' results: 1, 1, 0

Associativity test: PASS
Commutativity test: PASS
Idempotency test: PASS

1000 random tests ('.' = PASS; 'x' = FAIL):
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
....................................................................................
............................................................................
All tests are passed!
```
