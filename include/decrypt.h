#ifndef DECRYPT_H_INCLUDED
#define DECRYPT_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "cipher_core.h"

/**
 * Decrypt a message encrypted with two transposition keys.
 *
 * @param encoded_msg Non-empty, NUL-terminated ciphertext; input is unchanged.
 * @param first_key Non-empty, NUL-terminated first encryption key.
 * @param second_key Non-empty, NUL-terminated second encryption key.
 * @param clear_msg Output pointer receiving the allocated plaintext on
 *                  success. The caller must release it with free().
 * @return SUCCESS on success; NULL_ERROR if an allocation fails.
 * @pre All pointers must be non-NULL; the message and both keys must not be
 *      empty.
 * @note Supply keys in the same order used for encryption. The output value
 *       is only usable when SUCCESS is returned.
 */
ALLOC_RESULT decrypt_total(const char encoded_msg[], const char first_key[], const char second_key[], char **clear_msg);

/**
 * Decrypt a message encrypted with one transposition key.
 *
 * @param encoded_msg Non-empty, NUL-terminated ciphertext; input is unchanged.
 * @param key Non-empty, NUL-terminated encryption key.
 * @param clear_msg Output pointer receiving the allocated plaintext on
 *                  success. The caller must release it with free().
 * @return SUCCESS on success; NULL_ERROR if an allocation fails.
 * @pre All pointers must be non-NULL; the message and key must not be empty.
 * @note The output value is only usable when SUCCESS is returned.
 */
ALLOC_RESULT decrypt_step(const char encoded_msg[], const char key[], char **clear_msg);

#endif