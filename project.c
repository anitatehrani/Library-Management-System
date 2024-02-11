#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBRARIES 100
#define MAX_SHELVES 100
#define MAX_BOOKS 100

typedef struct {
    char address[20];
    char name[50];
} Library;

typedef struct {
    char genre[20];
    char libraryName[50];
    int capacity;
    char shelfName[20];

} Shelf;

typedef struct {
    char title[100];
    char author[50];
    long long int ISBN;
    char genre[20];
    float price;
    char nasher[20];
    int inLibrary;
    char libraryName[50];
    char shelf[20];
} Book;

typedef struct {
    char title[100];
    char author[50];
    long long int ISBN;
    char genre[20];
    float price;
    char nasher[20];
    char libraryName[50];
    char buyerName[50];
} SoldBooks;


void loadLibraries(Library libraries[], int *libraryCount) {
    FILE *file = fopen("libraries.csv", "r");
    if (file==NULL) {
        printf("Error opening libraries.csv file.\n");
        exit(1);
    }

    *libraryCount = 0;
    while (fscanf(file, "%49[^,],%19[^,\n]\n", libraries[*libraryCount].name, libraries[*libraryCount].address) == 2) {
        (*libraryCount)++;
    }

    fclose(file);
}

void loadShelves(Shelf shelves[], int *shelfCount) {
    FILE *file = fopen("shelves.csv", "r");
    if (file==NULL) {
        printf("Error opening shelves.csv file.\n");
        exit(1);
    }

    *shelfCount = 0;
    while (fscanf(file, "%49[^,],%19[^,],%d,%19[^,\n]\n", shelves[*shelfCount].libraryName, shelves[*shelfCount].shelfName, &shelves[*shelfCount].capacity,shelves[*shelfCount].genre) == 4) {
        (*shelfCount)++;
    }

    fclose(file);
}

void loadBooks(Book books[], int *bookCount) {
    FILE *file = fopen("books.csv", "r");
    if (file==NULL) {
        printf("Error opening books.csv file.\n");
        exit(1);
    }

    *bookCount = 0;
    while (fscanf(file, "%99[^,],%49[^,],%lld,%19[^,],%f,%19[^,],%d,%49[^,],%19[^,\n]\n",
                  books[*bookCount].title, books[*bookCount].author,&books[*bookCount].ISBN,books[*bookCount].genre,
                  &books[*bookCount].price,books[*bookCount].nasher,&books[*bookCount].inLibrary,
                  books[*bookCount].libraryName, books[*bookCount].shelf) == 9) {
        (*bookCount)++;
    }
    fclose(file);
}
void loadSoldBooks(SoldBooks soldBooks[], int *soldbooksCount) {
    FILE *file = fopen("soldbooks.csv", "r");
    if (file==NULL) {
        printf("Error opening soldbooks.csv file.\n");
        exit(1);
    }

    *soldbooksCount = 0;
    while (fscanf(file, "%99[^,],%49[^,],%lld,%19[^,],%f,%19[^,],%50[^,],%49[^,\n]\n",
                  soldBooks[*soldbooksCount].title, soldBooks[*soldbooksCount].author,&soldBooks[*soldbooksCount].ISBN
                  ,soldBooks[*soldbooksCount].genre,&soldBooks[*soldbooksCount].price,soldBooks[*soldbooksCount].nasher
                  ,soldBooks[*soldbooksCount].buyerName,soldBooks[*soldbooksCount].libraryName ) == 8) {
        (*soldbooksCount)++;
    }
    fclose(file);
}

void saveBooks(Book books[], int bookCount) {
    FILE *file = fopen("books.csv", "w");
    if (file==NULL) {
        printf("Error opening books.csv file for writing.\n");
        exit(1);
    }

    for(int i = 0; i < bookCount; i++) {
         fprintf(file, "%s,%s,%lld,%s,%.2f,%s,%d,%d,%s,%s\n",
                books[i].title, books[i].author,books[i].ISBN, books[i].genre,
                books[i].price,books[i].nasher, books[i].inLibrary,
                books[i].libraryName, books[i].shelf);
    }

    fclose(file);
}

void updateBooksData(Book books[], int bookCount) {
    FILE *file = fopen("books.csv", "w");
    if (file==NULL) {
        printf("Error opening books.csv file for writing.\n");
        exit(1);
    }

    for(int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%lld,%s,%.2f,%s,%d,%s,%s\n",
                books[i].title, books[i].author,books[i].ISBN, books[i].genre,
                books[i].price,books[i].nasher, books[i].inLibrary,
                books[i].libraryName, books[i].shelf);
    }

    fclose(file);
}

void updateShelvesData(Shelf Shelves[], int shelfCount) {
    FILE *file = fopen("shelves.csv", "w");
    if (file==NULL) {
        printf("Error opening shelves.csv file for writing.\n");
        exit(1);
    }

    for(int i = 0; i < shelfCount; i++) {
        fprintf(file, "%s,%s,%d,%s\n",
                Shelves[i].libraryName, Shelves[i].shelfName,Shelves[i].capacity, Shelves[i].genre);
    }

    fclose(file);
}
void updateSoldBooksData(SoldBooks soldBooks[], int soldbooksCount) {
    FILE *file = fopen("soldbooks.csv", "w");
    if (file==NULL) {
        printf("Error opening shelves.csv file for writing.\n");
        exit(1);
    }

    for(int i = 0; i < soldbooksCount; i++) {
        fprintf(file, "%s,%s,%lld,%s,%.2f,%s,%s,%s\n",
                soldBooks[i].title, soldBooks[i].author,soldBooks[i].ISBN, soldBooks[i].genre,
                soldBooks[i].price,soldBooks[i].nasher, soldBooks[i].buyerName,
                soldBooks[i].libraryName);
    }

    fclose(file);
}


void PrintBook(Book *p){
   printf("title:%s\n",p->title);
   printf("author:%s\n",p->author);
   printf("ISBN:%lld\n",p->ISBN);
   printf("genre:%s\n",p->genre);
   printf("price:%f\n",p->price);
   printf("nasher:%s\n",p->nasher);
   putchar('\n');
}

void addBook(Book books[], int *bookCount) {
    printf("\nAdding a new book:\n");

    printf("Enter Title: ");
    scanf("%s",books[*bookCount].title);

    printf("Enter author: ");
    scanf("%s",books[*bookCount].author);
    long long int ISBN;
    printf("Enter ISBN: ");
    scanf("%lld",&ISBN);
    books[*bookCount].ISBN=ISBN;
    printf("Enter genre: ");
    scanf("%s",books[*bookCount].genre);

    printf("Enter price: ");
    scanf("%f", &books[*bookCount].price);

    printf("Enter nasher: ");
    scanf("%s",books[*bookCount].nasher);
    char a[100];
    books[*bookCount].inLibrary = 0;
    strcpy(books[*bookCount].libraryName, a);
    strcpy(books[*bookCount].shelf, a);
    (*bookCount)++;
    printf("Book added successfully!\n");
}

void searchBook(Book books[], int bookCount) {
    printf("Which filter do you want to use?\n");
    int choice;
    char title[100];
    char author[50];
    long long int ISBN;
    char genre[20];
    float price;
    char nasher[20];
    int inLibrary;
    char libraryName[50];
    char shelf[20];

    printf("1.title\n2.author\n3.ISBN\n4.genre\n5.price\n6.nasher\n");
    scanf("%d", &choice );
    switch (choice)
    {
    case 1:
        printf("Enter title:\n");
         scanf("%s",title);
         for(int j=0;j<bookCount;j++)
         {
            if(strcmp(books[j].title,title)==0){
               PrintBook(&books[j]);
            }
         }
        break;
    case 2:
        printf("Enter author:\n");
         scanf("%s",author);
         for(int j=0;j<bookCount;j++)
         {
            if(strcmp(books[j].author,author)==0){
               PrintBook(&books[j]);
            }
         }
        break;
    case 3:
        printf("Enter ISBN:\n");
         scanf("%d",&ISBN);
         for(int j=0;j<bookCount;j++)
         {
            if(books[j].ISBN==ISBN){
               PrintBook(&books[j]);
            }
         }
        break;
    case 4:
        printf("Enter genre:\n");
         scanf("%s",genre);
         for(int j=0;j<bookCount;j++)
         {
            if(strcmp(books[j].genre,genre)==0){
               PrintBook(&books[j]);
            }
         }
        
        break;
    case 5:
        printf("Enter price:\n");
         scanf("%d",&price);
         for(int j=0;j<bookCount;j++)
         {
            if(books[j].price==price){
               PrintBook(&books[j]);
            }
         }
        break;
    case 6:
        printf("Enter nasher:\n");
         scanf("%s",nasher);
         for(int j=0;j<bookCount;j++)
         {
            if(strcmp(books[j].nasher,nasher)==0){
               PrintBook(&books[j]);
            }
         }
        break;                 
    }
}


void deleteBook(Book books[], int *bookCount,Shelf shelves[], int shelfCount) {
    printf("\nDeleting a book:\n");
    char title[100];
    for(int i=0;i<*bookCount;i++){
       printf("%d.%s\n",i+1,books[i].title); 
      
    }
    printf("--------------------\n");
    printf("Enter the title of the book to delete: \n");
    scanf("%s",title);
    
    for(int i = 0; i < *bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            for (int j = 0; j < shelfCount; j++) {
                if (strcmp(shelves[j].libraryName, books[i].libraryName) == 0) {
                    if (strcmp(shelves[j].shelfName, books[i].shelf) == 0) {
                        shelves[j].capacity = shelves[j].capacity + 1;
                        break;
                    }
                }
            }
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

void assignBookToLibrary(Book books[], int bookCount, Shelf shelves[], int shelfCount,Library libraries[],int libraryCount) {
    printf("\nAssigning a book to a library:\n");
    char title[100];
    for(int i=0;i<bookCount;i++){
       printf("%d.%s\n",i+1,books[i].title); 
      
    }
    printf("--------------------\n");
    printf("Enter the title of the book to assign: \n");
    scanf("%s", title);

    for(int i = 0; i < bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            char libraryName[50];
            printf("Libraries :\n");
             int cur=-1;
             for(int k=0;k<libraryCount;k++){
                
                for(int j = 0; j < shelfCount; j++){ 

                   if(strcmp(libraries[k].name,shelves[j].libraryName)==0 && shelves[j].capacity!= 0 && strcmp(books[i].genre,shelves[j].genre)==0){   
                   cur=j;
                   }

                }           
                if(cur!=-1){
                   printf("%d.%s\n",k+1,libraries[k].name);
                }
             }
            if(cur == -1){
                printf("Library not found.\n");
                return;
            }
             printf("--------------------\n");
             printf("Select the name of the library: ");
             scanf("%s", libraryName);

            int count=0,temp=0;
            for(int j = 0; j < shelfCount; j++) {
                if (strcmp(shelves[j].libraryName, libraryName) == 0 && shelves[j].capacity > 0 && (count ==0 || shelves[j].capacity < count)) {
//                    printf("capacity:%d\n", shelves[j].capacity);
                    count = shelves[j].capacity;
                    temp = j;
                }
            }
//            printf("temp:%d\n",temp);
//            exit(1);
          if(temp!=0) {
              if (books[i].inLibrary == 1) {
//                  printf("Book already assigned to library.\n");
                  for (int j = 0; j < shelfCount; j++) {
                      if (strcmp(shelves[j].libraryName, books[i].libraryName) == 0) {
                          if (strcmp(shelves[j].shelfName, books[i].shelf) == 0) {
                              shelves[j].capacity = shelves[j].capacity + 1;
                              break;
                          }
                      }
                  }
              }
              strcpy(books[i].libraryName, libraryName);
              strcpy(books[i].shelf, shelves[temp].shelfName);
              books[i].inLibrary = 1;
              printf("Book assigned to library successfully!\n");
              shelves[temp].capacity = shelves[temp].capacity - 1;
              return;
          }
              
             
            printf("Library not found.\n");
            return;
        }
    }
    

    printf("Book not found.\n");
}

void sellBook(Book books[], int *bookCount, Shelf shelves[], int shelfCount,Library libraries[],int libraryCount, SoldBooks soldbooks[], int *soldbooksCount) {
    printf("\nSelling a book:\n");
    char libraryName[50];
    printf("Libraries :\n");

    for(int i=0;i<libraryCount;i++){
        printf("%d.%s\n",i+1,libraries[i].name);
    }

    printf("--------------------\n");
    printf("Select the name of the library: ");
    scanf("%s", libraryName);

    printf("Books :\n");
    char title[100];
    int count=0;
//    printf("%d",bookCount);
    for(int i=0;i < *bookCount;i++){
        if(strcmp(books[i].libraryName,libraryName)==0){
            if(books[i].inLibrary==1) {
                count++;
                printf("%d.%s\n", i + 1, books[i].title);
            }
        }
    }
    if(count == 0){
        printf("No books found.\n");
        return;
    }

    printf("--------------------\n");
    printf("Enter the title of the book: ");
    scanf("%s", title);
    for(int i = 0; i < *bookCount; i++) {
        if(strcmp(books[i].title, title) == 0) {
            PrintBook(&books[i]);
            break;
        }
    }
    char name[100];

    printf("--------------------\n");
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter the price you want to pay: ");
    float price ;
    scanf("%f", &price);
//    printf("price:%f\n",price);
//    exit(1);
    for(int i = 0; i < *bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].price <= price) {
                for (int j = 0; j < shelfCount; j++) {
                    if (strcmp(shelves[j].libraryName, books[i].libraryName) == 0) {
                        if (strcmp(shelves[j].shelfName, books[i].shelf) == 0) {
                            shelves[j].capacity = shelves[j].capacity + 1;
                            break;
                        }
                    }
                }

                strcpy(soldbooks[*soldbooksCount].title, books[i].title);
                strcpy(soldbooks[*soldbooksCount].author, books[i].author);
                soldbooks[*soldbooksCount].ISBN = books[i].ISBN;
                strcpy(soldbooks[*soldbooksCount].genre, books[i].genre);
                soldbooks[*soldbooksCount].price = books[i].price;
                strcpy(soldbooks[*soldbooksCount].nasher, books[i].nasher);
                strcpy(soldbooks[*soldbooksCount].buyerName, name);
                strcpy(soldbooks[*soldbooksCount].libraryName, books[i].libraryName);
                (*soldbooksCount)++;
                printf("Remaining amonut: %s\n", price - books[i].price);

                for (int j = i; j < *bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }

                printf("Book sold successfully!\n");
                return;
            } else {
                printf("Price is not enough.\n");
                return;
            }
            break;
        }
    }

    printf("Book not found.\n");
}

void viewSoldBooksHistory(SoldBooks soldbooks[], int *soldbooksCount) {
    printf("\nSelect one of the following:\n");
    int select ;

//    printf("\n1.Sort sold books history by buyer name\n");
//    printf("\n2.Sort sold books history by Library name\n");
//    scanf("%d", &select);

//    if(select == 1) {
//
//        printf("\nViewing sold books history by buyer name:\n");
//    } else if(select == 2) {
//
//        printf("\nViewing sold books history by library name:\n");
//    }

    for(int i = 0; i < *soldbooksCount; i++) {
        printf("Book found:\n");
        printf("Title: %s\n", soldbooks[i].title);
        printf("Author: %s\n", soldbooks[i].author);
        printf("Genre: %s\n", soldbooks[i].genre);
        printf("Price: %.2f\n", soldbooks[i].price);
        printf("Buyer: %s\n", soldbooks[i].buyerName);
        printf("Library Name: %s\n", soldbooks[i].libraryName);
        printf("-------------------------\n");
    }
}

void displayStockedBooks(Book books[], int bookCount) {
    printf("\nViewing stocked books:\n");
    printf("-------------------------\n");
    for(int i = 0; i < bookCount; i++) {
        if(books[i].inLibrary==0) {
            printf("Book found:\n");
            PrintBook(&books[i]);
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
    SoldBooks soldbooks[MAX_BOOKS];
    int libraryCount, shelfCount, bookCount, soldbooksCount;

    loadLibraries(libraries, &libraryCount);
    loadShelves(shelves, &shelfCount);
    loadBooks(books, &bookCount);
    loadSoldBooks(soldbooks, &soldbooksCount);

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
                deleteBook(books, &bookCount, shelves , shelfCount);
                break;
            case 4:
                displayStockedBooks(books, bookCount);
                break;
            case 5:
                assignBookToLibrary(books, bookCount, shelves, shelfCount,libraries,libraryCount);
                break;
            case 6:
                sellBook(books, &bookCount , shelves , shelfCount,libraries,libraryCount, soldbooks, &soldbooksCount);
                break;
            case 7:
                viewSoldBooksHistory(soldbooks, &soldbooksCount);
                break;
            case 8:
                //saveBooks(books, bookCount);
                updateBooksData(books, bookCount);
                updateShelvesData(shelves,shelfCount);
                updateSoldBooksData(soldbooks,soldbooksCount);
                printf("Data saved successfully.\n");
                break;
            case 9:
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 to 9.\n");
        }
    } while (choice != 9);

    return 0;
}