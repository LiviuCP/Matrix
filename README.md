Matrix is template library class implementing bidimensional arrays (matrixes) that are dynamically allocatable.

0. DISCLAIMER:

Thanks for using this library!

However please do not use it in critical applications. Although I tested the functionality to my best knowledge and effort there might still be bugs or crashes within the code. Also it might pose some security concerns. For example when the memory is de-allocated it is not overwritten by using a memset(_s) or similar method.

To conclude: use it at your own risk, I will not be held accountable for any damages it might cause whatsoever. Thanks for understanding!


1. INSTALLATION SCENARIOS

Please note that for scenarios 1.1 and 1.2 you need to have the Qt framework installed. This is because the unit tests have been written using Qt tests. I recommend using Qt creator for performing the build although this is not mandatory (I recently migrated the whole project to CMake so it should be possible to use other IDEs too). For using other IDEs additional setup would be required so CMake properly detects the Qt environment (otherwise CMake excludes all tests from build). So far I have only run the tests after building from Qt Creator.

1.1. Running the Tests (excluding FractionMatrixTests)

1) Download the Matrix repo (e.g. by using git clone): https://github.com/LiviuCP/Matrix.git
2) Build it
3) Run the tests either from IDE or from command line (CLI)

1.2. Running the FractionMatrixTests

This is an extension of the previous scenario. For running the tests for fraction matrixes (a.k.a. FractionMatrixTests) first a "third-party" library should be setup.

After building and running the tests for the Matrix library (see section 1.1) the required steps for successfully testing fraction matrixes are:

1) Download (e.g. by using git clone) and build the Fractions repo: https://github.com/LiviuCP/Fractions.git
2) Go to subdir Matrix/MatrixTests/OtherMatrixTypesTests and open CMakeLists.txt
3) Do the following changes:
- adjust the path of the Fractions include directory (FractionLib) by modifying: include_directories(../../../Fractions/FractionLib)
- adjust the path of the Fractions library (built in step 1) by modifying: set_target_properties(fractionlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/../../../Fractions/FractionLib/libFractionLib.so)
- modify the extension of the Fractions library file accordingly (check the Fractions build directory, subdir FractionLib): .so for Linux, .dylib for MacOS, etc. Please note the for Windows this library is built statically
- set the CMake variable FRACTION_LIB_ENABLED to ON
4) Build and run FractionMatrixTests

1.3. Running the Example application

After building the Matrix project (see section 1.1) just run the application from IDE or CLI. Its purpose is to provide a quick overview of the Matrix library functionality.
Please note that it is not required to have Qt installed for having the example application run.

1.4. Using the Matrix library in your own application

Please follow these steps:

1) Download the Matrix repository into a "third-party" directory belonging to your application
2) Add following path to the include paths of your project: [PATH TO THIRD-PARTY DIR]/Matrix/MatrixLib/Matrix
3) #include "matrix.h" (and/or any other file contained within MatrixLib/Matrix) wherever required

Notes:
- please do NOT directly #include any of the files belonging to MatrixLib/Utils into your code files! These are only meant for internal use by the Matrix library.
- the matrix library requires C++17 and above

Important notice! Each object used as matrix template type should satisfy following requirements:
- it should be default constructible
- it should be move/copy constructible/assignable and swappable
- it should support the comparison operators == and !=


2. ESSENTIAL FUNCTIONALITY

Important functionality contained within Matrix class is:
- matrix capacity
- iterators

2.1. Matrix capacity

It's similar to the capacity of std::vector, however it's a bidimentional capacity (rows/columns). It is essential for minimizing performance costs when a matrix needs to be redimensioned, either by resize() or by another size-changing operation like adding a row, column etc.

To be noted: unlike std::vector there is currently no reserve() method for growing capacity without affecting the actual size of the container. This job is instead fulfilled by the resize() method which comes in two flavors:
- resize(): additional elements added when size grows are initialized with a default constructed value
- resizeWithValue(): additional elements are initialized with a specified value

If only the capacity of the matrix needs to be modified, then any resize method should take as arguments:
- the same number of rows and columns as before
- the newly requested row/column capacities

If either capacity is lower than the corresponding size, then the size is taken as (minimal) capacity. For example if the matrix has 3 rows and 5 columns and the requested row/column capacities are 1 and 2, then the matrix will finally have row capacity 3 and column capacity 5. Otherwise the requested capacity is allocated.

2.2. Iterators

Following iterator types are available:

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