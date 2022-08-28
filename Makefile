# Author: Tarun Govind Kesavamurthi
#  School: North Carolina State University
#  mail  : tkesava@ncsu.edu
# /********************************************************************************/
cc=g++
CFLAGS= -g
DEPS = hash_table.cc
OBJ = hash_table.o

%.o: %.cc $(DEPS)
	$(cc) -c -o $@ $< $(CFLAGS)

hash_table.exe: $(OBJ)
	$(cc) -o $@ $^ $(CFLAGS)
clean:
	rm -rf *.o hash_table.exe
