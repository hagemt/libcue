# This file licensed permissively under the BSD 3-Clause License (as per OSI)
# Modifications encouraged; original version Copyright (c) 2014 Tor E Hagemann

BUILD_SLUG := libcue
BUILD_TYPE := DEBUG
SAY := "$(shell which echo)" -e "[$(BUILD_SLUG):$(BUILD_TYPE)]"

## C Compilation / Linking

CFLAGS_DEBUG   := -O0 -ggdb3 -pedantic
CFLAGS_RELEASE := -O3 -DNDEBUG
CFLAGS_WARNING := -Wall -Wextra
CFLAGS := -std=c99 -D_BSD_SOURCE -D_XOPEN_SOURCE -DNSIG=16 $(CFLAGS)
CFLAGS := $(FLAGS_WARNING) $(CFLAGS_$(BUILD_TYPE)) $(CFLAGS)

CC := "$(shell which gcc)"
DB := "$(shell which gdb)"

###

all: $(BUILD_SLUG)

clean:
	@$(SAY) 'starting project clean-up:'
	@$(RM) -fv "$(BUILD_SLUG).so" "$(BUILD_SLUG)"
	@$(SAY) 'removing object files:'
	@$(RM) -fv *.o *.so test/*.o

debug: all
	@$(SAY) 'starting a debugger:'
	@LD_LIBRARY_PATH=. $(DB) -tui "./$(BUILD_SLUG)"

test: all
	@$(SAY) 'running test program(s)'
	@LD_LIBRARY_PATH=. "./$(BUILD_SLUG)"

.PHONY: all clean debug test

###

SOURCE_FILES := test/$(BUILD_SLUG).c
OBJECT_FILES := $(SOURCE_FILES:%.c=%.o)

LIB_SOURCE_FILES := $(BUILD_SLUG).c
LIB_OBJECT_FILES := $(LIB_SOURCE_FILES:%.c=%.o)

$(BUILD_SLUG): $(BUILD_SLUG).so $(OBJECT_FILES)
	@$(SAY) 'LINK' "($(OBJECT_FILES) + $(BUILD_SLUG).so) => '$@'"
	@$(CC) $(CFLAGS) -o "$@" $(OBJECT_FILES) -L. -l$(BUILD_SLUG:lib%=%)

$(BUILD_SLUG).so: $(LIB_OBJECT_FILES)
	@$(SAY) 'LINK' "($^) => '$@'"
	@$(CC) -shared $(CFLAGS) -o "$@" $^

## Generic Targets:

%.o: %.c
	@$(SAY) 'COMPILE' "'$<' => '$@'"
	@$(CC) -fPIC $(CFLAGS) -o "$@" -c "$<" -Iinclude

%.c: include/libcue.h Makefile
