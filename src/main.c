#include <stdio.h>
#include "encrypt.h"

int main(void) {
    char *encoded_msg;
    char clear_msg[] = "HelloWorld";
    char first_key[] = "Tree";
    char second_key[] = "Bee";

    if (encrypt_total(clear_msg, first_key, second_key, &encoded_msg) == NULL_ERROR) {
        printf("FUCK\n");
    } else {
        printf("%s\n", encoded_msg);
        free(encoded_msg);
    }

    return 0;
}