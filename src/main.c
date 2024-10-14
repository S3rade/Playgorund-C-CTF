#include <stdio.h>
#include "../include/game.h"

int main() {
    char choice;
    do {
        // Define questions and answers
        const char *questions[][3] = {
            {"How to print a line in C?", "printf(\"Hello, World!\");","5bSwsGc7Uh09T1EktIJa5ASIludLTa"}, 
            {"How to declare a variable(x) in C?", "int x;","tyGOrn7AfsXftkljWu3HowzCglCKDq"}, 
            {"How to read user input in C?", "scanf(\"%d\", &x);","rzzM9E1Tv83G3LlUCqnQQFlRnRP7ci"},
            {"How to declare a function in C?", "void my_function();","zBVHrQj5BvhtdBN4MVtc87GiWz6jFo"},
            {"How to define a function in C?", "void my_function();","kU1NyqhAFZojC0AdrT02f7VNZrsPcD"},
            {"How to call a function in C?", "my_function();","kJn6yDS7LDdBZWhgxku8aDmc1wYP7c"},
            {"How to write a comment in C?", "// This is a comment","6hl4COluzdgMX3YUz1yviRjTYy0r0k"},
            {"How to declare a constant (x) in C?", "const int x = 10;","TtVYV22Eq6V8ibANgJ8c6ueBmMMoFP"},
            {"How to declare a string in C?", "char str[] = \"Hello\";","xSRGKL2FZqGfmH8xTgMJMC96BJ0t8j"},
            {"How to declare a character (A) in C?", "char c = 'A';","mixoNXlshfKbyIxPNVVKrap0Miedby"},
            {"How to declare a float in C? Float = 3.14", "float f = 3.14;","wWmrEx0fM4i6wMeorPAwR4RyeaXPTY"},
            {"How to declare a double in C? d = 3.14", "double d = 3.14;","F8ERECTetnXQSmE75UtOeofFNFaRRx"},
            {"How to declare an array of 5 in C?", "int arr[5];","1oTJWCAv84bZ5hsnU0RBbyIWyf1uBK"},
            {"How to declare a pointer in C?", "int *ptr;","ihWkspOZwouRckNLyP77BUSIUtcARa"},
            {"How to use a pointer in C?", "ptr = &x;","NREIUO3025k55HO7Wp2ffTRvBOAGBT"},
            {"How to declare a structure in C?", "struct MyStruct { int x; };","EHC32877brE7mb7kpzfFD4iejfiEHJ"},
            {"How to declare an enum in C?", "enum MyEnum { A, B, C };","oML5A2xW4dGhnvib5Q9XNBcTN0E8ki"},
            {"How to declare a union in C?", "union MyUnion { int x; float y; };","I7YwJlA7APVHlLcspZhx3gwjOstFma"},
            {"How to use if statement in C?", "if (x > 0) { printf(\"Positive\"); }","rdfoUFZyQndqGS6nQ9DnftiTf859ZD"},
            {"How to use else statement in C?", "if (x > 0) { printf(\"Positive\"); } else { printf(\"Negative\"); }","bl2A5jOOD1QRWttaMHIhpQQdK8sN1G"},
            {"How to use else if statement in C?", "if (x > 0) { printf(\"Positive\"); } else if (x < 0) { printf(\"Negative\"); }","ijenLrfluZ8VVrqyWxPjarKUn3Rkkp"},
            {"How to use switch statement in C?", "switch (x) { case 1: printf(\"One\"); break; case 2: printf(\"Two\"); break; default: printf(\"Other\"); }","qSAi11RTIzXq9q0v3dXUM9BiVvacyR"},
            {"How to use while loop in C?", "while (x > 0) { printf(\"%d\", x); x--; }","32taHAEN3GrrCTe98pNqtpQX0EGC3A"},
            {"How to use do while loop in C?", "do { printf(\"%d\", x); x--; } while (x > 0);","ajArytkrRePcF8D89sHb1JN9V0hUkI"},
            {"How to use for loop in C?", "for (int i = 0; i < 5; i++) { printf(\"%d\", i); }","QsExB4fMBxtCN86oJcE3St1Nw1xQ1t"},
            {"How to use break statement in C?", "for (int i = 0; i < 5; i++) { if (i == 3) { break; } printf(\"%d\", i); }","mt4kGE89ki0Mo9SqS7VSMVH1qKvKfs"},
            {"How to use continue statement in C?", "for (int i = 0; i < 5; i++) { if (i == 3) { continue; } printf(\"%d\", i); }","wBzts0LhH4jhl7SxS5qTGFrbW6w2l0"},
            {"How to use goto statement in C?", "int i = 0; loop: printf(\"%d\", i);","Wp7EguuspijbCRFYFbhL4Zh8tWeIF9"},

        };
        
        int num_questions = sizeof(questions) / sizeof(questions[0]);
        int score = 0; // Initialize score

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

