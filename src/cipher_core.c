#include "cipher_core.h"

ALLOC_RESULT sort_key(const char key[], key_element **sorted_structured_key, size_t *sorted_structured_key_len) {
    size_t key_index;

    *sorted_structured_key_len = strlen(key);
    *sorted_structured_key = malloc(sizeof(key_element) * (*sorted_structured_key_len));
    if (*sorted_structured_key == NULL) {
        return NULL_ERROR;
    }

    for (key_index = 0; key_index < *sorted_structured_key_len; key_index++) {
        (*sorted_structured_key)[key_index].letter = tolower(key[key_index]);
        (*sorted_structured_key)[key_index].original_index = key_index;
    }

    qsort((*sorted_structured_key), (*sorted_structured_key_len), sizeof(key_element), compare_key_elements_for_sorting);

    return SUCCESS;
}

int compare_key_elements_for_sorting(const void *a, const void *b) {
    key_element *ea = (key_element *)a;
    key_element *eb = (key_element *)b;

    if (ea->letter != eb->letter)
        return ea->letter - eb->letter;

    return (int)ea->original_index - (int)eb->original_index;
}

ALLOC_RESULT create_premutation_matrix(const char key[], const char msg[], char ***permutation_matrix, size_t *permutation_matrix_row_count, size_t *permutation_matrix_col_count) {
    size_t key_len, msg_len, row_index, b_row_index;

    key_len = strlen(key);
    msg_len = strlen(msg);

    *permutation_matrix_col_count = key_len;
    *permutation_matrix_row_count = msg_len / key_len;

    if (msg_len % key_len != 0) 
        (*permutation_matrix_row_count)++;

    *permutation_matrix = malloc(sizeof(char*) * (*permutation_matrix_row_count));
    if (*permutation_matrix == NULL) {
        return NULL_ERROR;
    }

    for (row_index = 0; row_index < (*permutation_matrix_row_count); row_index++) {
        (*permutation_matrix)[row_index] = malloc(sizeof(char) * (*permutation_matrix_col_count));
        if ((*permutation_matrix)[row_index] == NULL) {
            for (b_row_index = 0; b_row_index < row_index; b_row_index++) {
                free((*permutation_matrix)[b_row_index]);
            }
            free(*permutation_matrix);
            return NULL_ERROR;
        }
    }

    return SUCCESS;
}

void destroy_permutation_matrix(char ***permutation_matrix, size_t permutation_matrix_row_count) {
    size_t row_index;
    
    for (row_index = 0; row_index < permutation_matrix_row_count; row_index++) {
        free((*permutation_matrix)[row_index]);   
    }
    free(*permutation_matrix);
}