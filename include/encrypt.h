#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "cipher_core.h"

/**
 * Encrypt a message by applying two transposition steps in sequence.
 *
 * @param clear_msg Non-empty, NUL-terminated plaintext; input is not modified.
 * @param first_key Non-empty, NUL-terminated key for the first step.
 * @param second_key Non-empty, NUL-terminated key for the second step.
 * @param encoded_msg Output pointer receiving the allocated ciphertext on
 *                    success. The caller must release it with free().
 * @return SUCCESS on success; NULL_ERROR if an allocation fails.
 * @pre All pointers must be non-NULL; the message and both keys must not be
 *      empty.
 * @note The output value is only usable when SUCCESS is returned.
 */
ALLOC_RESULT encrypt_total(const char clear_msg[], const char first_key[], const char second_key[], char **encoded_msg);

/**
 * Encrypt a message using one transposition key.
 *
 * @param clear_msg Non-empty, NUL-terminated plaintext; input is not modified.
 * @param key Non-empty, NUL-terminated key.
 * @param encoded_msg Output pointer receiving the allocated ciphertext on
 *                    success. The caller must release it with free().
 * @return SUCCESS on success; NULL_ERROR if an allocation fails.
 * @pre All pointers must be non-NULL; the message and key must not be empty.
 * @note The output value is only usable when SUCCESS is returned.
 */
ALLOC_RESULT encrypt_step(const char clear_msg[], const char key[], char **encoded_msg);

#endif