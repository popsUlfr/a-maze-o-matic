CXX=clang++
CXXFLAGS= -std=c++11 -Wall -Wextra -pedantic -ggdb
LDFLAGS=
HEADERFLAGS= -I/home/popsulfr/work/termbox-out/include
LIBFLAGS= -L/home/popsulfr/work/termbox-out/lib
LIBS= -ltermbox -lpthread
BIN=mytbproject
BINDIR=../bin
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: clean

all: $(BIN)

bin:
	mkdir -p $(BINDIR)
	
$(BIN): bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(LIBS) -o $(BINDIR)/$(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADERFLAGS) -c $< -o $@
	
clean:
	rm -f $(BINDIR)/$(BIN) $(OBJECTS)