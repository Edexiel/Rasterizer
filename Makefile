MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

# -no-pie -pg
CXXFLAGS= -O3 -g -no-pie -pg -Iinclude -Wall -Wextra -Wfloat-conversion -MMD -Wno-unused-function -march=native -mtune=native -ffast-math
CFLAGS=$(CXXFLAGS)
CXXFLAGS+= -std=c++17 
CC=gcc
CXX=g++
# CXX=/home/g.nisi/Downloads/clang/clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/clang++

# ifeq ($(CC),x86_64-w64-mingw32-gcc)
# CPPFLAGS=-DCALLBACK=__stdcall
# LDFLAGS=-Llibs/mingw
# LDLIBS=-lglfw -lgdi32 -lglu32 -
# else
LDFLAGS=-pg -no-pie
LDLIBS=-lglfw -lGL -lGLU -ldl
# endif

SRCSC = $(wildcard src/*.c)
SRCSCXX = $(wildcard src/*.cpp)

OBJS = $(SRCSC:.c=.o)
OBJS+= $(SRCSCXX:.cpp=.o)

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: rast

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

rast: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(OBJS) $(DEPS) rast
