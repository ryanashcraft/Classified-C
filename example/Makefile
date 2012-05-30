
# C!
# Ryan Ashcraft

# vpath %.a ../libcbang
# vpath %.h ../libcbang
# vpath %.h .

obj=Foo.o FooClass.o
inc=Foo.h FooClass.h
misc=Makefile
target=Example.o
cflags=-Wall -c -g -Werror -pedantic -std=c99 -DDebug
lflags=-Wall -g -DDebug
include=-I../libcbang/
c=gcc
lcbang= ../libcbang/libcbang.a

all: $(target)

clean-all:
	cd ../libcbang; make clean; make; cd ../example; make clean; make;

run-clean: clean-all
	./$(target)

gdb-clean: clean-all
	gdb ./$(target)

valgrind-clean: clean-all
	valgrind --leak-check=full ./$(target)

$(target) : $(obj) $(misc) $(lcbang)
	$(c) $(lflags) $(obj) $(lcbang) -o $(target)

# .SECONDARY:
# %.c : %.cbang
# 	cat $< | sed -e 's/\([A-Za-z][A-Za-z0-9_]*\):\([A-Za-z0-9_-]*\)!\([A-Za-z0-9"() _-]*\)/cbang_message_send\(\1, \"\2\", \3)/' > $@

%.o : %.c $(misc)
	$(c) $(cflags) -c $<

clean:
	rm -f $(obj) $(target)