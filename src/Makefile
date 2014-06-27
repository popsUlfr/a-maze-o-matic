CXX=g++
CXXFLAGS= -std=c++11 -Wall -Wextra -pedantic -ggdb
HEADERFLAGS= -I/usr/local/include
LIBFLAGS= -L/usr/local/lib
LIBS= -ltermbox -lpthread
STATIC_LIBS= -static-libstdc++ -Wl,-Bstatic -ltermbox -Wl,-Bdynamic -lpthread
BIN=amazeomatic
BINDIR=../bin
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: clean

all: $(BIN)

bin:
	mkdir -p $(BINDIR)
	
$(BIN): bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(LIBS) -o $(BINDIR)/$(BIN)
	
$(BIN)_static: bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(STATIC_LIBS) -o $(BINDIR)/$(BIN)_static

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADERFLAGS) -c $< -o $@
	
clean:
	rm -f $(BINDIR)/$(BIN) $(BINDIR)/$(BIN)_static $(OBJECTS)