
# C!
# Ryan Ashcraft

# cbsrc=foo.cbang
cb=foo.c
cbo=foo.o

src=cbang.c list.c cbobject.c cbnull.c cbstring.c cbinteger.c
obj=cbang.o list.o cbobject.o cbnull.o cbstring.o cbinteger.o
inc=cbang.h list.h cbobject.h cbnull.h cbstring.h cbinteger.h
misc=Makefile
target=cb-foo.out
cflags=-Wall -g -Werror -pedantic -std=c99
lflags=-lpthread

all: $(target)

$(target) : $(obj) $(cbo) $(misc)
	gcc $(cflags) $(lflags) -o $(target) $(obj) $(cbo)

.SECONDARY:

%.c : %.cbang
	cat $< | sed -e 's/\([A-Za-z][A-Za-z0-9_]*\):\([A-Za-z0-9_-]*\)!\([A-Za-z0-9"() _-]*\)/cbang_message_send\(\1, \"\2\", \3)/' > $@

%.o : %.c $(misc) $(inc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(cbo) $(target) foo.c