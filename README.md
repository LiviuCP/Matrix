# Matrix
A template library implementing a bidimentional matrix class.

Note: for running the tests for fraction matrixes (FractionMatrixTests) first a ThirdParty library should be set. The required steps are:

1) Clone and build the Fractions repo: https://github.com/LiviuCP/Fractions.git
2) Inside the Matrix source directory create a ThirdParty directory with subdirectories Fractions/lib and Fractions/include
3) From the build directory of the Fractions repo, subdirectory FractionLib copy the whole content to Fractions/lib
4) From the cloned Fractions repo, subdirectory FractionLib copy the .h files to Fractions/include
5) Build and run FractionMatrixTests
