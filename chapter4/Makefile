ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
	ZAP = zap
else
	ZAP =
endif


PROGS =	filetype access umask changemod unlink $(ZAP) mycd cdpwd devrdev
# access cdpwd changemod devrdev filetype mycd umask unlink $(ZAP)
MOREPROGS = ftw8

all:	$(PROGS) $(MOREPROGS)

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99

ftw8:	ftw8.c $(LIBAPUE)
	$(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o ftw8 $(LDFLAGS) $(LDLIBS)	-std=c99

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)

include $(ROOT)/Make.libapue.inc
