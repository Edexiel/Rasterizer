MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

# -no-pie -pg
CXXFLAGS= -O3 -g -Iinclude -Wall -Wextra -Wfloat-conversion -MMD -Wno-unused-function -march=native -mtune=native -ffast-math -fopenmp
CFLAGS=$(CXXFLAGS)
CXXFLAGS+= -std=c++17 -Iinclude
CC=gcc
CXX=g++
# CXX=/home/g.nisi/Downloads/clang/clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/clang++
# CXX=/home/g.nisi/intel/system_studio_2019/compilers_and_libraries_2019.5.281/linux/bin/intel64/icpc

# ifeq ($(CC),x86_64-w64-mingw32-gcc)
# CPPFLAGS=-DCALLBACK=__stdcall
# LDFLAGS=-Llibs/mingw -msse2 -msse3 
# LDLIBS=-lglfw -lgdi32 -lglu32 -
# else
# LDFLAGS=-Llibs/linux
# LDFLAGS= -no-pie -pg
LDLIBS= -Llib -lglfw -lGL -lGLU -ldl -fopenmp
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
