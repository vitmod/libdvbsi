#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([libdvbsi++],[0.3.6],[obi@saftware.de],[libdvbsi++])
AM_INIT_AUTOMAKE([dist-bzip2 no-define])
AC_CONFIG_SRCDIR([src/descriptor.cpp])
AC_CONFIG_HEADERS([libdvbsi++-config.h])

# Silent rules are available since 1.11, but older versions
# are still in use. So don't use them unconditionally.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CXX

m4_ifdef([LT_INIT], [LT_INIT], [AC_PROG_LIBTOOL])
AC_CONFIG_MACRO_DIR([m4])

AC_PATH_PROG(CXXTEST, cxxtestgen.pl, no)
AM_CONDITIONAL(HAVE_CXXTEST, test "$CXXTEST" != "no")
AC_PATH_PROG(GIT, git, no)
AM_CONDITIONAL(HAVE_GIT, test "$GIT" != "no")
AC_PATH_PROG(GNUPG, gpg, no)
AM_CONDITIONAL(HAVE_GNUPG, test "$GNUPG" != "no")
AC_PATH_PROG(MD5SUM, md5sum, no)
AM_CONDITIONAL(HAVE_MD5SUM, test "$MD5SUM" != "no")

# Checks for header files.
AC_CHECK_HEADERS([byteswap.h endian.h])

dnl - If any interfaces have been added, removed, or changed since the last
dnl   update, increment current, and set revision to 0.
LT_CURRENT=1
AC_SUBST([LT_CURRENT])
dnl - If the library source code has changed at all since the last update,
dnl   then increment revision (c:r:a becomes c:r+1:a).
LT_REVISION=0
AC_SUBST([LT_REVISION])
dnl - If any interfaces have been added since the last public release, then
dnl   increment age.
dnl - If any interfaces have been removed since the last public release, then
dnl   set age to 0.
LT_AGE=0
AC_SUBST([LT_AGE])

AC_CONFIG_FILES([
Makefile
debian/Makefile
include/Makefile
include/dvbsi++/Makefile
qa/Makefile
src/Makefile
libdvbsi++.pc
])
AC_OUTPUT
