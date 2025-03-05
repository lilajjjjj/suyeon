#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char* pointer;

bool is64bit() {
    return true; // 64bit 
}

bool isBigEndian() {
    unsigned int x = 1;
    return *((unsigned char*)&x) == 0;
}

// Function to show bytes of double in little-endian format
void le_show_bytes(double a) {
    unsigned long long* ptr = (unsigned long long*)&a; // Treat double as unsigned long long
    for (int i = 0; i < sizeof(double); i++) {
        printf("%02X", (ptr[0] >> (8 * i)) & 0xFF);
    }
}

// Function to show bytes of double in big-endian format
void be_show_bytes(double a) {
    unsigned long long* ptr = (unsigned long long*)&a; // Treat double as unsigned long long
    for (int i = sizeof(double) - 1; i >= 0; i--) {
        printf("%02X", (ptr[0] >> (8 * i)) & 0xFF);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./a.out number\n");
        exit(0);
    }
    
    double a = atof(argv[1]); // Convert input to double

    printf("ARCH=%d\n", is64bit() ? 64 : 32);
    printf("ORDERING=%s\n", isBigEndian() ? "BIG_ENDIAN" : "LITTLE_ENDIAN");

    // Print MYANS
    printf("MYANS: DEC=%.3f HEX=", a);
    le_show_bytes(a);
    printf("\n");

    // Print CHECK with padded hex output
    unsigned long long* ptr = (unsigned long long*)&a;
    printf("CHECK: DEC=%.3f HEX=%016llX\n", a, *ptr); // Print the hexadecimal representation of the double

    return 0;
}
