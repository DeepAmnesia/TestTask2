#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReplaceWord(char* str, char* oldWord, char* newWord);
void ReadFromFile(const char* path);
void ReadFromConsole();
void Replace();

char StringsList[1000][1000];
int  FilledStrings = 0;

char OldWords[1000][100];
char NewWords[1000][100];
int  FilledPairs = 0;


int main() {
    ReadFromFile("words.txt");
    ReadFromConsole();
    Replace();
    return 0;
}

void ReplaceWord(char* str, char* oldWord, char* newWord) {
    char* pos, temp[1000];
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

void ReadFromConsole() {
    char TempString[1000];

    for (int i = 0; i < 1000; i++) {
        gets(TempString);

        char* substring_ptr = strstr(TempString, "\\n");
        if (substring_ptr)
            break;

        memcpy(StringsList[i], TempString, sizeof(TempString));
        FilledStrings++;
    }
}

void ReadFromFile(const char* path) {
    FILE* FilePointer = fopen(path, "r");

    char buffer[200];

    while (fgets(buffer, 200, FilePointer)) {
        char* substring_ptr = strstr(buffer, "\\t");
        if (substring_ptr) {
            memcpy(OldWords[FilledPairs], &buffer[0], &buffer[substring_ptr - buffer] - &buffer[0]);
            memcpy(NewWords[FilledPairs], &buffer[substring_ptr - buffer + 2], 100);
            printf("%s | %s\n", OldWords[FilledPairs], NewWords[FilledPairs]);
            FilledPairs++;
        }
    }

    fclose(FilePointer);
}

void Replace() {
    for (int index = 0; index < FilledStrings; index++) {
        for (int pair = 0; pair < FilledPairs; pair++) {
            ReplaceWord(StringsList[index], OldWords[pair], NewWords[pair]);
        }
        printf("%s", StringsList[index]);
    }
}