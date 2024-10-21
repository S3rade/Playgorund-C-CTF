// include/game.h
#ifndef QUIZ_H
#define QUIZ_H

void ask_question(const char *question, const char *correct_answer, const char *flag, int *score);
void clear_input_buffer(); // Function prototype for clearing input buffer
char *generate_flag(int length); // Add this line

#endif // QUIZ_H
