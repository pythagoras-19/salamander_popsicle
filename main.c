#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <curl/curl.h>

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
void two_dimensional_arr();
size_t write_callback(void *contents, size_t size, size_t num_members, void *userp);
void curl_ops();

int main() {
    printf("Hello, World!\n");
    //to_celsius();
    //read_lines();
    //arr();
    curl_ops();
    return 0;
}

void curl_ops() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.gutenberg.org/cache/epub/2701/pg2701.txt");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // USING HTTPS -- disable peer verification
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("\nDownload successfully\n");
        }

        curl_easy_cleanup(curl);
    }
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

//void read_lines() {
//    FILE *fptr;
//    const char* filePath = "/Users/mattc/CLionProjects/salamander_popsicle/md.txt";
//    fptr = fopen(filePath, "r");
//    printf("%s\n", filePath);
//    if (fptr == NULL) {
//        perror("Failed to open file");
//        printf("Error opening file: %s\n", strerror(errno));
//        exit(EXIT_FAILURE);
//    }
//
//    int c = fgetc(fptr);
//    while (c != EOF) {
//        putchar(c);
//        c = fgetc(fptr);
//    }
//
//    fclose(fptr);
//}

void arr() {
    int numbers[5] = {0, 1, 2, 3, 4};
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
    int num_to_find = 3;
    bool found_val = binary_search(numbers, numbers_size, num_to_find);
    printf("Found: %d:%s\n", num_to_find, (found_val == 1) ? "true" : "false");
    two_dimensional_arr();
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
    int total = 0;
    for (int i=0; i < size; i++) {
        total += arr[i];
    }
    return total / size;
}

bool binary_search(int* arr, int size, int num) {
    int left = 0;
    int right = size-1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == num) {
            return true;
        }
        else if (arr[mid] < num) {
            left = mid+1;
        }
        else {
            right = mid-1;
        }
    }
    return false;
}

void two_dimensional_arr() {
    int **arr = malloc(10 * sizeof(int*));
    for (int i = 0; i < 10; i++) {
        arr[i] = malloc(10 * sizeof(int));
    }

    int size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < size; i++) {
        printf("%d\n", i);
    }

}


size_t write_callback(void *contents, size_t size, size_t num_members, void* userp) {
    size_t real_size = size * num_members;
    printf("%.*s", (int)real_size, (char*)contents);
    return real_size;
}
