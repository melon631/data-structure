#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000
#define RUN 100

void make_random_array(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000001;
    }
}

void copy_array(int dst[], int src[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

long long insertion_sort(int A[], int n) {
    long long cmp = 0;

    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;

        cmp++;
        while (j >= 0 && A[j] > key) {
            cmp++;
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
    return cmp;
}

long long shell_sort_basic(int A[], int n) {
    long long cmp = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = A[i];
            int j = i;

            cmp++;
            while (j >= gap && A[j - gap] > key) {
                cmp++;
                A[j] = A[j - gap];
                j -= gap;
            }
            A[j] = key;
        }
    }
    return cmp;
}

long long shell_sort_knuth(int A[], int n) {
    long long cmp = 0;
    int gap = 1;

    while (gap < n / 3)
        gap = 3 * gap + 1;

    for (; gap >= 1; gap /= 3) {
        for (int i = gap; i < n; i++) {
            int key = A[i];
            int j = i;

            cmp++;
            while (j >= gap && A[j - gap] > key) {
                cmp++;
                A[j] = A[j - gap];
                j -= gap;
            }
            A[j] = key;
        }
    }
    return cmp;
}

int main() {
    srand(time(NULL));

    int original[N];
    int arr[N];

    long long insertion_total = 0;
    long long shell_basic_total = 0;
    long long shell_knuth_total = 0;

    for (int t = 0; t < RUN; t++) {
        make_random_array(original, N);

        copy_array(arr, original, N);
        insertion_total += insertion_sort(arr, N);

        copy_array(arr, original, N);
        shell_basic_total += shell_sort_basic(arr, N);

        copy_array(arr, original, N);
        shell_knuth_total += shell_sort_knuth(arr, N);
    }

    printf("Insertion Sort Average Comparisons : %.0f\n",
        (double)insertion_total / RUN);
    printf("Shell Sort (Basic Gap) Average     : %.0f\n",
        (double)shell_basic_total / RUN);
    printf("Shell Sort (Knuth Gap) Average     : %.0f\n",
        (double)shell_knuth_total / RUN);

    return 0;
}