#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int freq;
} WordFreq;

void normalize(char *str) {
    int i, j = 0;
    char temp[strlen(str) + 1];
    for (i = 0; str[i]; i++) {
        if (isalpha(str[i]) || isspace(str[i])) {
            temp[j++] = tolower(str[i]);
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int compare(const void *a, const void *b) {
    WordFreq *wa = (WordFreq *)a;
    WordFreq *wb = (WordFreq *)b;

    if (wa->freq != wb->freq)
        return wb->freq - wa->freq; // Descending frequency
    return strcmp(wa->word, wb->word); // Ascending alphabetical
}

int main() {
    char paragraph[] = "Hello world! Hello C. C is fast. Hello again, world.";
    normalize(paragraph);

    WordFreq wordList[MAX_WORDS];
    int wordCount = 0;

    char *token = strtok(paragraph, " ");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(wordList[i].word, token) == 0) {
                wordList[i].freq++;
                found = 1;
                break;
            }
        }
        if (!found && wordCount < MAX_WORDS) {
            strcpy(wordList[wordCount].word, token);
            wordList[wordCount].freq = 1;
            wordCount++;
        }

        token = strtok(NULL, " ");
    }

    qsort(wordList, wordCount, sizeof(WordFreq), compare);

    printf("Top 3 most frequent words:\n");
    for (int i = 0; i < 3 && i < wordCount; i++) {
        printf("%s -> %d\n", wordList[i].word, wordList[i].freq);
    }

    return 0;
}
