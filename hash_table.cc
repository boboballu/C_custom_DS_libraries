#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

// local .h files
#include "hash_table.h"

// ---------------------------- All Function definition goes here ------------------------------- //
// Note: if a class uses templates, keep both the declaration and definition in the same file
// Else there will be linking errors
// Theory:
// [1] The template class and the member functions are created during the compilation only if the
// the class object declaration with the template datatypes are specified in a cc file.
// Hence, if 2 cc files have 2 class object declarations, the template will create separate class
// functions for those 2 object declarations.
// [2] A regular class class function definitions should be done ic cc files,
// they are created when the class function defenitions are compiled.
// ----------------------------------------------------------------------------------------------//