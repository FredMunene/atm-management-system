CC = gcc
CFLAGS = -Wall -Wextra

SRCDIR = src
#  dir for exec
BINDIR = bin
# dir for objects
OBJDIR = obj
# list all source code files
SRCFILES = $(wildcard $(SRCDIR)/*.c)
# list all objects files '.o'
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))
EXECUTABLE = atm

.PHONY: all clean directories
#  directories exists >> creates an executable
all: directories $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJFILES) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJFILES) -o $@
#  compiles each '.c' file into a '.o' file
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
# ensures directories exists
directories: | $(BINDIR) $(OBJDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)