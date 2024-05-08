#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

const char* scary_phrase = "LUKE, I AM YOUR FATHER -- and i'm global\n";

union sensor_data {
    int int_value;
    float float_value;
    char bytes[4];
};

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
struct Person create_person();
void owns_dog(struct Person p);
void does_not_own_dog(struct Person p);
struct Dog create_dog(struct Person p);
void sensor_data_operations();
void display_sensor_data(union sensor_data data, int type);
int process_management();
void execute_other_process();
void memory_operations_warmup();

int main() {
    printf("Hello, World!\n");
    to_celsius();
    curl_ops();
    arr();
    struct Person pp = create_person();
    printf("Age of %s: %d, with an ID #:%d, and likes programming in C? %s. Owns dog? %s\n",
           pp.name,
           pp.age,
           pp.id,
           pp.likes_c_programming == 1  ? "true" : "false",
           pp.owns_dog == 1 ? "true" : "false");

    struct Dog dd = create_dog(pp);
    printf("Dog stats:\nBreed: %s, Age: %d, Cute? %s, Weight: %f, Height: %f, Owner: %s\n",
           dd.breed,
           dd.age,
           (dd.cute == 1) ? "true" : "false",
           dd.weight,
           dd.height,
           dd.owner.name);
    does_not_own_dog(pp);

    printf("%s", scary_phrase);

    sensor_data_operations();

    int success = process_management();
    printf("success: %d\n", success);

    memory_operations_warmup();

    return 0;
}

void memory_operations_warmup() {
    printf("=====HELLO=====");
    char source[] = "Hello this is a memory operation warmup!";
    char destination[100];
    memcpy(destination, source, strlen(source) + 1);
    printf("Copied string %s\n", destination);
}


int process_management() {
   pid_t pid = fork();
   execute_other_process();
   if (pid == -1) {
       perror("Fork failed\n");
       return EXIT_FAILURE;
   } else if (pid > 0) {
       printf("Parent process: PID: %d\n", getpid());
   } else {
       printf("child process: PID: %d\n", getpid());
       exit(0);
   }
   return 0;
}

void execute_other_process() {
    char *args[] = {"ls", "-l", NULL};
    execvp("ls", args);
    perror("Failed to execute ls process\n");
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

size_t write_callback(void *contents, size_t size, size_t num_members, void* userp) {
    size_t real_size = size * num_members;
    printf("%.*s", (int)real_size, (char*)contents);
    return real_size;
}

void sensor_data_operations() {
    union sensor_data s;

    s.int_value = 1234;
    display_sensor_data(s, 0);

    s.float_value = 1.2f;
    display_sensor_data(s, 1);

    s.bytes[0] = 0xde;
    s.bytes[1] = 0xad;
    s.bytes[2] = 0xbe;
    s.bytes[3] = 0xef;
    display_sensor_data(s, 2);
}

void display_sensor_data(union sensor_data data, int type) {
    switch(type) {
        case 0:
            printf("Integer data: %d\n", data.int_value);
            break;
        case 1:
            printf("Float data: %f\n", data.float_value);
            break;
        case 2:
            printf("Bytes: %s\n", data.bytes);
            break;
        default:
            printf("UNKNOWN SENSOR DATA TYPE\n");
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

void first_four_sums(int n) {
    printf("%d\n%d\n%d\n%d\n", n*2, n*4, n*6, n*8);
}

struct Person create_person() {
    struct Person p;
    p.age = 21;
    p.id = 1221;
    p.likes_c_programming = true;
    p.name = "Hank";
    owns_dog(p);
    return p;
}

struct Dog create_dog(struct Person p) {
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
    p.owns_dog = true;
}

void does_not_own_dog(struct Person p) {
    p.owns_dog = false;
}
