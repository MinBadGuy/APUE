ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS=-lsocket -lnsl
endif

PROGS =	pollmsg sendmsg bindunix
#bindunix pollmsg sendmsg
FDPASS =

ifeq "$(PLATFORM)" "linux"
	FDPASS = sendfd2.o recvfd2.o 
endif
ifeq "$(PLATFORM)" "freebsd"
	FDPASS = sendfd2.o recvfd2.o
endif

all:	$(PROGS) $(FDPASS)
	for i in open.fe opend.fe open opend; do \
		(cd $$i && $(MAKE) ) || exit 1; \
	done

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	for i in open.fe opend.fe open opend; do \
		(cd $$i && $(MAKE) clean) || exit 1; \
	done

include $(ROOT)/Make.libapue.inc
