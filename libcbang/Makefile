
# C!
# Ryan Ashcraft

#
obj=CBang.o list.o CBObject.o CBNull.o CBString.o CBInteger.o CBStack.o CBFile.o CBScanner.o
inc=CBang.h list.h CBObject.h CBNull.h CBString.h CBInteger.h CBStack.h CBFile.h CBScanner.h
misc=Makefile
libtarget=libcbang.a
cflags=-fPIC -Wall -g -Werror -pedantic -std=c99

all: $(libtarget)

$(libtarget) : $(obj) $(misc)
	ar rcs $@ $(obj)

# $(libtarget) : $(obj) $(cbobj) $(misc)
# 	gcc $(cflags) -o $(target) $(obj) $(cbobj)

%.o : %.c %.h $(misc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(libtarget)