
# C!
# Ryan Ashcraft

# vpath %.a ../libcbang
# vpath %.h ../libcbang
# vpath %.h .

obj=MyClass.o Foo.o
inc=MyClass.h Foo.h
misc=Makefile
target=Example.o
cflags=-Wall -g -Werror -pedantic -std=c99
# include=-I../libcbang
c=gcc
lcbang= ../libcbang/libcbang.a

all: $(target)

$(target) : $(obj) $(misc) $(lcbang)
	$(c) $(lcbang) -o $(target) $(obj)

# .SECONDARY:
# %.c : %.cbang
# 	cat $< | sed -e 's/\([A-Za-z][A-Za-z0-9_]*\):\([A-Za-z0-9_-]*\)!\([A-Za-z0-9"() _-]*\)/cbang_message_send\(\1, \"\2\", \3)/' > $@

%.o : %.c $(misc) %.h
	$(c) $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(target)