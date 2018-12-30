CC := g++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := lib/libBromine.a

CLFAGS := -g --std=c++11 -D _DEBUG

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
LIB := -L lib -lSDL2
INC := -I include
INCLUDES := $(shell find include -type f -name *.h)

TEST_TARGET := bin/test
TEST_SOURCES := $(shell find $(TESTDIR)/$(SRCDIR) -type f -name *.$(SRCEXT))
TEST_OBJECTS := $(patsubst $(TESTDIR)/$(SRCDIR)/%, $(TESTDIR)/$(BUILDDIR)/%, $(TEST_SOURCES:.$(SRCEXT)=.o))
TEST_LIB := -L lib -lBromine -lSDL2 -lSDL2_image
TEST_INC := -I $(TESTDIR)/include -I include

$(TARGET): $(OBJECTS) $(INCLUDES)
	@echo " Archiving..."
	@echo " ar cru $@ $^"; ar cru $@ $^

# TODO: Rewrite this so it's not defined explicitly
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR) $(BUILDDIR)/Trait $(BUILDDIR)/Node
	@echo " $(CC) $(CLFAGS) $(INC) -c -o $@ $<"; $(CC) $(CLFAGS) $(INC) -c -o $@ $<


$(TEST_TARGET): $(TARGET) $(TEST_OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TEST_TARGET) $(TEST_LIB)"; $(CC) $^ -o $(TEST_TARGET) $(TEST_LIB)

$(TESTDIR)/$(BUILDDIR)/%.o: $(TESTDIR)/$(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTDIR)/$(BUILDDIR)
	@echo " $(CC) $(CLFAGS) $(TEST_INC) -c -o $@ $<"; $(CC) $(CLFAGS) $(TEST_INC) -c -o $@ $<

test: $(TARGET) $(TEST_TARGET)

.PHONY: clean
clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(BUILDDIR) $(TEST_TARGET)"; $(RM) -r $(BUILDDIR) $(TEST_TARGET)