CC := g++
SRCDIR := src
BUILDDIR := build
DEPDIR := $(BUILDDIR)/deps
TARGET := bin/main

CFLAGS = -g --std=c++11 -D _DEBUG -O2 -fsanitize=undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,nullability -fsanitize=address
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
LIB = -L lib -framework OpenGL -lglew -lSDL2 -lSDL2_image
INC = -I include -I src

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
DEPS := $(patsubst $(SRCDIR)/%, $(DEPDIR)/%, $(SOURCES:.$(SRCEXT)=.d))

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $(CFLAGS) $(LIB) -o $@ $^"; $(CC) $(CFLAGS) $(LIB) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d | $(BUILDDIR) $(DEPDIR)
	@mkdir -p $(dir $@)

	@echo "$(CC) $(DEPFLAGS) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(DEPFLAGS) $(CFLAGS) $(INC) -c -o $@ $<

$(DEPS): ; @mkdir -p $(dir $@)

$(BUILDDIR): ; @mkdir -p $@
$(DEPDIR): ; @mkdir -p $@

include $(wildcard $(DEPS))

.PHONY: clean run
clean:
	@echo "Cleaning..."
	@echo "$(RM) -r $(BUILDDIR) $(OBJECTS)"; $(RM) -r $(BUILDDIR) $(OBJECTS)

run: $(TARGET)
	$(TARGET)