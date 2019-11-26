MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

# ifeq ($(CC),x86_64-w64-mingw32-gcc)
# CPPFLAGS=-DCALLBACK=__stdcall
# LDFLAGS=-Llibs/mingw
# LDLIBS=-lglfw -lgdi32 -lglu32 -
# else
# LDFLAGS=-Llibs/linux
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
	rm -f $(OBJS) $(DEPS) StackIt
