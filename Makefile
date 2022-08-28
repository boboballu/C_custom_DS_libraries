# Author: Tarun Govind Kesavamurthi
#  School: North Carolina State University
#  mail  : tkesava@ncsu.edu
# /********************************************************************************/
cc=g++
CFLAGS= -g
DEPS = hash_table.cc
OBJ = hash_table.o

# Makefile rules:
# tab should be used for indentation.
# $@ evaluates to target name
# $< evaluates to library.cpp first and main.cpp second. one by one
# $^ evaluates to library.cpp main.cpp
# %.o: %.cc $(ccFs) # is the placeholder. {library, main}

%.o: %.cc $(DEPS)
	$(cc) -c -o $@ $< $(CFLAGS)

hash_table.exe: $(OBJ)
	$(cc) -o $@ $^ $(CFLAGS)
clean:
	rm -rf *.o hash_table.exe
