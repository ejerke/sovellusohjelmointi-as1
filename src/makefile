#IDIR =../include
CC=gcc
CFLAGS=-I. #$(IDIR)

ODIR=./
#LDIR =../lib

#LIBS=-lm

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o source.o
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~
