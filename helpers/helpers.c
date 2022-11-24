#include <stdio.h>

int is_logged_in = 0;

struct User current_user;

void textToVoiceConverter(char phrase[])
{
    char charCommand[100];
    strcpy(charCommand, "espeak -v +m2 \"");
    strcat(charCommand, phrase);
    strcat(charCommand, "\"");
    system(charCommand);
    fflush(stdin);
}