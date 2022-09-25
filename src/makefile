# Compiler version and flags
CC=gcc
CFLAGS=-Wall -pedantic -I $(IDIR)

# Directories
ODIR=./obj
LDIR =../lib
IDIR =../include
# # Macro for common libraries: math
# LIBS=-lm

# List all .h and .c files
_DEPS = header.h
_OBJ = main.o source.o server.o client.o

# Create directories for the header files
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Create the directories for object files
# using the object file list and object dir
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Create dependencies between the .o, .c and .h files
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile command
run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# clean
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
