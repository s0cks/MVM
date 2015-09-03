#ifndef MICROVM_MVN_PRIVATE_H
#define MICROVM_MVN_PRIVATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#ifndef __attribute__
#define __attribute__(x)
#endif

typedef unsigned char byte;

char* mvm_bool_to_str(byte b);

void mvm_assert(int exp, char* msg);

#endif