AC_PREREQ(2.65)
AC_INIT([FULL-PACKAGE-NAME],[VERSION],[BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_PATH_MASA(0.50,[],AC_MSG_ERROR([Unable to locate MASA or meet minimum version\
requirement]))

AX_PATH_GRVY(0.34,[],AC_MSG_ERROR([Unable to locate GRVY or meet minimum version\
requirement]))

#Cheks for library functions.
AC_CHECK_FUNCS([pow])


AC_OUTPUT(Makefile src/Makefile test/Makefile)



