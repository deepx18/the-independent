#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)str, strlen(str), output);
}

bool hashcmp(unsigned char h1[SHA256_DIGEST_LENGTH], unsigned char h2[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) if (h1[i] != h2[i]) return false;
    return true;
}



void go_rebuild_urself(void) {

    FILE *file = fopen(__FILE__, "rb");
    if (file == NULL) goto terminate;

    char *buf = malloc(BUFFER_SIZE);
    fread(buf, BUFFER_SIZE, 1, file);

    FILE *old_file = fopen("main.old", "rb");
    if (old_file == NULL) {
        FILE *old_file_new = fopen("main.old", "wb");
        fprintf(old_file_new, "%s", buf);
        fclose(old_file_new);
        goto terminate;
    }

    char *old_buf = malloc(BUFFER_SIZE);
    fread(old_buf, BUFFER_SIZE, 1, old_file);



    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256(buf, hash);


    unsigned char old_hash[SHA256_DIGEST_LENGTH];
    sha256(old_buf, old_hash);

    if (!hashcmp(old_hash, hash)) {
        int res = system("gcc -L/usr/lib -lcrypto -o main main.c /usr/lib/x86_64-linux-gnu/libcrypto.a");
        printf("[INFO] Program has just rebuilt it self !\n");
        FILE *old_file_new = fopen("main.old", "wb");
        fprintf(old_file_new, "%s", buf);
        fclose(old_file_new);
        // system("./main");
    };

    goto terminate;

terminate:
    if (old_file) fclose(old_file);
    if (file) fclose(file);
    return;
}


int main() {
    go_rebuild_urself();
    printf("Hello, Planet!\n");
    return 0;
}
