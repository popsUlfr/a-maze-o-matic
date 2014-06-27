MAKE=make
SRCDIR=src
BIN=amazeomatic

.PHONY: clean

all:
	$(MAKE) -C $(SRCDIR) all
	
$(BIN):
	$(MAKE) -C $(SRCDIR) $(BIN)
	
$(BIN)_static:
	$(MAKE) -C $(SRCDIR) $(BIN)_static
	
clean:
	$(MAKE) -C $(SRCDIR) clean