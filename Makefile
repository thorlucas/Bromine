CC := g++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := bin/main

CLFAGS := -g --std=c++11 -D _DEBUG

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
LIB := -L lib -lSDL2 -lSDL2_image
INC := -I include
INCLUDES := $(shell find include -type f -name *.h)

$(TARGET): $(OBJECTS) $(INCLUDES)
	@echo " Linking..."
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# TODO: Rewrite this so it's not defined explicitly
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " mkdir -p $(dir $@)"
	@mkdir -p $(dir $@)

	@echo " $(CC) $(CLFAGS) $(INC) -c -o $@ $<"; $(CC) $(CLFAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(OBJECTS)"; $(RM) -r $(BUILDDIR) $(OBJECTS)