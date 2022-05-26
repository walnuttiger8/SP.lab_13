#include "database.h"
#include "counter/counter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char filename[] = "FB.bin";

const char authors[4][50] = {
        "Sharipov\0",
        "Zaripov\0",
        "Abramov\0",
        "Latypov\0"
};

const char publishers[4][50] = {
        "Bulat\0",
        "Shamil\0",
        "Oleg\0",
        "Damir\0"
};

const char names[4][50] = {
        "Bible\0",
        "Rofli\0",
        "Cringes\0",
        "SP posobie dlya debilov\0"
};


struct T getRandomT() {
    struct T t;

    strcpy_s(t.author, sizeof(authors[0]), authors[rand() % 4]);
    strcpy_s(t.publisher, sizeof(publishers[0]), publishers[rand() % 4]);
    strcpy_s(t.name, sizeof(names[0]), names[rand() % 4]);
    t.year = rand() % 2023;

    return t;
}

int insert(struct T *t) {
    FILE *f;

    if (fopen_s(&f, filename, "a")) {
        printf("Error opening file '%s'", filename);
        return -1;
    }

    fwrite(t, sizeof(struct T), 1, f);
    fclose(f);

    incCounter();

    return 1;
}


int fill(struct T *t, int n) {
    FILE *f;

    setCounter(0);
    if (fopen_s(&f, filename, "wb")) {
        printf("Error opening file '%s'", filename);
        return -1;
    }

    fwrite(t, sizeof(struct T), n, f);

    setCounter(n);

    fclose(f);
    return 1;
}


int init(int n) {
    FILE *f;

    struct T *t = calloc(n, sizeof(struct T));

    for (int i = 0; i < n; i++) {
        t[i] = getRandomT();
    }

    fill(t, n);

    return 0;
}

struct T *read(int *k) {

    FILE *f;
    *k = getCounter();
    struct T *t;

    if (fopen_s(&f, filename, "rb")) {
        printf("Error opening file '%s'", filename);
        return 0;
    }

    t = calloc(*k, sizeof(struct T));
    fread(t, sizeof(struct T), *k, f);
    fclose(f);


    return t;
}


void printT(struct T t) {
    printf("T: %s; %s; %s; %d;\n", t.author, t.publisher, t.name, t.year);
}


int print() {
    int k;
    struct T *t = read(&k);

    for (int i = 0; i < k; i++) {
        printT(t[i]);
    }

    return 1;
}


struct T *getPublisherBooks(char *publisher, int *n) {
    int k;
    struct T *t = read(&k);
    struct T *result;
    struct T *temp;

    *n = 0;
    for (int i = 0; i < k; i++) {
        if (!strcmp(publisher, t[i].publisher)) {
            *n += 1;
            temp = calloc(*n, sizeof(struct T));
            for (int j = 0; j < *n - 1; j++) {
                temp[j] = result[j];
            }
            temp[*n - 1] = t[i];
            result = temp;
        }
    }
    if (*n > 0) {
        return result;
    } else {
        return -1;
    }
}

struct T get(int n) {
    int k;
    struct T *t = read(&k);


    return t[n - 1];
}


int changeAuthor(int n, char *author) {
    int k;
    struct T *t = read(&k);

    strcpy_s(t[n-1].author, sizeof(t[n-1].author), author);

    fill(t, k);
    return 0;
}
