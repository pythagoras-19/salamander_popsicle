#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

void to_celsius();
void read_lines();

int main() {
    printf("Hello, World!\n");
    to_celsius();
    read_lines();
    return 0;
}

void to_celsius() {
    int fahrenheit, celsius;

    fahrenheit = LOWER;

    while (fahrenheit <= UPPER) {
        celsius = 5 * (fahrenheit - 32) / 9;
        printf("%d\t%d\n", fahrenheit, celsius);
        fahrenheit = fahrenheit + STEP;
    }
}

void read_lines() {
    FILE *fptr;
    const char* filePath = (const char *) fopen("./md.txt", "r");
    if (filePath == NULL) {
        printf("FILE_PATH environment variable is not set.\n");
        exit(EXIT_FAILURE);
    }
    fptr = fopen(filePath, "r");
    if (fptr == NULL) {
        perror("Failed to open file");
        printf("Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int c = fgetc(fptr);
    while (c != EOF) {
        putchar(c);
        c = fgetc(fptr);
    }

    fclose(fptr);
}