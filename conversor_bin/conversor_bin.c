#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint32_t;

#define BIT_COUNT 15
#define TABSIZE 4096

/* Example table (shortened for readability) */
const unsigned short sintab[TABSIZE] = {
    16384, 16409, 16434, 16459 /* ... fill as needed ... */
};

/* Bit arrays */
unsigned int bit_sintab[BIT_COUNT * TABSIZE];
uint32_t cmar_sintab[BIT_COUNT * TABSIZE];

/* Convert sintab values into flat bit_sintab (MSB first) */
void populate_bit_sintab(void) {
    for (size_t i = 0; i < TABSIZE; ++i) {
        unsigned short v = sintab[i];
        for (int b = 0; b < BIT_COUNT; ++b) {
            bit_sintab[i * BIT_COUNT + b] = (v >> (BIT_COUNT - 1 - b)) & 1u;
        }
    }
}

/* Convert bit_sintab into CMAR-compatible values */
void populate_cmar_sintab(void) {
    for (size_t i = 0; i < BIT_COUNT * TABSIZE; ++i) {
        cmar_sintab[i] = bit_sintab[i] ? 0x00002000 : 0x00000000;
    }
}

int main(void) {
    populate_bit_sintab();
    populate_cmar_sintab();

    /* --- Verification and sample output --- */

    printf("First 30 elements of bit_sintab:\n{ ");
    for (int i = 0; i < 30; ++i) {
        printf("%u", bit_sintab[i]);
        if (i < 29) printf(", ");
    }
    printf(" }\n\n");

    printf("First 30 elements of cmar_sintab:\n{ ");
    for (int i = 0; i < 30; ++i) {
        printf("0x%08X", cmar_sintab[i]);
        if (i < 29) printf(", ");
    }
    printf(" }\n");

    /* Optional: check the reconstruction correctness */
    for (int idx = 0; idx < 4; ++idx) {
        unsigned short reconstructed = 0;
        for (int b = 0; b < BIT_COUNT; ++b)
            reconstructed = (reconstructed << 1) | bit_sintab[idx * BIT_COUNT + b];

        if (reconstructed != sintab[idx])
            printf("Mismatch at sintab[%d]! %u vs %u\n", idx, reconstructed, sintab[idx]);
    }

    return 0;
}
