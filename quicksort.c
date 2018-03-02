#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SZ 20000

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition (int *v, int min, int max) {
    int i = min - 1, j, pivot = v[max];

    for (j = min; j <= max; j++) {
        if (v[j] < pivot) {
            i++;
            swap (&v[i], &v[j]);
        }
    }
    swap (&v[i+1], &v[max]);

    return i + 1;
}

void quicksort (int *v, int min, int max) {
    if (min < max) {
        int pi = partition (v, min, max);

        quicksort(v, pi + 1, max);
        quicksort(v, min, pi - 1);
    }
}

void log_to_file (int *v, FILE *fp, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        fprintf(fp, "%d\n", v[i]);
    }
}

int main () {
    srand(time(NULL));

    int i, v[SZ];
    for (i = 0; i < SZ; i++) {
        v[i] = (rand() % SZ) + 1;
    }
    FILE *unordered = fopen("unordered.txt", "w");
    log_to_file(v, unordered, SZ);

    clock_t begin = clock();
    quicksort (v, 0, SZ - 1);
    clock_t end = clock();

    FILE *ordered = fopen("ordered.txt", "w");
    log_to_file(v, ordered, SZ);

    printf("\nQuicksort time: %.2f\n", (double)(end - begin));

    fclose(unordered);
    fclose(ordered);

    return 0;
}
