TEMPLATE = subdirs

SUBDIRS += \
    MatrixLib \
    MatrixTests

MatrixTests.depends = MatrixLib
