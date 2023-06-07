ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	pipe1 pipe2 popen2 myuclc popen1 add2 pipe4 add2stdio tshm devzero
#add2 add2stdio devzero myuclc pipe1 pipe2 pipe4 popen1 popen2 tshm

all:	$(PROGS) tellwait.o popen.o slock.o
#popen.o slock.o tellwait.o

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

slock.o:	slock.c slock.h

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
