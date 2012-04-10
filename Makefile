objcsrc=foo.objc
src=objc.c list.c objc_null.c
obj=foo.o objc.o list.o objc_null.o
inc=objc.h list.h objc_null.h
misc=Makefile
target=objc-test
cflags=-Wall -g -Werror -pedantic -std=c99
lflags=-lpthread

all: $(target)

$(target) : $(obj) $(misc)
	gcc $(cflags) $(lflags) -o $(target) $(obj)

%.c : %.objc
	cat $< | sed -e 's/\(\&[A-Za-z][A-Za-z0-9_]*\)[ ]*= [ ]*\[\([A-Za-z][A-Za-z0-9_]*\) [ ]*\([A-Za-z0-9_-]*\)\];/objc_message_send\(\2, \"\3\", \1\);/' > $@

%.o : %.c $(misc) $(inc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(target) foo.c