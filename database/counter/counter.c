#include "counter.h"
#include <stdio.h>


static const char filename[] = "counter.txt";

int getCounter() {
    FILE *f;
    int counter;

    if (fopen_s(&f, filename, "r")) {
        printf("Error opening file '%s'", filename);
        return 0;
    }

    fscanf_s(f, "%d", &counter);

    fclose(f);

    return counter;

}

int setCounter(int counter) {
    FILE *f;

    if (fopen_s(&f, filename, "w")) {
        printf("Error opening file '%s'", filename);
        return 0;
    }

    fprintf(f, "%d", counter);
    fclose(f);
    return 1;
}

void incCounter() {
    int counter;

    counter = getCounter();
    counter++;
    setCounter(counter);
}



