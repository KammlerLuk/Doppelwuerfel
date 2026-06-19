#ifndef CIPHER_CORE_H_INCLUDED
#define CIPHER_CORE_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _key_element {
    char letter;
    size_t original_index;
} key_element; 

typedef enum _ALLOC_RESULT {
    SUCCESS,
    NULL_ERROR
} ALLOC_RESULT;

ALLOC_RESULT sort_key(const char key[], key_element **sorted_structured_key, size_t *sorted_structured_key_len);
int compare_key_elements_for_sorting(const void *a, const void *b);
ALLOC_RESULT create_premutation_matrix(const char key[], const char msg[], char ***permutation_matrix, size_t *permutation_matrix_row_count, size_t *permutation_matrix_col_count);
void destroy_permutation_matrix(char ***permutation_matrix, size_t permutation_matrix_row_count);

#endif