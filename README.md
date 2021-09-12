# Matrix
A template library implementing a bidimentional matrix class.

0. DISCLAIMER:

Thanks for using this library!

However please do not use it in critical applications. Although I tested the functionality to my best knowledge and effort there might still be bugs or crashes within the code.

To conclude: use it at your own risk, I will not be held accountable for any damages it might cause whatsoever. Thanks for understanding!

1. INSTALLATION SCENARIOS

1.1. Running the Tests (excluding FractionMatrixTests)

1) Git clone the Matrix repo: https://github.com/LiviuCP/Matrix.git
2) Build it with Qt Creator
3) Run the tests

1.2. Running the FractionMatrixTests

For running the tests for fraction matrixes (FractionMatrixTests) first a ThirdParty library should be set.

After building and running the tests for the Matrix library (see section 1.1) the required steps for successfully testing fraction matrixes are:

1) Clone and build the Fractions repo: https://github.com/LiviuCP/Fractions.git
2) Inside the Matrix source directory create a ThirdParty directory with subdirectories Fractions/lib and Fractions/include
3) From the build directory of the Fractions repo, subdirectory FractionLib copy the whole content to Fractions/lib
4) From the cloned Fractions repo, subdirectory FractionLib copy the .h files to Fractions/include
5) In the .pro file of TypeDependentTests uncomment the FractionMatrixTests subproject
6) Build and run FractionMatrixTests

1.3. Using the Matrix library within an application

The below instructions are not necessarily the only solution but the one I've been using/testing so far. It assumes you are using Qt Creator as IDE and Git as VCS. For other setups different workarounds would be required.

Please follow these steps:

1) Download the Matrix repository as submodule in a "third-party" directory belonging to your application. For more details regarding submodules please check: https://git-scm.com/book/en/v2/Git-Tools-Submodules
2) Add following paths to your INCLUDEPATH project variable in any project you wish to include the Matrix code:

[PATH TO THIRD-PARTY DIR]/Matrix/MatrixLib/Matrix
[PATH TO THIRD-PARTY DIR]/Matrix/MatrixLib/Utils

3) #include "matrix.h" (and/or any other file belonging to MatrixLib/Matrix) into the code files where it is required.
4) Update your code as per requirements and build the project

Note: please do NOT directly #include any of the files belonging to MatrixLib/Utils into your code files! These are only meant for internal use by the Matrix library.

2. ESSENTIAL FUNCTIONALITY

Important functionality contained in the Matrix class is:

1) Matrix capacity. It's similar to the capacity of std::vector, however it's a bidimentional capacity (rows/columns). It is essential for minimizing performance costs when a matrix has to be redimensioned, either by resize() or by another size-changing operation like adding a row, column etc.

2) Iterators. Following iterator types are available:

a) Z-Iterators. These traverse the matrix row by row. For example by using a ZIterator pointing to the first element ([0][0]) of this matrix:

0   1   2
3   4   5
6   7   8

the matrix will be traversed: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8

The Z-Iterators have following sub-types:
- read-write Z-Iterators (class ZIterator)
- read-only Z-Iterators (class ConstZIterator)
- reverse read-write Z-Iterators (class ReverseZIterator)
- reverse read-only Z-Iterators (class ConstReverseZIterator)

b) N-Iterators. These traverse the matrix column by column. For example by using a NIterator pointing to the first element ([0][0]) of the above matrix it will be traversed as follows: 0 -> 3 -> 6 -> 1 -> 4 -> 7 -> 2 -> 5 -> 8. Using N-Iterators is equivalent to using Z-Iterators on the transposed matrix.

The N-Iterators have following sub-types:
- read-write N-Iterators (class NIterator)
- read-only N-Iterators (class ConstNIterator)
- reverse read-write N-Iterators (class ReverseNIterator)
- reverse read-only N-Iterators (class ConstReverseNIterator)

c) D-Iterators. These traverse the matrix diagonally. A matrix can be divided into m + n - 1 diagonals where m is the number of lines and n is the number of columns. The diagonal starting at [0][0] has diagonal number 0 while the lower ones are numbered negatively and the upper ones are numbered positively. Take the below matrix for example:

0   1   2   3
4   5   6   7
8   9  10  11

It has following diagonals:
- diagonal -2 with element 8
- diagonal -1 with elements 4, 9
- diagonal 0 with elements 0, 5, 10
- diagonal 1 with elements 1, 6, 11
- diagonal 2 with elements 2, 7
- diagonal 3 with element 3

Each diagonal is traversed from the first element (with diagonal index 0) to the last element. For example for diagonal 1 the traversing order is: 1 -> 6 -> 11 for a direct D-Iterator. For a reverse D-Iterator the order would be 11 -> 6 -> 1.

Consequently a matrix element can be defined in two ways:
- by line and column number
- by diagonal number and diagonal index. For example the element with value 6 for above 4x3 matrix can be defined by line 1 and column 2 or by diagonal 1 and diagonal index 1.

To be noted:
- unlike ZIterators no empty DIterator (meaning not linked to a matrix) can be created.
- also unlike ZIterators no DIterator related to an empty matrix can be created. This is because a diagonal should always have a strictly positive size.
- another important way the DIterators differentiate from ZItertors is that only a part of the matrix (a diagonal) can be traversed by using a D-Iterator. In order to traverse another diagonal it has to be re-assigned by using an iterator return function like getDIterator(). It is not possible to individually change the diagonal number or index by using a setter.

The D-Iterators have following sub-types:
- read-write D-Iterator (class DIterator)
- read-only D-Iterator (class ConstDIterator)
- read-write reverse D-Iterator (class ReverseDIterator)
- read-only reverse D-Iterator (class ConstReverseDIterator)

d) Mirrored diagonal iterators (M-Iterators). These work the same way as D-Iterators but traverse the "crossing diagonals" of the matrix. This way the "mirror" the D-Iterators.

Take the above example. A "forward" M-Iterator has as diagonal 0 following elements: [0, 3], [1, 2], [2, 1], namely: 3, 6, 9. It traverses them exactly in this order. The corresponding mirrored reverse iterator traverses them in opposite direction: [2, 1] -> [1, 2] -> [0, 3].

The -1 diagonal is the one below and the +1 diagonal is the above one and so on. In this way they mirror the behavior of the D-Iterators.

Same notes apply for M-Iterators as for D-Iterators (see above).

The M-Iterators have following sub-types:
- read-write M-Iterator (class MIterator)
- read-only M-Iterator (class ConstMIterator)
- read-write reverse M-Iterator (class ReverseMIterator)
- read-only reverse M-Iterator (class ConstReverseMIterator)

Final iterator notes:
- the begin() function has been implemented to make it possible to pass through matrix elements by using the auto keyword. This can only be done in the "Z" direction starting with element [0][0] as begin() returns a ZIterator object.
- the isValidWithMatrix() method of all iterator classes has been created mainly as a helper function for writing unit tests for iterators. Although it can be used in "production" scenarios it is not recommended to do so. Instead it should be assumed that an iterator becomes invalid once the structure of the matrix it points to changes. Examples of structure modifications are: matrix resize, using the move constructor, using assignment operators, removing a row/column, clearing the matrix content, etc. In this case the iterator should be reset (e.g. to matrix begin) or a new one should be created.

3. ERROR HANDLING

The Matrix library contains error handling functionality that deals with various situations like: index out of bounds, negative arguments provided as indexes, etc. This functionality is by default enabled as a safety measure especially when newly using the class. It can be disabled by adding #define ERROR_CHECKING_DISABLED before the matrix.h include statement. It is obviously recommended to do this only when the code implementation has been finished and all bugs and crashes have been corrected. For the list of possible errors please consult errorhandling.h.

There are two ways of triggering the errors: by assertion or by exception. By default assertions are made so each error will terminate the code immediately. They can be turned into exceptions by adding #define CONVERT_TO_EXCEPTIONS right after the previously mentioned define statement (and obviously before the matrix.h include). Exceptions should only be used when you necessarily need to capture an error with a try-catch block. I only enabled them in tst_exceptionstests.cpp where I tested that all necessary errors are triggered by the library code. In real application scenarios you would normally not require them but instead use asserts for debugging.

For any questions please feel free to comment on my repo.