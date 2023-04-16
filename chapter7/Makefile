ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = hello1 doatexit echoarg testjmp getrlimit
#doatexit echoarg getrlimit hello1 testjmp

all:	$(PROGS) opendata.o scope.o

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99
#		$(CC) $(CFLAGS) -O $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99
clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
