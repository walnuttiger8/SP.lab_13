#ifndef LAB_13_DATABASE_H
#define LAB_13_DATABASE_H

#endif //LAB_13_DATABASE_H


struct T {
    char author[50];
    char name[50];
    char publisher[50];
    int year;
};

int init(int n);

struct T *read(int *k);

struct T *getPublisherBooks(char *publisher, int *n);

struct T get(int n);

int changeAuthor(int n, char *author);

int print();

void printT(struct T t);