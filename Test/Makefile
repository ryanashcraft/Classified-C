
# Classified-C
# Ryan Ashcraft

obj=TestMain.o Test.o TestCase.o
inc=Test.h TestCase.h
misc=Makefile
target=UnitTests.o
cflags=-Wall -c -g -Werror -pedantic -std=c99 -DDebug
lflags=-Wall -g -DDebug
libclassc=../libclassc/
include=-I$(libclassc)
c=gcc
lcbang= $(libclassc)/libclassc.a

all: $(target)

clean-all:
	cd $(libclassc); make clean; make; cd ../Test; make clean; make;

run-clean: clean-all
	./$(target)

gdb-clean: clean-all
	gdb ./$(target)

valgrind-clean: clean-all
	valgrind --leak-check=full ./$(target)

$(target) : $(obj) $(misc) $(lcbang)
	$(c) $(lflags) $(obj) $(lcbang) -o $(target)

%.o : %.c $(misc)
	$(c) $(cflags) -c $<

clean:
	rm -f $(obj) $(target)