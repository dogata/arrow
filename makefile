CC := mpicxx

SRCDIR := src
OBJDIR := obj
TARGET := bin/cstore

LIBPATH="/usr/local"
ARROW_INCLUDE=-I"${LIBPATH}/include/arrow" -I"${LIBPATH}/include/plasma"
ARROW_LIB=-L"${LIBPATH}/lib"
ARROW_LIBS=-larrow -lplasma

CFLAGS=-std=c++11 -Wall -Wno-parentheses -Wno-deprecated $(ARROW_INCLUDE) $(ARROW_LIB) $(ARROW_LIBS)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC := -I include

$(TARGET): $(OBJECTS)
	@mkdir -p ./bin
	@echo " Linking..."
	@echo " $(CC) -o $@ $^ $(CFLAGS)"; $(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@ )
	@mkdir -p $(OBJDIR)
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(OBJDIR) $(TARGET)"; $(RM) -r $(OBJDIR) $(TARGET)

.PHONY: clean