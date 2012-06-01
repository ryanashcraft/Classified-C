
# Classified-C
# Ryan Ashcraft

obj=Classified-C.o list.o Object.o Class.o Null.o Array.o String.o MutableString.o File.o Integer.o Stack.o Scanner.o Printer.o Iterator.o LinkedList.o
inc=Classified-C.h list.h Object.h Class.h Null.h Array.h String.h MutableString.h File.h Integer.h Stack.h Scanner.h Printer.h Iterator.h LinkedList.h
misc=Makefile
libtarget=libclassc.a
cflags=-fPIC -Wall -g -Werror -pedantic -std=c99 -DDebug

all: $(libtarget)

$(libtarget) : $(obj) $(misc)
	ar rcs $@ $(obj)

# $(libtarget) : $(obj) $(cbobj) $(misc)
# 	gcc $(cflags) -o $(target) $(obj) $(cbobj)

%.o : %.c %.h $(misc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(libtarget)