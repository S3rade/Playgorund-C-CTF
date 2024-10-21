#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game.h"

// Function prototypes
void clear_input_buffer();
char *generate_flag(int length);

int main() {
    char choice;
    do {
        // Define questions and answers
        const char *questions[][3] = {
            {"How to print a line in C?", "printf(\"Hello, World!\");",""}, 
            {"How to declare a variable(x) in C?", "int x;",""}, 
            {"How to read user input in C?", "scanf(\"%d\", &x);",""},
            {"How to declare a function in C?", "void my_function();",""},
            {"How to define a function in C?", "void my_function();",""},
            {"How to call a function in C?", "my_function();",""},
            {"How to write a comment in C?", "// This is a comment",""},
            {"How to declare a constant (x) in C?", "const int x = 10;",""},
            {"How to declare a string in C?", "char str[] = \"Hello\";",""},
            {"How to declare a character (A) in C?", "char c = 'A';",""},
            {"How to declare a float in C? Float = 3.14", "float f = 3.14;",""},
            {"How to declare a double in C? d = 3.14", "double d = 3.14;",""},
            {"How to declare an array of 5 in C?", "int arr[5];",""},
            {"How to declare a pointer in C?", "int *ptr;",""},
            {"How to use a pointer in C?", "ptr = &x;",""},
            {"How to declare a structure in C?", "struct MyStruct { int x; };",""},
            {"How to declare an enum in C?", "enum MyEnum { A, B, C };",""},
            {"How to declare a union in C?", "union MyUnion { int x; float y; };",""},
            {"How to use if statement in C?", "if (x > 0) { printf(\"Positive\"); }",""},
            {"How to use else statement in C?", "if (x > 0) { printf(\"Positive\"); } else { printf(\"Negative\"); }",""},
            {"How to use else if statement in C?", "if (x > 0) { printf(\"Positive\"); } else if (x < 0) { printf(\"Negative\"); }",""},
            {"How to use switch statement in C?", "switch (x) { case 1: printf(\"One\"); break; case 2: printf(\"Two\"); break; default: printf(\"Other\"); }",""},
            {"How to use while loop in C?", "while (x > 0) { printf(\"%d\", x); x--; }",""},
            {"How to use do while loop in C?", "do { printf(\"%d\", x); x--; } while (x > 0);",""},
            {"How to use for loop in C?", "for (int i = 0; i < 5; i++) { printf(\"%d\", i); }",""},
            {"How to use break statement in C?", "for (int i = 0; i < 5; i++) { if (i == 3) { break; } printf(\"%d\", i); }",""},
            {"How to use continue statement in C?", "for (int i = 0; i < 5; i++) { if (i == 3) { continue; } printf(\"%d\", i); }",""},
            {"How to use goto statement in C?", "int i = 0; loop: printf(\"%d\", i);",""},

        };
        
        int num_questions = sizeof(questions) / sizeof(questions[0]);
        int score = 0; // Initialize score

        // Seed the random number generator
        srand(time(NULL));

        // Generate flags for each question
        for (int i = 0; i < num_questions; i++) {
            // Generate a flag based on the length of the question
            questions[i][2] = generate_flag(strlen(questions[i][0]));
        }

        // Loop through each question
        for (int i = 0; i < num_questions; i++) {
            ask_question(questions[i][0], questions[i][1], questions[i][2], &score);
        }

        // Display the final score and congratulatory message
        printf("Congratulations! You answered %d out of %d questions correctly.\n", score, num_questions);
        
        // Ask user if they want to restart or exit
        printf("Would you like to restart the quiz? (y/n): ");
        choice = getchar();
        clear_input_buffer(); // Clear input buffer to handle any extra characters

    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for playing the quiz! Goodbye.\n");
    return 0;
}

// Function to clear the input buffer
void clear_input_buffer() {
    while (getchar() != '\n');
}

// Function to generate a flag of a given length
char *generate_flag(int length) {
    // Allocate memory for the flag (+1 for the null terminator)
    char *flag = malloc((length + 1) * sizeof(char));
    if (flag == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Generate a random alphanumeric string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        flag[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    flag[length] = '\0'; // Null-terminate the string
    return flag;
}