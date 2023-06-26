#include <stdio.h>
#include <string.h>
// Reference: https://github.com/clibs/sha1
#include "sha1.h"
int main(int, char**) {
    //std::string message = "12345678";
    SHA1_CTX sha; uint8_t results[20]; int n;
    const char *buf = "12345678"; n = strlen(buf); SHA1Init(&sha); SHA1Update(&sha, (uint8_t *)buf, n); SHA1Final(results, &sha);
    /* Print the digest as one long hex value */ printf("0x"); 
    for (n = 0; n < 20; n++)
    printf("%02x", results[n]);
    putchar('\n');
    // result = 0x7c222fb2927d828af22f592134e8932480637c0d
    return 0;
}
