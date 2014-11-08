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
       -Wno-nonnull \
       -Wno-unused-parameter \
       -Wno-old-style-cast \
       -Wno-unused-label \
       -Wno-variadic-macros \
       -Wno-c99-extensions \
       -Wno-c++98-compat \
       -Wno-global-constructors

SRCDIR = src
OBJDIR=obj

DEBUGOPT ?= -ggdb3 -fno-inline -O0 -DDEBUG

CXXFLAGS += $(OPT) -I$(SRCDIR) -std=c++11
CXXSTATICFLAGS = $(CXXFLAGS) -c -static

TESTS =
TESTFLAGS = $(CXXFLAGS)
TESTFLAGS += -lgtest
TEST_DEFINES ?= -DDEBUG


# Main target
MAIN = main

# Name for the main executable.
MAIN_EXEC = balloon

SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.cpp=.o)))

obj/%.o: src/%.cpp
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
	$(CXX) $(CXXFLAGS) $^ -o $(MAIN_EXEC)

valgrind: OPT += ${DEBUGOPT}
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all -- ./$(MAIN) ${ARGS}

## TEST

filereader_test: $(SRCDIR)/filereader/filereader_test.cpp filereader.a
	$(CXX) -lgtest $(CXXFLAGS) $^ -o $@

stringparserclass_test: $(SRCDIR)/stringparserclass/stringparserclass_test.cpp \
			stringparserclass.a
	$(CXX) -lgtest $(CXXFLAGS) $^ -o $@

test: OPT += ${TEST_DEFINES}
test: OPT += ${DEBUGOPT}
test: all $(TESTS)
	@for testcase in $(TESTS); do \
	    ./$$testcase; \
	done;

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
