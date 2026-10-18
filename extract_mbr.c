#include <stdint.h>
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("MBR1.dd", "rb");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    unsigned char buffer[16];
    size_t n;
    size_t offset = 0;

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        // optional: print offset
        printf("%08zx: ", offset);

        for (size_t i = 0; i < n; i++)
            printf("%02x ", buffer[i]);

        printf("\n");
        offset += n;
    }

    if (ferror(fp))
        perror("fread");

    fclose(fp);
    return 0;
}