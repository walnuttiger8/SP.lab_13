#include <stdio.h>
#include <stdlib.h>
#include "database/database.h"


int getOption() {
    int option;
    char menu[] = "Options:\n"
                  "\t[0] -> Init db.\n"
                  "\t[1] -> Print db.\n"
                  "\t[2] -> Get by publisher\n"
                  "\t[3] -> Get by index \n"
                  "\t[4] -> Change author\n"
                  "\t[5] -> Exit\n";

    printf("%s\n>> ", menu);
    scanf_s("%d", &option);
    return option;
}


void initDbOption() {
    int n;
    printf("N: ");
    scanf_s("%d", &n);

    init(n);
}

void getByPublisherOption() {
    char publisher[50];
    int n;

    printf("Publisher: ");
    scanf_s("%s", publisher, sizeof(publisher));

    struct T *t = getPublisherBooks(publisher, &n);


    for (int i = 0; i < n; i++) {
        printT(t[i]);
    }
}

void getByIndexOption() {
    int n;

    printf("n: ");
    scanf_s("%d", &n);

    struct T t = get(n);

    printT(t);
}


void changeAuthorOption() {
    int n;
    char author[50];

    printf("n: ");
    scanf_s("%d", &n);

    printf("\n author: ");
    scanf_s("%s", author, sizeof(author));

    changeAuthor(n, author);
}


int main() {
    srand(rand());
    int option;

    while (1) {
        option = getOption();

        switch (option) {
            case 0:
                initDbOption();
                break;
            case 1:
                print();
                break;
            case 2:
                getByPublisherOption();
                break;
            case 3:
                getByIndexOption();
                break;
            case 4:
                changeAuthorOption();
                break;
            case 5:
                return 0;
            default:
                break;
        }
    }

//    int k;
//    init(5);
//
//    print();

//    struct T *t = getPublisherBooks("Shamil", &k);
//    printf("\n");
//
//    for (int i = 0; i < k; i++) {
//        struct T ti = t[i];
//        printT(ti);
//    }
//
//    printf("\n");
//
//    printT(get(5));

//    changeAuthor(2, "Rofl");
//
//    printf("\n");
//    print();
//
    return 0;
}
