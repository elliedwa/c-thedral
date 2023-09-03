COMMON_DEFINES = -D_GLIBCXX_ASSERTIONS -D__USE_GNU
COMMON_CFLAGS = $(COMMON_DEFINES) -Wall -Wextra -Wno-unused-variable -pipe \
								-pedantic -Wimplicit-fallthrough
DEBUG_DEFINES = -DDEBUG -D_GLIBCXX_DEBUG
DEBUG_CFLAGS = $(DEBUG_DEFINES) -O0 -g -ggdb3 -fno-omit-frame-pointer \
							 -mno-omit-leaf-frame-pointer -fvar-tracking-uninit
RELEASE_DEFINES = -D_FORTIFY_SOURCE=3
RELEASE_CFLAGS = $(RELEASE_DEFINES) -Ofast -march=native -mtune=native -flto

AM_CFLAGS = $(COMMON_CFLAGS) $(DEBUG_CFLAGS)

bin_PROGRAMS = cathedral

cathedral_SOURCES = main.c pieces.c pieces.h \
										placement_gen.c placement_gen.h bitboard.c bitboard.h
cathedral_CFLAGS = $(AM_CFLAGS)

