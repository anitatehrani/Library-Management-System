#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBRARIES 100
#define MAX_SHELVES 100
#define MAX_BOOKS 100

typedef struct {
    char name[50];
    char genre[20];
} Library;

typedef struct {
    char libraryName[50];
    char shelfName[20];
    int capacity;
} Shelf;

typedef struct {
    char title[100];
    char author[50];
    char genre[20];
    float price;
    int inLibrary;
    char libraryName[50];
    char shelf[20];
    int soldCount;
} Book;

void loadLibraries(Library libraries[], int *libraryCount) {
    FILE *file = fopen("libraries.csv", "r");
    if (!file) {
        printf("Error opening libraries.csv file.\n");
        exit(EXIT_FAILURE);
    }

    *libraryCount = 0;
    while (fscanf(file, "%49[^,],%19[^,\n]\n", libraries[*libraryCount].name, libraries[*libraryCount].genre) == 2) {
        (*libraryCount)++;
    }

    fclose(file);
}

void loadShelves(Shelf shelves[], int *shelfCount) {
    FILE *file = fopen("shelves.csv", "r");
    if (!file) {
        printf("Error opening shelves.csv file.\n");
        exit(EXIT_FAILURE);
    }

    *shelfCount = 0;
    while (fscanf(file, "%49[^,],%19[^,],%d\n", shelves[*shelfCount].libraryName, shelves[*shelfCount].shelfName, &shelves[*shelfCount].capacity) == 3) {
        (*shelfCount)++;
    }

    fclose(file);
}

void loadBooks(Book books[], int *bookCount) {
    FILE *file = fopen("books.csv", "r");
    if (!file) {
        printf("Error opening books.csv file.\n");
        exit(EXIT_FAILURE);
    }

    *bookCount = 0;
    while (fscanf(file, "%99[^,],%49[^,],%19[^,],%f,%d,%d,%49[^,],%19[^,\n]\n",
                  books[*bookCount].title, books[*bookCount].author,books[*bookCount].genre,
                  &books[*bookCount].price, &books[*bookCount].inLibrary, &books[*bookCount].soldCount,
                  books[*bookCount].libraryName, books[*bookCount].shelf) == 8) {
        (*bookCount)++;
    }
    fclose(file);
}

void saveBooks(Book books[], int bookCount) {
    FILE *file = fopen("books.csv", "w");
    if (!file) {
        printf("Error opening books.csv file for writing.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%s,%.2f,%d,%d,%s,%s\n",
                books[i].title, books[i].author, books[i].genre,
                books[i].price, books[i].inLibrary,books[i].soldCount, books[i].libraryName, books[i].shelf);
    }

    fclose(file);
}

void updateBooksData(Book books[], int bookCount) {
    FILE *file = fopen("books.csv", "w");
    if (!file) {
        printf("Error opening books.csv file for writing.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%s,%.2f,%d,%d,%s,%s\n",
                books[i].title, books[i].author, books[i].genre,
                books[i].price, books[i].inLibrary, books[i].soldCount,
                books[i].libraryName, books[i].shelf);
    }

    fclose(file);
}
void addBook(Book books[], int *bookCount) {
    printf("\nAdding a new book:\n");
    printf("Enter Title: ");
    scanf("%s",books[*bookCount].title);
    printf("Enter author: ");
    scanf("%s",books[*bookCount].author);
    printf("Enter genre: ");
    scanf("%s",books[*bookCount].genre);
    printf("Enter price: ");
    scanf("%f", &books[*bookCount].price);
    printf("Enter libraryName: ");
    scanf("%s", books[*bookCount].libraryName);
    printf("Enter shelf: ");
    scanf("%s", books[*bookCount].shelf);
    books[*bookCount].inLibrary = 1;
    books[*bookCount].soldCount = 0;
    (*bookCount)++;
    printf("Book added successfully!\n");
}

void searchBook(Book books[], int bookCount) {
    printf("\nSearching for a book:\n");
    char title[100];
    printf("Enter the title of the book: ");

    scanf("%s",title);
    for(int i = 0; i < bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            printf("Book found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Genre: %s\n", books[i].genre);
            printf("Price: %.2f\n", books[i].price);
            printf("Library Name: %s\n", books[i].libraryName);
            printf("Shelf: %s\n", books[i].shelf);
            printf("Sold: %d\n", books[i].soldCount);
            return;
        }
    }

    printf("Book not found.\n");
}

void deleteBook(Book books[], int *bookCount) {
    printf("\nDeleting a book:\n");
    char title[100];
    printf("Enter the title of the book to delete: ");
    scanf("%s",title);

    for(int i = 0; i < *bookCount; i++) {
        if(strcmp(books[i].title, title) == 0 && books[i].soldCount == 0) {
            for(int j = i; j < *bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            (*bookCount)--;
            printf("Book deleted successfully!\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void assignBookToLibrary(Book books[], int bookCount, Shelf shelves[], int shelfCount) {
    printf("\nAssigning a book to a library:\n");
    char title[100];
    printf("Enter the title of the book: ");
    scanf("%s", title);

    for(int i = 0; i < bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            char libraryName[50];
            printf("Enter the name of the library: ");
            scanf("%s", libraryName);

            for(int j = 0; j < shelfCount; j++) {
                if(strcmp(shelves[j].libraryName, libraryName) == 0) {
                    strcpy(books[i].libraryName, libraryName);
                    printf("Book assigned to library successfully!\n");
                    return;
                }
            }

            printf("Library not found.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void sellBook(Book books[], int *bookCount) {
    printf("\nSelling a book:\n");
    char title[100];
    printf("Enter the title of the book: ");
    scanf("%s", title);

    for(int i = 0; i < *bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            books[i].soldCount = 1;
            printf("Book sold successfully!\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void viewSoldBooksHistory(Book books[], int bookCount) {
    printf("\nViewing sold books history:\n");
    for(int i = 0; i < bookCount; i++) {
        if(books[i].soldCount == 1) {
            printf("Book found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Genre: %s\n", books[i].genre);
            printf("Price: %.2f\n", books[i].price);
            printf("Library Name: %s\n", books[i].libraryName);
            printf("Shelf: %s\n", books[i].shelf);
            printf("-------------------------\n");
        }
    }
}

void displayStockedBooks(Book books[], int bookCount) {
    printf("\nViewing sold books history:\n");

    for(int i = 0; i < bookCount; i++) {
        if(books[i].soldCount == 0) {
            printf("Book found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Genre: %s\n", books[i].genre);
            printf("Price: %.2f\n", books[i].price);
            printf("Library Name: %s\n", books[i].libraryName);
            printf("Shelf: %s\n", books[i].shelf);
            printf("-------------------------\n");
        }
    }
}

void printMenu() {
    printf("\nMain Menu:\n");
    printf("1. Add Book\n");
    printf("2. Search Book\n");
    printf("3. Delete Book\n");
    printf("4. Display Stocked Books\n");
    printf("5. Assign Book to Library\n");
    printf("6. Sell Book\n");
    printf("7. View Sold Books History\n");
    printf("8. Save Current Data\n");
    printf("9. Exit\n");
}

int main() {
    Library libraries[MAX_LIBRARIES];
    Shelf shelves[MAX_SHELVES];
    Book books[MAX_BOOKS];
    int libraryCount, shelfCount, bookCount;

    loadLibraries(libraries, &libraryCount);
    loadShelves(shelves, &shelfCount);
    loadBooks(books, &bookCount);

    int choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Delete Book\n");
        printf("4. Display Stocked Books\n");
        printf("5. Assign Book to Library\n");
        printf("6. Sell Book\n");
        printf("7. View Sold Books History\n");
        printf("8. Save Current Data\n");
        printf("9. Exit\n");

        printf("Enter your choice (1-9): ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &bookCount);
                break;
            case 2:
                searchBook(books, bookCount);
                break;
            case 3:
                deleteBook(books, &bookCount);
                break;
            case 4:
                displayStockedBooks(books, bookCount);
                break;
            case 5:
                assignBookToLibrary(books, bookCount, shelves, shelfCount);
                break;
            case 6:
                sellBook(books, &bookCount);
                break;
            case 7:
                viewSoldBooksHistory(books, bookCount);
                break;
            case 8:
                saveBooks(books, bookCount);
                updateBooksData(books, bookCount);
                printf("Data saved successfully.\n");
                break;
            case 9:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}