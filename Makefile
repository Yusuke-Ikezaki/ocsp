# Makefile

# configure env
CC = gcc
LFLAGS =
CFLAGS =

# program 
PROG1 = myshell

# header file
HDRS1 = command.h

# object file
OBJS1 = myshell.o cat.o cd.o cp.o echo.o exit.o head.o ln.o ls.o mv.o pwd.o rm.o unknown.o

# compile all
all: $(PROG1)

# test1
$(PROG1): $(OBJS1)
	$(CC) $(OBJS1) -o $@ $(LFLAGS)
$(OBJS1): $(HDRS1)

# how to compile objects
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	-rm -f $(OBJS1) *~

# clean all
veryclean:
	-rm -f $(PROG1) $(OBJS1) *~
