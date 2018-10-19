# Common make options:
#
# -n | --just-print
#		Prints only the operations, as a preview, not applying them.
#
# -j [N]
#		Executes at most N jobs to compute all the actions required.
#
# -C dir
#		Executes make in a different directory.
#
# -f file
#		Uses file instead of default makefile.
#
# -d
#		Print makefile debug information.

OBJS = main.o weak_fun.o construct.o
LIB_OBJS = my_library.o
PIC_OBJS = pic_my_library.o

# Uncomment this line to override the weak functions
OBJS += strong_fun.o strong_construct.o

# To link dynamically we use a different main and the same object files
DYN_OBJS = main_dll.o weak_fun.o construct.o strong_fun.o strong_construct.o

DEST = main.exe
LIB_DEST = libmy_library.so

# NOTICE: by default -pedantic forces compliance to ISO C90
CFLAGS += -Wall -pedantic -std=c99

.PHONY: main all static shared dynamic clean

main: static

all: static shared dynamic

clean:
	rm -f *.o *.exe *.so *.a

# Generic compilation rule
%.o: %.c
	$(COMPILE.c) $^ -o $@





# From now on things may get pretty confusing, I'll try to be as clean as possible





################ STATIC LIBRARY ################
# Basically a set of object files put together with a .a extension (they don't
# need to be compiled with -fPIC).

static: main_static.exe

# The filter-out is needed to remove the library from $^ dependencies
main_static.exe: $(OBJS) libmy_library.a
	$(LINK.o) -o $@ $(filter-out libmy_library.a,$^) -L. -lmy_library

# Packing object files into archive (there is only one object file, but whatever)
libmy_library.a: $(LIB_OBJS)
	ar rcs $@ $^





################ SHARED LIBRARY ################
# This allows a smaller executable file, but requires the shared library to b
# available when the program is run

shared: main_shared.exe

# NOTICE: the -L can be used only when linking, you need to export also the
# library location when launching it
main_shared.exe: $(OBJS) libmy_library.so
	$(LINK.o) -o $@ $(filter-out libmy_library.so,$^) -L. -lmy_library

# Position Indipendent Code will be compiled into special object names
libmy_library.so: $(PIC_OBJS)
	$(LINK.o) -shared $^ -o $@

# The -fPIC option compiles the library into a Position Indipendent Code object
pic_%.o: %.c
	$(COMPILE.c) -fPIC $^ -o $@

# To then get the library correctly when launching the application there are some
# different ways:
#
# 1) Put the shared library file within a standard folder, such as /lib or an
#    equivalent distribution-specific folder
# 2) Change the value of the LD_LIBRARY_PATH to point also to the location of
#    your shared library like this:
#    export LD_LIBRARY_PATH=<absolute_path>:$LD_LIBRARY_PATH
# 3) Using the -rpath, which allows to embed the library location information
#    hardcoded inside the executable itself (not recommended, since this is not
#    flexible at all)
#
#    gcc -o myprog main.c -L<path> -lmodule -Wl, -rpath=<path>
#
#  or
#
#    gcc −o myprog main.c −L<path> −lmodule −Xlinker −rpath −Xlinker <path>


################ DYNAMICALLY LINKED LIBRARY ################
# With dynamically linked libraries, you do not need to link together the main
# with the library, but it is linked at runtime: it is a sort of plug-in
# architecture.

# This time, the main is compiled and linked by itself, since the library is
# dynamically loaded later on, but the main source code must be modified.

dynamic: main_dynamic.exe

# The library is compiled using the same rules in the shared example
# Notice that it is not strictly necessary to state that the dynamically linked
# program will require said library

# The last argument is because the new main must be linked against libdl.so
main_dynamic.exe: $(DYN_OBJS) libmy_library.so
	$(LINK.o) -o $@ $(filter-out libmy_library.so,$^) -ldl

# To run the program then use the following command, since it expects the library
# path as first command-line argument
#
# ./main_dynamic.exe "$(pwd)/libmy_library.so"




############################# ADDITIONAL RESOURCES #############################

# The following commands can be used to debug and check:

# ldd <file>
# Prints all library or program dependencies and prints whether the linker is
# able to resolve them right now or not

# objdump -t <main.o>
# Print the symbol table entries of the file. The format of the output depends
# upon the format of the file being dumped. This can be used to check which
# symbols are exported by this file and which are the required ones.

# objdump -d <main.o>
# Display the assembler mnemonics for the machine instructions from objfile.
# This option only disassembles those sections which are expected to contain
# instructions. For a whole disassembly use -D.
