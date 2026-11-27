#ifndef CIPHER_CORE_H_INCLUDED
#define CIPHER_CORE_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * One key character and its position in the original key.
 * The position determines the order of columns for duplicate characters.
 */
typedef struct _key_element {
    char letter;
    size_t original_index;
} key_element; 

/** Result codes used by operations that allocate memory. */
typedef enum _ALLOC_RESULT {
    SUCCESS,
    NULL_ERROR
} ALLOC_RESULT;

/**
 * Create a sorted, case-folded representation of a key.
 *
 * @param key Non-empty, NUL-terminated key; input is not modified. Characters
 *            must be valid arguments to tolower().
 * @param sorted_structured_key Output pointer receiving an allocated array
 *                              on success; caller releases it with free().
 * @param sorted_structured_key_len Output receiving the array element count.
 * @return SUCCESS on success; NULL_ERROR if allocation fails.
 * @pre All pointers must be non-NULL and key must not be empty.
 */
ALLOC_RESULT sort_key(const char key[], key_element **sorted_structured_key, size_t *sorted_structured_key_len);

/**
 * Compare two key elements for use as a qsort() comparator.
 *
 * @param a Pointer to the first key_element.
 * @param b Pointer to the second key_element.
 * @return Negative if a sorts first, positive if b sorts first, or zero if
 *         they compare equal. Original positions break ties between letters.
 * @pre Both arguments must point to valid key_element values.
 */
int compare_key_elements_for_sorting(const void *a, const void *b);

/**
 * Allocate a matrix sized for a message and a transposition key.
 *
 * The key length determines the column count; the message length determines
 * the number of rows.
 *
 * @param key Non-empty, NUL-terminated key; input is not modified.
 * @param msg Non-empty, NUL-terminated message; input is not modified.
 * @param permutation_matrix Output pointer receiving the allocated matrix
 *                           on success. Release it with
 *                           destroy_permutation_matrix().
 * @param permutation_matrix_row_count Output receiving the row count.
 * @param permutation_matrix_col_count Output receiving the column count.
 * @return SUCCESS on success; NULL_ERROR if an allocation fails.
 * @pre All pointers must be non-NULL; key and msg must not be empty.
 */
ALLOC_RESULT create_premutation_matrix(const char key[], const char msg[], char ***permutation_matrix, size_t *permutation_matrix_row_count, size_t *permutation_matrix_col_count);

/**
 * Free a matrix returned by create_premutation_matrix().
 *
 * @param permutation_matrix Address of the matrix pointer to free.
 * @param permutation_matrix_row_count Number of rows in the matrix.
 * @pre The pointer must refer to a successfully allocated matrix and its
 *      matching row count.
 * @post The matrix and its rows are freed; do not use the pointer afterward.
 */
void destroy_permutation_matrix(char ***permutation_matrix, size_t permutation_matrix_row_count);

#endif