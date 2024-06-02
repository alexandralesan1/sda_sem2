#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long fib(int n) {
    unsigned long long fib[n + 2];
    int i;

    fib[0] = 0;
    fib[1] = 1;

    for (i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int generate_random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

void initialize_array(int *array, int size, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = generate_random_number(min, max);
    }
}

void print_array(int *array, int size) {
    printf("Tablou: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void free_array(int *array) {
    free(array);
}

void selection_sort(int *array, int size) {
    clock_t start = clock();

    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        int temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sortare folosind Selection Sort: %f secunde\n", time_spent);
}

void merge(int *array, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *array, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

int linear_search(int *array, int size, int key) {
    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            clock_t end = clock();
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Cautare folosind Linear Search: %f secunde\n", time_spent);
            return i;
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elementul nu a fost gasit. Timpul de cautare: %f secunde\n", time_spent);
    return -1;
}

int binary_search(int *array, int size, int key) {
    int left = 0, right = size - 1;
    clock_t start = clock();

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == key) {
            clock_t end = clock();
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Cautare folosind Binary Search: %f secunde\n", time_spent);
            return mid;
        }

        if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Dacă nu găsim cheia în tablou
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elementul nu a fost gasit. Timpul de cautare: %f secunde\n", time_spent);
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int *array = NULL;
    int size, min, max;
    int optiune;

    do {
        printf("\nMeniu:\n");
        printf("1. Initializare tablou cu numere aleatorii\n");
        printf("2. Afisare tablou\n");
        printf("3. Eliberare memorie tablou\n");
        printf("4. Sortare tablou folosind Selection Sort\n");
        printf("5. Sortare tablou folosind Merge Sort\n");
        printf("6. Cautare numar in tablou folosind Linear Search\n");
        printf("7. Cautare numar in tablou folosind Binary Search\n");
        printf("8. Calculare element din sirul lui Fibonacci\n");
        printf("0. Iesire\n");
        printf("Alegeti optiunea: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 1:
                printf("Introduceti dimensiunea tabloului: ");
                scanf("%d", &size);
                printf("Introduceti valoarea minima pentru numerele aleatorii: ");
                scanf("%d", &min);
                printf("Introduceti valoarea maxima pentru numerele aleatorii: ");
                scanf("%d", &max);

                array = (int *)malloc(size * sizeof(int));
                if (array == NULL) {
                    printf("Alocare de memorie esuata\n");
                    return 1;
                }

                initialize_array(array, size, min, max);
                break;
            case 2:
                if (array == NULL) {
                    printf("Tabloul nu este initializat\n");
                } else {
                    print_array(array, size);
                }
                break;
            case 3:
                if (array != NULL) {
                    free_array(array);
                    array = NULL;
                    printf("Memoria tabloului a fost eliberata\n");
                } else {
                    printf("Tabloul nu este initializat\n");
                }
                break;
            case 4:
                if (array == NULL) {
                    printf("Tabloul nu este initializat\n");
                } else {
                    clock_t start = clock();

                    selection_sort(array, size);

                    clock_t end = clock();
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("Sortare folosind Selection Sort: %f secunde\n", time_spent);
                }
                break;
            case 5:
                if (array == NULL) {
                    printf("Tabloul nu este initializat\n");
                } else {
                    clock_t start = clock();

                    merge_sort(array, 0, size - 1);

                    clock_t end = clock();
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("Sortare folosind Merge Sort: %f secunde\n", time_spent);
                }
                break;
            case 6:
                if (array == NULL) {
                    printf("Tabloul nu este initializat\n");
                } else {
                    int key;
                    printf("Introduceti numarul pe care doriti sa-l cautati in tablou: ");
                    scanf("%d", &key);
                    int index = linear_search(array, size, key);
                    if (index != -1) {
                        printf("Numarul %d a fost gasit pe pozitia %d in tablou\n", key, index);
                    } else {
                        printf("Numarul %d nu a fost gasit in tablou\n", key);
                    }
                }
                break;
            case 7:
                if (array == NULL) {
                    printf("Tabloul nu este initializat\n");
                } else {
                    int key;
                    printf("Introduceti numarul pe care doriti sa-l cautati in tablou: ");
                    scanf("%d", &key);
                    int index = binary_search(array, size, key);
                    if (index != -1) {
                        printf("Numarul %d a fost gasit pe pozitia %d in tablou\n", key, index);
                    } else {
                        printf("Numarul %d nu a fost gasit in tablou\n", key);
                    }
                }
                break;
            case 8:
                {
                    int position;
                    printf("Introduceti pozitia elementului din sirul lui Fibonacci (intre 50 si 1000000): ");
                    scanf("%d", &position);

                    if (position < 50 || position > 1000000) {
                        printf("Pozitia trebuie sa fie intre 50 si 1000000.\n");
                    } else {
                        clock_t start = clock();
                        unsigned long long result = fib(position);
                        clock_t end = clock();
                        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                        printf("Elementul de la pozitia %d din sirul lui Fibonacci este: %llu\n", position, result);
                        printf("Timpul de calcul: %f secunde\n", time_spent);
                    }
                }
                break;
            case 0:
                printf("Iesire din program\n");
                if (array != NULL) {
                    free_array(array);
                }
                break;
            default:
                printf("Optiune invalida\n");
        }
    } while (optiune != 0);

    return 0;
}
