#include "decrypt.h"

ALLOC_RESULT decrypt_total(const char encoded_msg[], const char first_key[], const char second_key[], char **clear_msg) {
    char *interim_result;

    if (decrypt_step(encoded_msg, second_key, &interim_result) != SUCCESS) {
        return NULL_ERROR;
    }

    if (decrypt_step(interim_result, first_key, clear_msg) != SUCCESS) {
        free(interim_result);
        return NULL_ERROR;
    }

    free(interim_result);
    return SUCCESS;
}

ALLOC_RESULT decrypt_step(const char encoded_msg[], const char key[], char **clear_msg) {
    size_t permutation_matrix_row_count, permutation_matrix_col_count, r_idx, c_idx, m_idx, sorted_structured_key_len, k_idx;
    char **permutation_matrix;
    key_element *sorted_structured_key;

    if (create_premutation_matrix(key, encoded_msg, &permutation_matrix, &permutation_matrix_row_count, &permutation_matrix_col_count) != SUCCESS) 
        return NULL_ERROR;

    if (sort_key(key, &sorted_structured_key, &sorted_structured_key_len) != SUCCESS) {
        destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
        return NULL_ERROR;
    }
    
    *clear_msg = malloc(sizeof(char) * strlen(encoded_msg));
    if (*clear_msg == NULL) {
        destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
        free(sorted_structured_key);
        return NULL_ERROR;
    }
    
    m_idx = 0;
    for (k_idx = 0; k_idx < sorted_structured_key_len; k_idx++) {
        for (r_idx = 0; r_idx < permutation_matrix_row_count; r_idx++) {
            if (r_idx == permutation_matrix_row_count - 1 && sorted_structured_key[k_idx].original_index >= strlen(encoded_msg) % sorted_structured_key_len) {
                permutation_matrix[r_idx][sorted_structured_key[k_idx].original_index] = '\0';
            } else {
                permutation_matrix[r_idx][sorted_structured_key[k_idx].original_index] = encoded_msg[m_idx++];
            }
        }
    }

    m_idx = 0;
    for (r_idx = 0; r_idx < permutation_matrix_row_count; r_idx++) {
        for (c_idx = 0; c_idx < permutation_matrix_col_count; c_idx++) {
            if (permutation_matrix[r_idx][c_idx] == '\0') {
                break;
            }
            (*clear_msg)[m_idx++] = permutation_matrix[r_idx][c_idx]; 
        }
    }    
    (*clear_msg)[m_idx] = '\0';

    destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
    free(sorted_structured_key);
    return SUCCESS;
}