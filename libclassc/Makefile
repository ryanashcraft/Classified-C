
# Classified-C
# Ryan Ashcraft

VPATH = hashtable:

obj=Classified-C.o list.o hashtable.o Object.o Class.o Thread.o AutoReleasePool.o Null.o Array.o String.o MutableString.o File.o Integer.o Boolean.o Stack.o Scanner.o Printer.o Iterator.o LinkedList.o
inc=Classified-C.h list.h hashtable.h Object.h Class.h Thread.h AutoReleasePool.h Null.h Array.h String.h MutableString.h File.h Integer.h Boolean.h Stack.h Scanner.h Printer.h Iterator.h LinkedList.h
misc=Makefile
libtarget=libclassc.a
cflags=-fPIC -Wall -g -Werror -pedantic -std=c99 -DDebug -02

all: $(libtarget)

$(libtarget) : $(obj) $(misc)
	ar rcs $@ $(obj)

# $(libtarget) : $(obj) $(cbobj) $(misc)
# 	gcc $(cflags) -o $(target) $(obj) $(cbobj)

%.o : %.c %.h $(misc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(libtarget)