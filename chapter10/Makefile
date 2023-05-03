ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CLD =

ifeq "$(PLATFORM)" "linux"
  CLD = child
endif
ifeq "$(PLATFORM)" "solaris"
  CLD = child
endif

PROGS =	sigusr reenter $(CLD) read1 read2 critical mask suspend1 suspend2 sigtstp
#critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2
MOREPROGS = tsleep2 systest2
#systest2 tsleep2

all:	$(PROGS) $(MOREPROGS) abort.o sleep1.o sleep2.o system.o

$(PROGS):	$(LIBAPUE)
#		@echo $(CLD)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99

tsleep2:	tsleep2.o sleep2.o
		$(CC) $(CFLAGS) -o tsleep2 tsleep2.o sleep2.o $(LDFLAGS) $(LDLIBS) -std=c99

systest2:	systest2.o system.o
		$(CC) $(CFLAGS) -o systest2 systest2.o system.o $(LDFLAGS) $(LDLIBS) -std=c99

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)

include $(ROOT)/Make.libapue.inc
