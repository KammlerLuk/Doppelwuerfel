#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "cipher_core.h"

ALLOC_RESULT encrypt_total(const char clear_msg[], const char first_key[], const char second_key[], char **encoded_msg);
ALLOC_RESULT encrypt_step(const char clear_msg[], const char key[], char **encoded_msg);

#endif