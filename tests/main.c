#include <stdio.h>
#include "encrypt.h"
#include "decrypt.h"

int main(void) {
    char *encoded_msg, *cleared_msg;
    char clear_msg[] = "Hello World";
    char first_key[] = "Tree";
    char second_key[] = "Lee";

    if (encrypt_total(clear_msg, first_key, second_key, &encoded_msg) == NULL_ERROR) {
        printf("FUCK\n");
        return 1;
    } else {
        printf("%s\n", encoded_msg);
    }

    if (decrypt_total(encoded_msg, first_key, second_key, &cleared_msg) == NULL_ERROR) {
        printf("FUCK\n");
        free(encoded_msg);
        return 2;
    } else {
        printf("%s\n", cleared_msg);
        free(cleared_msg);
        free(encoded_msg);
    }
    
    return 0;
}