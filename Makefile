##### DIRECTORIES

# sources (src)
SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# objects (obj)
OBJDIR := obj
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# assembly files
ifeq ($(GEN_ASM), 1)

ASMS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.s,$(SRCS))

else

ASMS := 

endif

# bin (bin)
BINDIR := bin

# target
ifdef NAME
	TARGET := $(BINDIR)/$(NAME)
else
	TARGET := $(BINDIR)/bin.out
endif

##### SETTING COMPILER

# system bitness
N_BITS = $(shell getconf LONG_BIT)

ifeq ($(N_BITS),32)
	BITS_OPTION = -m32
else
	BITS_OPTION = -m64
endif

# compiler used
CXXC := g++

## COMPILER FLAGS

# $(BITS_OPTION):	Set bitness option based on system
# -fPIC:			Generate position-independent code (PIC)
# -fexceptions:		Enable exception handling
# -std=c++17:		Use C++17 standard
# -MMD:         	Generate dependency files for make

CXXCFLAGS := $(BITS_OPTION) -fPIC -fexceptions -std=c++17 -MMD

## LINKER FLAGS

# -lm:			Link against the math library
# -lpthread:	Link against the pthread library

CXXCLFLAGS := -lm -lpthread


ifeq ($(DEBUG), 1)

## DEBUG FLAGS

# -DDEBUG:            	Define the DEBUG macro
# -g3:                	Generate debugging information with maximum detail
# -Wall:              	Enable all standard warnings
# -Wextra:            	Enable extra warnings
# -Wpedantic:         	Issue all the warnings demanded by strict ISO C and ISO C++
# -Wsign-conversion:  	Warn on implicit conversions that may change the sign of an integer value
# -fmax-errors=1:     	Limit the number of errors to 1
# -Wfatal-errors:     	Stop after the first error
# -D_GLIBCXX_DEBUG:		Enable extra debugging checks for the GNU C++ library

CXXCFLAGS += -DDEBUG -g3 -Wall -Wextra -Wpedantic -Wsign-conversion -fmax-errors=1 \
			 -Wfatal-errors -D_GLIBCXX_DEBUG -fsanitize=undefined -fsanitize=address

# -fsanitize=undefined: Enable undefined behavior sanitizer
# -fsanitize=address:	Enable address sanitizer

CXXCLFLAGS += -fsanitize=address -fsanitize=undefined

else

## PERFORMANCE FLAGS

# -O3:			Enable all optimization flags
# -DNDEBUG:     Disable debugging macros

CXXCFLAGS += -O3 -DNDEBUG

endif


## ASSEMBLY FLAGS

# -S:				Compile only, generating assembly code
# -fverbose-asm:	Add extra comments to assembly code

ASMFLAGS := -S -fverbose-asm


## PROFILING FLAGS

# -pg:	Enable profiling information generation

ifeq ($(PROFILE), 1)

CXXCFLAGS += -pg

endif


all: mkdirs mode $(TARGET) $(ASMS)
	@echo "\n\033[1;32m[>>] Build complete: $(TARGET) ($$(stat -c%s $(TARGET)) bytes)\033[0m\n"


##### GENERATE ASSEMBLY FILES

ifeq ($(GEN_ASM), 1)

$(OBJDIR)/%.s: $(SRCDIR)/%.cpp
	@echo "\n\033[1;45m[%] Generating verbose assembly file: $@\033[0m"
	$(CXXC) $(CXXCFLAGS) -S -fverbose-asm $< -o $@

endif


##### COMPILE AND LINK C++

# compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "\033[1;36m[+] Compiling: $<\033[0m"
	$(CXXC) -c $< -o $@ $(CXXCFLAGS)


# linking the target executable
$(TARGET): $(OBJS)
	@echo "\n\033[1;34m[-]  Linking objects to create executable: $@\033[0m"
	$(CXXC) -o $@ $(OBJS) $(CXXCLFLAGS)


.PHONY: clean all rebuild mode run mkdirs


##### UTILS RULES

# clean and build the project
rebuild: clean all

# log the mode
mode:
ifeq ($(DEBUG), 1)
	@echo "\033[1;41m[!]  DEBUG mode.\033[0m\n"
else
	@echo "\033[1;42m[!]  PERFORMANCE mode.\033[0m\n"
endif


# compile and run
run: all
	@echo "\033[1;35m[$$]  Running: .$(TARGET)\033[0m\n"
	./$(TARGET) $(ARGS)


# print size of the target executable in KB
size: $(TARGET)
	@echo "\033[1;33m[>>] Size of $(TARGET): \033[1;32m$$(du -k $(TARGET) | cut -f1) KB\033[0m"


mkdirs:
	@echo "\n\033[1m[*]  Making directories...\033[0m\n"
	@mkdir -p $(OBJDIR) $(SRCDIR) $(BINDIR)
# 	recreates the src folder structure into the obj folder
	@find -L $(SRCDIR) -type d -not -path "$(SRCDIR)" | sed -e "s|$(SRCDIR)/|$(OBJDIR)/|" | xargs -I {} mkdir -p {}


# clean up
clean:
	@echo "\033[1;33m[x]  Cleaning target...\033[0m"
	rm -f $(TARGET)
	@echo "\033[1;33m[x]  Cleaning objects...\033[0m"
	rm -f $(OBJS)
	@echo "\033[1;33m[x]  Cleaning dependency files for make...\033[0m"
	rm -f $(wildcard $(OBJDIR)/*.d)
	@echo "\033[1;33m[x]  Cleaning assembly files...\033[0m"
	rm -f $(wildcard $(OBJDIR)/*.s)
