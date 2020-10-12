CC = gcc

SDIR = src
IDIR = src
ODIR = bin

TARGET = app

CFLAGS = -Wall -Wint-conversion -g
LDFLAGS = -lm -lpthread

RM = rm -rf
MKDIR = mkdir

SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

# Get list of object files, with paths
OBJECTS := $(addprefix $(ODIR)/,$(SOURCES:%.c=%.o))

all: $(TARGET)

$(ODIR)/%.o: %.c
	$(MKDIR) -p $(@D) 
	$(CC) $(CFLAGS) -c -o $@ $< -I$(IDIR) $(LDFLAGS) 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(ODIR)/$(TARGET) $(LDFLAGS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

.PHONY: clean all
