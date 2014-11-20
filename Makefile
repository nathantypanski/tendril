# Makefile
#
# Author: Nathan Typanski <nathan.typanski.11@cnu.edu>
#
# Copyright (c) 2014 Nathan Typanski
#
# Author: Nathan Typanski
# Exercise: Ex04 string parser

CXX = clang++

OPT ?= -Weverything \
       -Werror \
       -Wno-padded \
       -Wno-variadic-macros \
       -Wno-c99-extensions \
       -Wno-c++98-compat \
       -Wno-c++98-compat-pedantic

SRCDIR = src
OBJDIR=obj

DEBUGOPT ?= -ggdb3 -fno-inline -O0 -DDEBUG

CXXFLAGS += $(OPT) -I$(SRCDIR) -pthread -std=c++11 -stdlib=libstdc++
CXXSTATICFLAGS = $(CXXFLAGS) -c -static
LINKFLAGS = -lncurses -ltermbox

TESTS =
TESTFLAGS = $(CXXFLAGS)
TESTFLAGS += -lgtest
TEST_DEFINES ?= -DDEBUG

# Main target
MAIN = main

# Name for the main executable.
MAIN_EXEC = balloon

SRCS=$(wildcard $(SRCDIR)/*.cc)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.cc=.o)))

obj/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

PHONY: clean all main

all: $(MAIN) $(OBJS)

clean:
	$(RM) $(OBJDIR)/*.o;
	$(RM) $(OBJDIR)/*.d;
	$(RM) $(MAIN_EXEC)
	@for testcase in $(TESTS); do \
	    $(RM) ./$$testcase; \
	done;

run: all
	./$(MAIN_EXEC) ${ARGS}

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $^ -o $(MAIN_EXEC)

valgrind: OPT += ${DEBUGOPT}
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all -- ./$(MAIN) ${ARGS}

## TEST

debug: OPT += ${DEBUGOPT}
debug: all

gdb: debug
	gdb -quiet ./$(MAIN) ${ARGS}

memcheck: debug
	valgrind --tool=memcheck \
                 -v \
                 --leak-check=full \
                 --show-leak-kinds=all \
                 -- ./$(MAIN) ${ARGS}

CXXFLAGS += -MMD
-include $(OBJS:.o=.d)
