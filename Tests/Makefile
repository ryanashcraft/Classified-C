
# Classified-C
# Ryan Ashcraft

obj=main.o Test.o StringTest.o
inc=Test.h StringTest.h
misc=Makefile
target=Tests.o
cflags=-Wall -c -g -Werror -pedantic -std=c99 -DDebug
lflags=-Wall -g -DDebug
libclassc=../libclassc/
include=-I$(libclassc)
c=gcc
lcbang= $(libclassc)/libclassc.a

all: $(target)

clean-all:
	cd $(libclassc); make clean; make; cd ../Tests; make clean; make;

valgrind-clean: clean-all
	valgrind --leak-check=full --dsymutil=yes ./$(target)

$(target) : $(obj) $(misc) $(lcbang)
	$(c) $(lflags) $(obj) $(lcbang) -o $(target)

%.o : %.c $(misc)
	$(c) $(cflags) -c $<

clean:
	rm -f $(obj) $(target)

time:
	for i in {1..10} ; do \
	time ./$(target); \
	done

run-clean: clean-all
	./$(target)

gdb-clean: clean-all
	gdb ./$(target)

time-clean: clean-all time
