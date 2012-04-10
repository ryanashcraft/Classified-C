
# C!
# Ryan Ashcraft

# cbsrc=foo.cbang
cb=foo.c
cbo=foo.o

src=CBang.c list.c CBObject.c CBNull.c CBString.c CBInteger.c
obj=CBang.o list.o CBObject.o CBNull.o CBString.o CBInteger.o
inc=CBang.h list.h CBObject.h CBNull.h CBString.h CBInteger.h
misc=Makefile
target=foo.out
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
	rm -f $(obj) $(cbo) $(target)