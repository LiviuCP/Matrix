# Matrix
A template library implementing a bidimentional matrix class.

0. DISCLAIMER:

Thanks for using this library!

However please do not use it in critical applications. Although I tested the functionality to my best knowledge and effort there might still be bugs within the code.

To conclude: use it at your own risk, I will not be held accountable for any damages it might cause whatsoever.

1. RUNNING the FractionMatrixTests

Note: for running the tests for fraction matrixes (FractionMatrixTests) first a ThirdParty library should be set.

After building and running the tests for the Matrix library the required steps for successfully testing fraction matrixes are:

1) Clone and build the Fractions repo: https://github.com/LiviuCP/Fractions.git
2) Inside the Matrix source directory create a ThirdParty directory with subdirectories Fractions/lib and Fractions/include
3) From the build directory of the Fractions repo, subdirectory FractionLib copy the whole content to Fractions/lib
4) From the cloned Fractions repo, subdirectory FractionLib copy the .h files to Fractions/include
5) In the .pro file of TypeDependentTests uncomment the FractionMatrixTests subproject
6) Build and run FractionMatrixTests

2. ESSENTIAL FUNCTIONALITY

Important functionality contained in the Matrix class is:

1) Matrix capacity. It's similar to the capacity of std::vector, however it's a bidimentional capacity (rows/columns). It is essential for minimizing performance costs when a matrix has to be redimensioned, either by resize() or by another size-changing operation like adding a row, column etc.

2) Iterators. Currently only ZIterators are available, i.e. iterators that pass the matrix row by row. For example if we have following matrix:

0   1   2
3   4   5
6   7   8

the matrix will be passed: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8

I am planning to add more iterators in the future, like ones that help traversing elements using diagonals (e.g. 0 -> 4 -> 8, 3 -> 7).

For any questions please feel free to comment on my repo.