#                                               -*- Autoconf -*-
# Copyright 2023 Elliot C. Edwards
#
# c-thedral is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# c-thedral is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with c-thedral.  If not, see <https://www.gnu.org/licenses/>.

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([c-thedral], [0.0.3])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([src/pieces.c])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_AWK
AM_PROG_AR
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX([11], [noext], [mandatory])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_FORK
AC_FUNC_MMAP
AC_CHECK_FUNCS([regcomp])


AC_CONFIG_FILES([Makefile])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AC_OUTPUT
