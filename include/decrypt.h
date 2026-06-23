#ifndef DECRYPT_H_INCLUDED
#define DECRYPT_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "cipher_core.h"

ALLOC_RESULT decrypt_total(const char encoded_msg[], const char first_key[], const char second_key[], char **clear_msg);
ALLOC_RESULT decrypt_step(const char encoded_msg[], const char key[], char **clear_msg);

#endif