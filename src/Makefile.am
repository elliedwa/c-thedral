COMMON_DEFINES = -D_GLIBCXX_ASSERTIONS -D__USE_GNU
COMMON_CFLAGS = $(COMMON_DEFINES) -Wall -Wextra -Wno-unused-variable -pipe \
								-pedantic -Wimplicit-fallthrough
AM_CFLAGS = $(COMMON_CFLAGS)

bin_PROGRAMS = cathedral

cathedral_SOURCES = main.c pieces.c pieces.h \
										placement_gen.c placement_gen.h bitboard.c bitboard.h
cathedral_CFLAGS = $(AM_CFLAGS)

