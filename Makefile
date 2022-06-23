OUTDIR = ./bin
SRCDIR = ./src
OBJDIR = ./obj
CC = gcc
CFLAGS = -g -Wall -Werror


cat: obj/cat.o
	$(CC) $(CFLAGS) $(OBJDIR)/cat.o -o $(OUTDIR)/cat

wc: obj/wc.o
	$(CC) $(CFLAGS) $(OBJDIR)/wc.o -o $(OUTDIR)/wc
	
ls: obj/ls.o
	$(CC) $(CFLAGS) $(OBJDIR)/ls.o -o $(OUTDIR)/ls

obj/cat.o: src/cat.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/cat.c -o $(OBJDIR)/cat.o

obj/wc.o: src/wc.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/wc.c -o $(OBJDIR)/wc.o

obj/ls.o: src/ls.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/ls.c -o $(OBJDIR)/ls.o 

clean:
	rm -f $(OBJDIR)/* $(OUTDIR)/*
