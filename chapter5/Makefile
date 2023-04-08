ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
  MEMSTR = memstr
else
  MEMSTR =
endif

PROGS =	getcputc fgetsfputs buf tempfiles mkstemp $(MEMSTR)
#buf fgetsfputs getcharbug getcputc mkstemp tempfiles

all:	$(PROGS) 

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)

include $(ROOT)/Make.libapue.inc
