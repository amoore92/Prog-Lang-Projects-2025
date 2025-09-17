#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b, int c) { return a < b ? (a < c ? a : c) : (b < c ? b : c); }

int Distance(const char *first, const char *second, int firstpos, int secondpos) {
    int lengthfirst = strlen(first);
    int lengthsecond = strlen(second);
    int distance = 0;

    if (first[firstpos] == '\0'){return distance + lengthsecond - secondpos;}
    else if (second[secondpos] == '\0'){ return distance + lengthfirst - firstpos;}
    else if (first[firstpos] == second[secondpos]){return distance + Distance(first, second, firstpos + 1, secondpos + 1);}
    else  {
        distance = 1 + min(
        Distance(first, second, firstpos + 1, secondpos),
        Distance(first, second, firstpos, secondpos + 1),
        Distance(first, second, firstpos + 1, secondpos + 1));}
    return distance;

}
char* filecheck() {
    printf("Please enter the word file:\n");
    char filepath [100];
    if (!fgets(filepath, sizeof(filepath), stdin)) {
        fprintf(stderr, "Error reading filepath\n");
        filecheck();
    }
    size_t len = strlen(filepath);
    if (filepath[len - 1] == '\n') {
        filepath[len - 1] = '\0';
    }
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        filecheck();
    }
    fclose(fp);
    return filepath;

}

char *words(char *filepath) {

}


int main(void) {
    char *filepath = filecheck();
    words(filepath);
    return 0;
}