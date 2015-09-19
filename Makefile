##################################################

# Project name
TARGET  = catch-me-if-you-can

# Compiler and flags
CC      = g++
CFLAGS  = -std=c++11 -Wall -Wextra -pedantic -g -lform -lncurses -lmenu

# Linker and flags
LINKER  = g++ -o
LFLAGS  = -std=c++11 -Wall -Wextra -pedantic -g -lform -lncurses -lmenu

# Project directories
SRCPATH = src
OBJPATH = obj
BINPATH = bin
LIBPATH = lib

# File extensions
LANGEXT = cpp
HEADEXT = hpp
LIBEXT  = a

##################################################

SOURCES  := $(wildcard $(SRCPATH)/*.$(LANGEXT))
INCLUDES := $(wildcard $(SRCPATH)/*.$(HEADEXT))
LIBS  	 := $(wildcard $(LIBPATH)/*.$(LIBEXT))
OBJECTS  := $(SOURCES:$(SRCPATH)/%.$(LANGEXT)=$(OBJPATH)/%.o)
rm       = rm -fv

$(BINPATH)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.$(LANGEXT)
	@$(CC) $(CFLAGS) -c $< -o $@ #$(LIBS)
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean: remove
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove:
	@$(rm) $(BINPATH)/$(TARGET)
	@echo "Executable removed!"
