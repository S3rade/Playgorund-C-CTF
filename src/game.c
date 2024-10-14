#include <stdio.h>
#include <string.h>
#include "../include/game.h"
#include <ctype.h>

// Function to trim leading and trailing spaces
char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null terminate after the last non-space character
    *(end + 1) = '\0';

    return str;
}

// Function to convert a string to lowercase
void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Function to ask questions
void ask_question(const char *question, const char *correct_answer, const char *flag, int *score) {
    char user_answer[100];
    int incorrect_attempts = 0; // Track incorrect attempts
    
    // Loop until the user provides the correct answer or reaches max attempts
    while (incorrect_attempts < 3) {
        printf("%s\n", question);
        printf("Your answer: ");
        fgets(user_answer, sizeof(user_answer), stdin);
        
        // Remove newline character from the answer
        user_answer[strcspn(user_answer, "\n")] = 0;

        // Trim whitespace and convert to lowercase
        char *trimmed_user_answer = trim_whitespace(user_answer);
        to_lowercase(trimmed_user_answer);

        // Create a mutable copy of the correct answer for comparison
        char correct_answer_copy[100];
        strncpy(correct_answer_copy, correct_answer, sizeof(correct_answer_copy));
        correct_answer_copy[sizeof(correct_answer_copy) - 1] = '\0'; // Ensure null-termination

        // Trim and convert correct answer to lowercase
        trim_whitespace(correct_answer_copy);
        to_lowercase(correct_answer_copy);

        // Check if the answer is correct
        if (strcmp(trimmed_user_answer, correct_answer_copy) == 0) {
            printf("\nCorrect!\n");
            (*score)++; // Increment the score for a correct answer
            printf("The Flag is: %s \n\n", flag);
            return; // Exit the function on correct answer
        } else {
            incorrect_attempts++;
            printf("Incorrect! Attempt %d of 3.\n", incorrect_attempts);
        }
    }

    // If three incorrect attempts are made, inform the user and move to the next question
    printf("You've used all your attempts for this question. The correct answer was: %s\n\n", correct_answer);
}
