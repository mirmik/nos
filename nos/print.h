#ifndef NOS_PRINT_H
#define NOS_PRINT_H

/**
	@file
*/

#include <nos/io/ostream.h>
#include <nos/print/print.h>
#include <nos/print/stdtype.h>

#define PRINT(arg) nos::println(#arg ":", arg)

#endif
