MAKE=make
SRCDIR=src
BIN=amazeomatic

.PHONY: debug static "$(BIN)" "$(BIN)_debug" "$(BIN)_static" clean

all:
	$(MAKE) -C $(SRCDIR) all
	
debug:
	$(MAKE) -C $(SRCDIR) debug
	
static:
	$(MAKE) -C $(SRCDIR) static
	
$(BIN):
	$(MAKE) -C $(SRCDIR) "$@"
	
$(BIN)_debug:
	$(MAKE) -C $(SRCDIR) "$@"
	
$(BIN)_static:
	$(MAKE) -C $(SRCDIR) "$@"
	
clean:
	$(MAKE) -C $(SRCDIR) clean