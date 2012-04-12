
# C!
# Ryan Ashcraft

# vpath %.a ../libcbang
# vpath %.h ../libcbang
# vpath %.h .

obj=Foo.o MyClass.o
inc=Foo.h MyClass.h
misc=Makefile
target=Example.o
cflags=-Wall -c -g -Werror -pedantic -std=c99
lflags=-Wall -g
include=-I../libcbang/
c=gcc
lcbang= ../libcbang/libcbang.a

all: $(target)

$(target) : $(obj) $(misc) $(lcbang)
	$(c) $(lflags) $(obj) $(lcbang) -o $(target)

# .SECONDARY:
# %.c : %.cbang
# 	cat $< | sed -e 's/\([A-Za-z][A-Za-z0-9_]*\):\([A-Za-z0-9_-]*\)!\([A-Za-z0-9"() _-]*\)/cbang_message_send\(\1, \"\2\", \3)/' > $@

%.o : %.c $(misc)
	$(c) $(cflags) -c $<

clean:
	rm -f $(obj) $(target)