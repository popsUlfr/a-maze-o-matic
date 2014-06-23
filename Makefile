MAKE=make
SRCDIR=src

.PHONY: clean

all:
	$(MAKE) -C $(SRCDIR) all
	
clean:
	$(MAKE) -C $(SRCDIR) clean