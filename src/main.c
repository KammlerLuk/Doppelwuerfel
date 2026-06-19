#include <stdio.h>
#include "cipher_core.h"

int main(void) {
    size_t len, i;
    key_element *elements;
    char key[] = "HelloWorld";

    if (NULL_ERROR == sort_key(key, &elements, &len)) {
        printf("malloc returned NULL!");
        return 1;
    }

    printf("key length: %i\n", len);

    printf("letter\toriginal index\n");
    for (i = 0; i < len; i++) {
        printf("%c\t%i\n", elements[i].letter, elements[i].original_index);
    }

    free(elements);

    return 0;
}