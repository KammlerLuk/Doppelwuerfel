#include "encrypt.h"

ALLOC_RESULT encrypt_total(const char clear_msg[], const char first_key[], const char second_key[], char **encoded_msg) {
    char *interim_result;

    if (encrypt_step(clear_msg, first_key, &interim_result) != SUCCESS) {
        return NULL_ERROR;
    }

    if (encrypt_step(interim_result, second_key, encoded_msg) != SUCCESS) {
        free(interim_result);
        return NULL_ERROR;
    }

    free(interim_result);
    return SUCCESS;
}

ALLOC_RESULT encrypt_step(const char clear_msg[], const char key[], char **encoded_msg) {
    size_t permutation_matrix_row_count, permutation_matrix_col_count, r_idx, c_idx, m_idx, sorted_structured_key_len, k_idx;
    char **permutation_matrix;
    key_element *sorted_structured_key;

    if (create_premutation_matrix(key, clear_msg, &permutation_matrix, &permutation_matrix_row_count, &permutation_matrix_col_count) != SUCCESS) 
        return NULL_ERROR;

    m_idx = 0;
    for (r_idx = 0; r_idx < permutation_matrix_row_count; r_idx++) {
        for (c_idx = 0; c_idx < permutation_matrix_col_count; c_idx++) {
            if (m_idx < strlen(clear_msg)) {
                permutation_matrix[r_idx][c_idx] = clear_msg[m_idx++];
            } else {
                permutation_matrix[r_idx][c_idx] = '\0';
            }
        }
    }

    if (sort_key(key, &sorted_structured_key, &sorted_structured_key_len) != SUCCESS) {
        destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
        return NULL_ERROR;
    }

    *encoded_msg = malloc(sizeof(char) * strlen(clear_msg));
    if (encoded_msg == NULL) {
        destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
        free(sorted_structured_key);
        return NULL_ERROR;
    }

    m_idx = 0;
    for (k_idx = 0; k_idx < sorted_structured_key_len; k_idx++) {
        for (r_idx = 0; r_idx < permutation_matrix_row_count; r_idx++) {
            if (permutation_matrix[r_idx][sorted_structured_key[k_idx].original_index] == '\0') {
                break;
            } else {
                (*encoded_msg)[m_idx++] = permutation_matrix[r_idx][sorted_structured_key[k_idx].original_index];
            }
        }
    }
    (*encoded_msg)[m_idx] = '\0';

    destroy_permutation_matrix(&permutation_matrix, permutation_matrix_row_count);
    free(sorted_structured_key);
    return SUCCESS;
}