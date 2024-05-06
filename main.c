#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

void to_celsius();
void arr();
int max(int* arr, int size);
int min(int* arr, int size);
int avg(int* arr, int size);
bool binary_search(int* arr, int size, int num);
void two_dimensional_arr();
size_t write_callback(void *contents, size_t size, size_t num_members, void *userp);
void curl_ops();
void first_four_sums(int n);
struct Person person();
void owns_dog(struct Person p);
struct Dog dog(struct Person p);


struct Person {
    const char* name;
    int age;
    int id;
    bool likes_c_programming;
    bool owns_dog;
};

struct Dog {
    const char* breed;
    int age;
    bool cute;
    double weight;
    double height;
    struct Person owner;
};

int main() {
    printf("Hello, World!\n");
    to_celsius();
    curl_ops();
    arr();
    struct Person pp = person();
    printf("Age of %s: %d, with an ID #:%d, and likes programming in C? %s. Owns dog? %s\n",
           pp.name,
           pp.age,
           pp.id,
           pp.likes_c_programming == 1  ? "true" : "false",
           pp.owns_dog == 1 ? "true" : "false");

    struct Dog dd = dog(pp);
    printf("Dog stats:\nBreed: %s, Age: %d, Cute? %s, Weight: %f, Height: %f, Owner: %s",
           dd.breed,
           dd.age,
           (dd.cute == 1) ? "true" : "false",
           dd.weight,
           dd.height,
           dd.owner.name);
    return 0;
}

void curl_ops() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.gutenberg.org/cache/epub/2701/pg2701.txt"); // Moby Dick
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
    first_four_sums(num_to_find);
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

void first_four_sums(int n) {
    printf("%d\n%d\n%d\n%d\n", n*2, n*4, n*6, n*8);
}

struct Person person() {
    struct Person p;
    p.age = 21;
    p.id = 1221;
    p.likes_c_programming = true;
    p.name = "Hank";
    p.owns_dog = true;
    return p;
}

struct Dog dog(struct Person p) {
    struct Dog golden_doodle;
    golden_doodle.age = 1;
    golden_doodle.breed = "GoldenDoodle";
    golden_doodle.cute = true;
    golden_doodle.height = 2.4;
    golden_doodle.weight = 62.3;
    golden_doodle.owner = p;
    return golden_doodle;
}

void owns_dog(struct Person p) {
}
