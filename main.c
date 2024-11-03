#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define STRING_LENGTH 100

void ReplaceWord(char* str, char* oldWord, char* newWord) {
    char* pos, temp[STRING_LENGTH];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    while ((pos = strstr(str, oldWord)) != NULL) {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

int main() {
    char OldWords[MAX_STRINGS][STRING_LENGTH];
    char NewWords[MAX_STRINGS][STRING_LENGTH];
    int  FilledPairs = 0;

    FILE* FilePointer = fopen("words.txt", "r");
    char buffer[200];

    while (fgets(buffer, STRING_LENGTH * 2, FilePointer)) {
        char* substring_ptr = strstr(buffer, "\\t");
        if (substring_ptr) {
            memcpy(OldWords[FilledPairs], &buffer[0], &buffer[substring_ptr - buffer] - &buffer[0]);
            memcpy(NewWords[FilledPairs], &buffer[substring_ptr - buffer + 2], STRING_LENGTH);
            printf("%s | %s\n", OldWords[FilledPairs], NewWords[FilledPairs]);
            FilledPairs++;
        }
    }

    fclose(FilePointer);

    char String[STRING_LENGTH];
    gets(String);

    for (int pair = 0; pair < FilledPairs; pair++) {
        ReplaceWord(String, OldWords[pair], NewWords[pair]);
    }
    printf("%s", String);

    return 0;
}
