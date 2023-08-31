CC = gcc
COMMON_DEFINES = -D_GLIBCXX_ASSERTIONS -D__USE_GNU
COMMON_CFLAGS = $(COMMON_DEFINES) -Wall -Wextra -Wno-unused-variable -pipe -pedantic -Wimplicit-fallthrough
DEBUG_DEFINES = -DDEBUG -D_GLIBCXX_DEBUG
DEBUG_CFLAGS = $(DEBUG_DEFINES) -Og -g -ggdb3 -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
RELEASE_DEFINES = -D_FORTIFY_SOURCE=3
RELEASE_CFLAGS = $(RELEASE_DEFINES) -Ofast -march=native -mtune=native -flto

all: debug

debug: CFLAGS = $(COMMON_CFLAGS) $(DEBUG_CFLAGS)
debug: cathedral

release: CFLAGS = $(COMMON_CFLAGS) $(RELEASE_CFLAGS)
release: cathedral

cathedral: cathedral.c

.PHONY: all clean debug
clean:
	$(RM) cathedral *.o
