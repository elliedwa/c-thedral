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

INCLUDE_FLAGS = -Iinclude -I$(srcdir)/include

COMMON_CPPFLAGS = -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_USE_CHAR8_T -D__USE_GNU
COMMON_CFLAGS = -Wall -Wextra -pipe \
								-ftrivial-auto-var-init=zero
COMMON_CXXFLAGS = $(COMMON_CFLAGS)
CLANG_CXXFLAGS = -Wthread-safety -Wthread-safety-beta -Wthread-safety-verbose

DEBUG_CPPFLAGS = -DDEBUG -D_GLIBCXX_DEBUG
DEBUG_CFLAGS = -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
DEBUG_CXXFLAGS = $(DEBUG_CFLAGS)

RELEASE_CPPFLAGS = -DNDEBUG -D_FORTIFY_SOURCE=3
RELEASE_CFLAGS = -O2 -march=native -mtune=native -flto
RELEASE_CXXFLAGS = $(RELEASE_CFLAGS)

#COMMON_SANITIZER_CPPFLAGS = -D_GLIBCXX_SANITIZE_STD_ALLOCATOR -D_GLIBCXX_SANITIZE_VECTOR
#COMMON_SANITIZER_FLAGS = $(COMMON_SANITIZER_CPPFLAGS) -fsanitize=address,undefined -fsanitize-address-use-after-scope
#GCC_SANITIZER_FLAGS = $(COMMON_SANITIZER_FLAGS)
#LLVM_SANITIZER_FLAGS = $(COMMON_SANITIZER_FLAGS) -fsanitize=function,integer,nullability

AM_CPPFLAGS = $(COMMON_CPPFLAGS) $(DEBUG_CPPFLAGS) $(INCLUDE_FLAGS)
AM_CFLAGS = $(COMMON_CFLAGS) $(DEBUG_CFLAGS) -Wc++-compat
AM_CXXFLAGS = $(COMMON_CXXFLAGS) $(DEBUG_CXXFLAGS)


noinst_LIBRARIES = libcthedral.a

libcthedral_a_SOURCES = src/pieces.c src/placement_gen.c src/bitboard.c src/pbb.c \
												include/cthedral/pieces.h include/cthedral/placement_gen.h include/cthedral/bitboard.h \
												include/cthedral/pbb.h
libcthedral_a_CFLAGS = $(AM_CFLAGS)


LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh
AM_LOG_DRIVER_FLAGS = --ignore-exit



check_LIBRARIES = test/libtap++.a

test_libtap___a_SOURCES = test/tap++.cc include/tap++/tap++.h

LDADD = libcthedral.a test/libtap++.a
check_PROGRAMS = test/test_placement_array_size test/test_bb_and test/test_bb_or \
								 test/test_bb_xor test/test_bb_eq_ne test/test_bb_copy test/test_generate_placement_array \
								 test/test_bb_cmp
AM_DEFAULT_SOURCE_EXT = .cc
TESTS = $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)
