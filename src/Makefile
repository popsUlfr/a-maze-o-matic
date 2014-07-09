CXX?=g++
LDFLAGS?= -Wl,-O1,--sort-common,--as-needed,-z,relro
CXXFLAGS?= -Wall -Wextra -pedantic
BASE_CXXFLAGS= -std=c++11
CXXFLAGS+=$(BASE_CXXFLAGS)
DEBUG_CXXFLAGS= -ggdb
RELEASE_CXXFLAGS= -mtune=generic -O2 -pipe -fstack-protector-strong --param=ssp-buffer-size=4
HEADERFLAGS= -I/usr/local/include
LIBFLAGS= -L/usr/local/lib
LIBS= -ltermbox -lpthread
STATIC_LIBS= -static-libstdc++ -Wl,-Bstatic -ltermbox -Wl,-Bdynamic -lpthread
BIN=amazeomatic
BINDIR=../bin
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: bin debug static "$(BIN)" "$(BIN)_debug" "$(BIN)_static" clean

all: $(BIN)

bin:
	mkdir -p $(BINDIR)
	
debug: $(BIN)_debug

static: $(BIN)_static
	
$(BIN): CXXFLAGS+=$(RELEASE_CXXFLAGS)
$(BIN): bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(LIBS) -o "$(BINDIR)/$@"
	
$(BIN)_debug: CXXFLAGS+=$(DEBUG_CXXFLAGS)
$(BIN)_debug: bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(LIBS) -o "$(BINDIR)/$@"
	
$(BIN)_static: CXXFLAGS+=$(RELEASE_CXXFLAGS)
$(BIN)_static: bin $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBFLAGS) $(OBJECTS) $(STATIC_LIBS) -o "$(BINDIR)/$@"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADERFLAGS) -c $< -o $@
	
clean:
	rm -f "$(BINDIR)/$(BIN)" "$(BINDIR)/$(BIN)_static" "$(BINDIR)/$(BIN)_debug" $(OBJECTS)
