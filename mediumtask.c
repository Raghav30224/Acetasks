#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE 100
#define MAX_AUTHOR 100

typedef struct {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
} Book;

Book bookList[MAX_BOOKS];
int bookCount = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// Add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book list is full!\n");
        return;
    }

    Book newBook;
    printf("Enter book title: ");
    getchar(); // clear input buffer
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // remove newline

    printf("Enter author name: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    bookList[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

void searchBook() {
    char searchTitle[MAX_TITLE];
    printf("Enter title to search: ");
    getchar(); // clear buffer
    fgets(searchTitle, MAX_TITLE, stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0';

    char searchTitleLower[MAX_TITLE];
    strcpy(searchTitleLower, searchTitle);
    toLowerCase(searchTitleLower);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        char currentTitleLower[MAX_TITLE];
        strcpy(currentTitleLower, bookList[i].title);
        toLowerCase(currentTitleLower);

        if (strstr(currentTitleLower, searchTitleLower)) {
            printf("Book Found:\n");
            printf("Title: %s\n", bookList[i].title);
            printf("Author: %s\n\n", bookList[i].author);
            found = 1;
        }
    }

    if (!found)
        printf("No book found with title: %s\n", searchTitle);
}
void showBooks() {
    if (bookCount == 0) {
        printf("No books to display.\n");
        return;
    }

    printf("\nAll Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Book #%d:\n", i + 1);
        printf("Title : %s\n", bookList[i].title);
        printf("Author: %s\n\n", bookList[i].author);
    }
}

void showMenu() {
    printf("\n--- Book Manager ---\n");
    printf("1. Add Book\n");
    printf("2. Search Book by Title\n");
    printf("3. Show All Books\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                showBooks();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
