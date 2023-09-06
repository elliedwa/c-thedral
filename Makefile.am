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

ACLOCAL_AMFLAGS = -I m4

dist_doc_DATA = README

AM_CPPFLAGS = -Iinclude -I$(srcdir)/include

COMMON_DEFINES = -D_GLIBCXX_ASSERTIONS -D__USE_GNU
COMMON_CFLAGS = $(COMMON_DEFINES) -Wall -Wextra -Wno-unused-variable -pipe \
								-pedantic -Wimplicit-fallthrough
AM_CFLAGS = $(COMMON_CFLAGS)

lib_LTLIBRARIES = libcthedral.la

libcthedral_la_SOURCES = src/pieces.c src/placement_gen.c src/bitboard.c
nobase_include_HEADERS = include/cthedral/pieces.h include/cthedral/placement_gen.h include/cthedral/bitboard.h
libcthedral_la_CFLAGS = $(AM_CFLAGS)

LDADD = libcthedral.la


check_PROGRAMS = test/cthedral_tests
test_cthedral_tests_SOURCES = test/cthedral_tests.c test/rexo.h

TESTS = $(check_PROGRAMS)
