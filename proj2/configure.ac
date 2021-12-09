AC_PREREQ(2.65)
AC_INIT([FULL-PACKAGE-NAME],[VERSION],[BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AX_PATH_MASA(0.50,[],AC_MSG_ERROR([Unable to locate MASA or meet minimum version\
requirement]))
AX_PATH_GRVY(0.34,[],AC_MSG_ERROR([Unable to locate GRVY or meet minimum version\
requirement]))
AX_PATH_HDF5([1.8.0],[yes])
AX_PATH_PETSC([no])

#Check for code coverage
AX_CODE_COVERAGE

#Cheks for library functions.
AC_CHECK_FUNCS([pow])


AC_OUTPUT(Makefile src/Makefile test/Makefile)

