#
# Students' Makefile for the Malloc Lab
#
TEAM = TIGERS 
VERSION = 1

CC = gcc
CFLAGS = -Wall -O2 -m32
# - Use "sudo apt install gcc-multilib" OR "sudo apt install gcc-9-multilib"
#   depending on the version of gcc installed to install 32 bit libraries.
# - 32 bit environment (i.e. "-m32" flag) is required because address space
#   in 64 bit environment will be too huge to perform the stress test.

OBJS = mdriver.o mm.o memlib.o fsecs.o fcyc.o clock.o ftimer.o
OBJS1 = mdriver.o mm1.o memlib.o fsecs.o fcyc.o clock.o ftimer.o
OBJS2 = mdriver.o mm2.o memlib.o fsecs.o fcyc.o clock.o ftimer.o

mdriver: $(OBJS) $(OBJS1) $(OBJS2)
	$(CC) $(CFLAGS) -o mdriver $(OBJS)
	$(CC) $(CFLAGS) -o mdriver1 $(OBJS1)
	$(CC) $(CFLAGS) -o mdriver2 $(OBJS2)
	

mdriver.o: mdriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h
memlib.o: memlib.c memlib.h
mm.o: mm.c mm.h memlib.h
mm1.o: mm1.c mm.h memlib.h
mm2.o: mm2.c mm.h memlib.h
fsecs.o: fsecs.c fsecs.h config.h
fcyc.o: fcyc.c fcyc.h
ftimer.o: ftimer.c ftimer.h config.h
clock.o: clock.c clock.h

clean:
	rm -f *~ *.o mdriver
	rm -f *~ *.o mdriver1
	rm -f *~ *.o mdriver2


