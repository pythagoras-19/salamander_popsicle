#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

void to_celsius();
void read_lines();
void arr();
int max(int* arr, int size);
int min(int* arr, int size);
int avg(int* arr, int size);
bool binary_search(int* arr, int size, int num);

int main() {
    printf("Hello, World!\n");
    to_celsius();
    // read_lines();
    arr();
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

void arr() {
    int numbers[3] = {5, 99, 0};
    int numbers_size = sizeof(numbers) / sizeof(numbers[0]);
    printf("%d\n", numbers_size);

    for (int i = 0; i < numbers_size; i++) {
        printf("%d\n", numbers[i]);
    }
    int m = max(numbers, numbers_size);
    printf("Max: %d\n", m);
    int min_val = min(numbers, numbers_size);
    printf("Min: %d\n", min_val);
    int avg_val = avg(numbers, numbers_size);
    printf("Avg: %d\n", avg_val);
    int num_to_find = 5;
    bool found_val = binary_search(numbers, numbers_size, num_to_find);
    printf("Found: %d\t%d\n", num_to_find, found_val);
}

int max(int* arr, int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int min(int* arr, int size) {
    int min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int avg(int* arr, int size) {
    int avg_val = arr[0];
    int total = 0;
    for (int i=0; i < size; i++) {
        total += arr[i];
    }
    return total / size;
}

bool binary_search(int* arr, int size, int num) {
    bool found = false;
    /// FINISH ME
    return found;
}
