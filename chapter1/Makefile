ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	ls1 mycat getcputc hello shell1 testerror uidgid shell2
#getcputc hello ls1 mycat shell1 shell2 testerror uidgid

all:	$(PROGS)

$(PROGS):	$(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS) -std=c99
# 不指定 -std=99，会报错不允许使用 // 注释，C++ style comments are not allowed in ISO C90

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
