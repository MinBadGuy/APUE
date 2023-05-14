ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TOUT =
ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS = -pthread
  TOUT = timeout.o
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lpthread
  TOUT = timeout.o
endif

# $(info $(PLATFORM))
# $(info $(TOUT))

PROGS =	suspend atfork
#atfork suspend

all: $(PROGS) detach.o $(TOUT) getenv1.o getenv2.o getenv3.o 

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
