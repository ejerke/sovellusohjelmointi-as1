#IDIR =../include
CC=gcc
CFLAGS=-I. #$(IDIR)

ODIR=obj
#LDIR =../lib

#LIBS=-lm

DEPS = header.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = main.o source.o
#OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aja: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
