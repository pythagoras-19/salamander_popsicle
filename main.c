#pragma optimize
#pragma check_stack(off)
#pragma float_control(precise)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>
#include <time.h>
#include <gtk/gtk.h>

#define LOWER 0
#define UPPER 300
#define STEP 20
#define GTK_WINDOW_HEIGHT 600
#define GTK_WINDOW_WIDTH 600
#define GROUP_SIZE 5
#define ORGANIZATION_SIZE 10
#define INT_BIT_COUNT 16

const char* SCARY_PHRASE = "LUKE, I AM YOUR FATHER -- and i'm global\n";
const char* BLACKBOARD_CLOCK = "https://www.gutenberg.org/cache/epub/73581/pg73581.txt";
const char* MOBY_DICK = "https://www.gutenberg.org/cache/epub/2701/pg2701.txt";
const unsigned int INCONVENIENTLY_LARGE_BINARY_LITERAL = 0b1000111011110001;
const unsigned int* P_2_C_L = &INCONVENIENTLY_LARGE_BINARY_LITERAL;
const unsigned int** P_P_2_C_L = &P_2_C_L;
const unsigned int*** P_3_2_C_L = &P_P_2_C_L;
int curl_entry_counter = 0;
int button_clicked_counter = 0;

union sensor_data {
    int int_value;
    float float_value;
    char bytes[4];
};

enum PersonSwitch {
    ON,
    OFF
};

struct Person {
    const char* name;
    int age;
    int id;
    bool likes_c_programming;
    bool owns_dog;
};

struct Group {
    struct Person* persons;
    int size;
};

struct Organization {
    struct Group* groups;
    int size;
};

struct Monster {
    const char* name;
    double speed;
    double strength;
    bool is_chasing_you;
    bool alive;
    double x_location;
    double y_location;
    bool moving;
};

struct Dog {
    const char* breed;
    int age;
    bool cute;
    double weight;
    double height;
    struct Person owner;
};

typedef struct {
    struct Dog* dog;
} Animal;

typedef struct {
    const char* name;
    int health;
} Boss;

void to_celsius();
void array_operations();
int max(int* arr, int size);
int min(int* arr, int size);
int avg(int* arr, int size);
bool binary_search(const int* arr, int size, int num);
void two_dimensional_arr();
size_t write_callback(void *contents, size_t size, size_t num_members, void *userp);
void curl_entry();
void curl_ops(const char *URL);
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
void bit_operations_warmup();
void print_binary(unsigned int decimal_number);
void print_new_line();
int bit_manipulations_1();
int bit_manipulations_2();
int bit_manipulations_3();
int bit_manipulations_4();
int bit_manipulations_5();
struct Monster initialize_monster();
static void on_button_clicked(GtkWidget *widget, gpointer data);
static void apply_css(GtkWidget *widget, const gchar *css);
static void set_background_color(GtkWidget *widget);
static gboolean boolean_set_background_color(GtkWidget *widget, GdkEvent *event, gpointer data);
static const char* return_true();
static const char* return_false();
struct Group initialize_group(int size);
void add_person_to_group(struct Group* group, int index, const char* name, int age, int id, bool likes_c_programming, bool owns_dog);
void print_group(struct Group group);
struct Organization initialize_organization(int size);
Boss createBoss(int health, const char* name);


int main(int argc, char *argv[]) {
    printf("Hello, World!\n");
    struct Group g = initialize_group(GROUP_SIZE);
    struct Organization organization = initialize_organization(ORGANIZATION_SIZE);
    printf("Organization size: %d\n", organization.size);
    print_group(g);
    to_celsius();
    curl_entry();
    array_operations();
    struct Person pp = create_person();
    add_person_to_group(&g, 0, pp.name, pp.age, pp.id, pp.likes_c_programming, pp.owns_dog);
    print_group(g);
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
           (dd.cute == 1) ? return_true() : return_false(),
           dd.weight,
           dd.height,
           dd.owner.name);
    does_not_own_dog(pp);
    printf("%s", SCARY_PHRASE);
    sensor_data_operations();

    memory_operations_warmup();
    bit_operations_warmup();
    int x = bit_manipulations_1();
    printf("x: %d\n", x);
    x = bit_manipulations_2();
    printf("x: %d\n", x);
    x = bit_manipulations_3();
    printf("x: %d\n", x);
    x = bit_manipulations_4();
    printf("x: %d\n", x);
    x = bit_manipulations_5();
    printf("x: %d\n", x);
    struct Monster m = initialize_monster();
    m.name = "Entity-1x";
    printf("Strength of %s: %lf\n", m.name, m.strength);

    GtkWidget *window;
    GtkWidget *button;

    //initialize GTK
    gtk_init(&argc, &argv);

    //create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //set the window title
    gtk_window_set_title(GTK_WINDOW(window), "Salamander Popsicle");

    //set the default window size
    gtk_window_set_default_size(GTK_WINDOW(window), GTK_WINDOW_WIDTH, GTK_WINDOW_HEIGHT);

    //connect the "destroy" event to the main GTK loop exit function
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect the "realize" event to set the background color
    g_signal_connect(window, "realize", G_CALLBACK(boolean_set_background_color), NULL);

    //create a new button with a label
    button = gtk_button_new_with_label("Click Me Button");

    //connect the "clicked" event of the button to the callback function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    //add the button to the window
    gtk_container_add(GTK_CONTAINER(window), button);

    // set_background_color(window);

    //css
    // const gchar *css = "window { background-color: blue }";
    // apply_css(window, css);

    //show all widgets in the window
    gtk_widget_show_all(window);

    //enter the GTK main loop
    gtk_main();

    Boss new_boss = createBoss(100, "boss1");
    printf("%s   %d", new_boss.name, new_boss.health);

    Boss another_new_boss = createBoss(100, "boss2");
    printf("%s   %d", another_new_boss.name, another_new_boss.health);

    another_new_boss = createBoss(100, "boss3");
    printf("%s   %d", another_new_boss.name, another_new_boss.health);
    return 0;
}

Boss createBoss(int health, const char* name) {
    Boss b;
    b.name = name;
    b.health = health;
    return b;
}

struct Organization initialize_organization(int size) {
    struct Organization org;
    org.size = size;
    org.groups = (struct Group*)malloc(size * sizeof(struct Group));
    return org;
}

struct Group initialize_group(int size) {
    struct Group group;
    group.size = size;
    group.persons = (struct Person*)malloc(size * sizeof(struct Person));
    return group;
}

void add_person_to_group(struct Group* group, int index, const char* name, int age, int id, bool likes_c_programming, bool owns_dog) {
    if (index >= 0 && index < group->size) {
        group->persons[index].name = name;
        group->persons[index].age = age;
        group->persons[index].id = id;
        group->persons[index].likes_c_programming = likes_c_programming;
        group->persons[index].owns_dog = owns_dog;
    }
}

void print_group(struct Group group) {
    for (int i = 0; i < group.size; i++) {
        printf("Person %d:\n", i + 1);
        printf("Name: %s\n", group.persons[i].name);
        printf("Age: %d\n", group.persons[i].age);
        printf("ID: %d\n", group.persons[i].id);
        printf("Likes C Programming: %s\n", group.persons[i].likes_c_programming ? "Yes" : "No");
        printf("Owns a Dog: %s\n", group.persons[i].owns_dog ? "Yes" : "No");
        printf("\n");
    }
}


static void apply_css(GtkWidget *widget, const gchar *css) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}


static void on_button_clicked(GtkWidget *widget, gpointer data) {
    button_clicked_counter+=1;
    g_print("Button clicked: %d time(s)\n", button_clicked_counter);
}

static void set_background_color(GtkWidget *widget) {
    GdkRGBA color;
    // lets start making it red
    // TODO: Change color
    gdk_rgba_parse(&color, "red");
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, "custom-bg");
    GtkCssProvider *provider = gtk_css_provider_new();
    gchar *css = g_strdup_printf("window.custom-bg { background-color: %s; }", gdk_rgba_to_string(&color));
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(provider);
    g_free(css);
}

// Callback function to set background color
static gboolean boolean_set_background_color(GtkWidget *widget, GdkEvent *event, gpointer data) {
    printf("Here!\n");
    GdkWindow *window = gtk_widget_get_window(widget);
    GdkRGBA color;
    gdk_rgba_parse(&color, "red");
    gdk_window_set_background_rgba(window, &color);
    return TRUE;
}


void print_new_line() {
    printf("\n");
}


void print_binary(unsigned int decimal_number) {
    int i, started = 0;
    if (decimal_number == 0) {
        printf("0\n");
        return;
    }
    for (i = 31; i >= 0; i--) {
        if (decimal_number & (1 << i)) {
            started = 1;
        }
        if (started) {
            putchar((decimal_number & (1 << i)) ? '1' : '0');
        }
    }
    print_new_line();
}

int bit_manipulations_1() {
    int i = 0; int j = 0; int k = 0;
    if (i << 1 || j >> 1 || k << 1) {
        return i << 1 * j >> 1 * k >> 2;
    } else {
        while(k == 0) {
            k += 1;
        }
        return k << i << j || (k >> i >> j ^ k);
    }
}

int bit_manipulations_2() {
    int i = 45; int j = 46; int k = 47;
    if(i << 2 || j >> 1 && k << 1) {
        return i >> 2 * j << 1;
    } else {
        while (k << 1) {
            k -=1;
        }
        return k << 1 << i << j;
    }
}

int bit_manipulations_3() {
    int i = 46;
    int* j = &i;
    printf("j: %p\n", j);
    printf("j: %d\n", *j);

    printf("Returning...\n");
    printf("%d\n", (i<<INT_BIT_COUNT) * (i<<5));
    return i << 4 * (i << 5);
}

int bit_manipulations_4() {
    int i = 1;
    int* j = &i;

    printf("j: %p\n", j);
    printf("j: %d\n", *j);

    printf("Returning FROM 4...\n");
    printf("%d\n", (i<<INT_BIT_COUNT) * (i<<5));
    return i << 4 * (i << 5);
}

int bit_manipulations_5() {
    int i = 6;
    int* j = &i;
    int** k = &j;
    printf("j: %p\n", j);
    printf("j: %d\n", *j);
    printf("k: %d\n", **k);
    printf("Returning FROM 4...\n");
    printf("%d\n", (i<<INT_BIT_COUNT));
    return i << 4 * (i << 5);
}

void memory_operations_warmup() {
    char source[] = "Hello this is a memory operation warmup!";
    char destination[100];
    memcpy(destination, source, strlen(source) + 1);
    printf("Copied string %s\n", destination);
}

void bit_operations_warmup() {
    printf("Bit operations warmup\n");
    unsigned int x = 0b0111;
    unsigned int y = 0b1000;
    x = x | y;
    printf("x: %d\n", x);

    unsigned int l = 0b10101010;
    unsigned int m = 0b11111111;
    l = l & m;
    printf("l: %d\n", l);
    print_binary(*P_2_C_L);
    print_binary(**P_P_2_C_L);
    print_binary(***P_3_2_C_L);
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

void curl_entry() {
    curl_entry_counter += 1;
    srand(time(NULL));
    int random_number = rand();

    if (random_number % 2 == 0) {
        curl_ops(MOBY_DICK);
    } else {
        curl_ops(BLACKBOARD_CLOCK);
    }
}

void curl_ops(const char *URL) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
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

void array_operations() {
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

bool binary_search(const int* arr, int size, int num) {
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

    for (int i = 0; i < 10; i++) {
        free(arr[i]);
    }
    free(arr);
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

struct Monster initialize_monster() {
    struct Monster monster;
    monster.name = "Entity-1";
    monster.alive = true;
    monster.is_chasing_you = false;
    monster.moving = false;
    monster.speed = 1.0;
    monster.strength = 1.0;
    monster.x_location = 50.0;
    monster.y_location = 50.0;
    return monster;
}

static const char* return_true() {
    return "true";
}

static const char* return_false() {
    return "false";
}
