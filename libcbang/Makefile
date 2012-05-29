
# C!
# Ryan Ashcraft

#
obj=CBang.o list.o CBObject.o CBClass.o CBNull.o CBString.o CBMutableString.o CBFile.o CBInteger.o CBStack.o CBScanner.o CBPrinter.o
inc=CBang.h list.h CBObject.h CBClass.h CBNull.h CBString.h CBMutableString.h CBFile.h CBInteger.h CBStack.h CBScanner.h CBPrinter.h
misc=Makefile
libtarget=libcbang.a
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