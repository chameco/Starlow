OBJECTS = main.o
CFLAGS = -I. -Wall -g
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(prefix)/bin
datarootdir = $(prefix)/share
datadir = $(datarootdir)
libdir = $(exec_prefix)/lib
all : $(OBJECTS)
	$(CC) $(OBJECTS) -g -Wall -lm -o starlow
tarball:
	mkdir starlow-$(VERSION)
	cp -r Makefile *.c *.h starlow-$(VERSION)
	tar -czf starlow-$(VERSION).tar.gz starlow-$(VERSION)
install:
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) starlow $(DESTDIR)$(bindir)/starlow
uninstall:
	rm $(DESTDIR)$(bindir)/starlow
clean:
	rm $(OBJECTS)
