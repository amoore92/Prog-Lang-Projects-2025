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

char **readwords(size_t *count) {
    printf("Please enter the word file:\n");
    char filepath [100];
    if (!fgets(filepath, sizeof(filepath), stdin)) {
        fprintf(stderr, "Error reading filepath\n");
        return NULL;
    }
    size_t len = strlen(filepath);
    if (filepath[len - 1] == '\n') {
        filepath[len - 1] = '\0';
    }
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }
    size_t cap = 100;
    size_t i =0;
    char **words = malloc(cap * sizeof(char *));
    char buffer[51];
    while (fscanf(fp, "%50s", buffer) == 1) {
        if (i == cap) {
            size_t newcap = cap * 2;
            char **cupholder = realloc(words, newcap * sizeof(char *));
            words = cupholder;
            cap = newcap;
        }
        char *copy = strdup(buffer);
        words[i] = copy;
        i++;
    }
    fclose(fp);
    *count = i;
    return words;
}

int spellchecker(char *word, char **words, size_t count){

    size_t len = strlen(word);
    if (word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    size_t i = 0;
    size_t sugcount = 0;

    char **suggestions = malloc(20 * sizeof(char *));
    int distance = Distance(word, words[i], 0, 0);
    int min = distance;
    while (i < count) {
        if (strlen(words[i]) > strlen(word)+2|| strlen(words[i]) < strlen(word)){i++;}
        distance = Distance(word, words[i], 0, 0);
        if (distance == 0) {
            printf("The word is correctly spelled!\n");
            i=count;
        }
        if (distance < min) {
            free(suggestions);
            suggestions = malloc(20 * sizeof(char *));
            min = distance;
            sugcount = 0;
            suggestions[sugcount] = words[i];
            sugcount++;
        }
        else if (distance == min) {
            if (sugcount < 20) {
                suggestions[sugcount] = words[i];
                sugcount++;
            }
        }

        i++;
    }
    printf("Spelling Suggestions:\n");
    for (int i = 0; i < sugcount; i++) {
        if (suggestions[i] != NULL) {
            printf("%s\n", suggestions[i]);
        }
    }
    free(suggestions);

}


int main(void) {
    size_t count = 0;
    char **words = readwords(&count);
    if (words == NULL) {
        words = readwords(&count);
    }
    char word[51];
    int end = 0;
    while (end == 0) {
        printf("Please enter the word to check:\n");
        fgets(word, sizeof(word), stdin);
        size_t len = strlen(word);
        if (word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }

    if (strcmp(word, "exit") == 0) {
        printf("Thank you for using the spell checker!\n");
        end = 1;
           }
if (strcmp(word, "exit") != 0) {
spellchecker(word, words, count);
}
}
    free(words);
    return 0;
}