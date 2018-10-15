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

OBJS = main.o weak-fun.o construct.o
LIB_OBJS = my_library.o
PIC_OBJS = pic_my_library.o

# Uncomment this line to override the weak functions
OBJS += strong-fun.o strong-construct.o

DEST = main.exe
LIB_DEST = libmy_library.so

# NOTICE: by default -pedantic forces compliance to ISO C90
CFLAGS += -Wall -pedantic -std=c99

.PHONY: main static dynamic clean

main: static

clean:
	rm *.o *.exe *.so *.a

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

dynamic: main_dynamic.exe

# NOTICE: the -L can be used only when linking, you need to export also the
# library location when launching it
main_dynamic.exe: $(OBJS) libmy_library.so
	$(LINK.o) -o $@ $(filter-out libmy_library.so,$^) -L. -lmy_library

# Position Indipendent Code will be compiled into special object names
libmy_library.so: $(PIC_OBJS)
	$(LINK.o) -shared $^ -o $@

# The -fPIC option compiles the library into a Position Indipendent Code object
pic_%.o: %.c
	$(COMPILE.c) -fPIC $^ -o $@
