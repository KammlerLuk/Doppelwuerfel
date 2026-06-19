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