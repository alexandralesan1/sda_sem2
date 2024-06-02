#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct magazin {
    int ziua;
    int luna;
    int anul;
    int id_produs;
    float pret_unit;
    int cantitate;
    char nume_produs[100];
    char categorie_produs[100];
    char tara[100];
    char orasul[100];
    char sub_categorie[100];
    float venit_total;
     int numar_vanzari_total;
} Magazin;

void orasMaxVanzari(Magazin *m, int size) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp(m[i].tara, n[j].tara) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].numar_vanzari_total = 0;
        n[i].orasul[0] = '\0';
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].tara, m[j].tara) == 0) {
                if (m[j].cantitate > n[i].numar_vanzari_total) {
                    n[i].numar_vanzari_total = m[j].cantitate;
                    strcpy(n[i].orasul, m[j].orasul);
                }
            }
        }
    }

    printf("\n\nOrasul cu cele mai multe vanzari pentru fiecare tara: \n");
    for (int i = 0; i < newSize-1; i++) {
        printf("%s, %s :   %d vanzari\n", n[i].tara, n[i].orasul, n[i].numar_vanzari_total);
    }

    free(n);
}
void fix(Magazin *m, int size) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp(m[i].categorie_produs, n[j].categorie_produs) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].numar_vanzari_total = 0;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].categorie_produs, m[j].categorie_produs) == 0) {
                n[i].numar_vanzari_total += m[j].cantitate;
            }
        }
    }


    printf("\n\n Categorii: \n");
    for (int i = 0; i < 12; i++) {
        printf("%d. %s :   %d vanzari\n", i + 1, n[i].categorie_produs, n[i].numar_vanzari_total);
    }

}

void bestvenit(Magazin *m, int size) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp(m[i].nume_produs, n[j].nume_produs) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].venit_total = 0;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].nume_produs, m[j].nume_produs) == 0) {
                n[i].venit_total += m[j].pret_unit;
            }
        }
    }

    Magazin temp;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize - 1; j++) {
            if (n[j].venit_total < n[j + 1].venit_total) {
                temp = n[j];
                n[j] = n[j + 1];
                n[j + 1] = temp;
            }
        }
    }

    printf("\n\nTop 5 produse: \n");
    for (int i = 0; i < 5 && i < newSize; i++) {
        printf("%d. %s :   %.2f\n", i + 1, n[i].nume_produs, n[i].venit_total);
    }

    free(n);
}

void venitlunar(Magazin *m, int size, int luna) {
    float monthlyIncome[10000][12] = {0};

    for (int i = 0; i < size; i++) {
        if (m[i].luna == luna) {
            monthlyIncome[m[i].anul][luna - 1] += m[i].pret_unit;
        }
    }

    printf("An\tVenit Total\n");
    for (int j = 0; j < 10000; j++) {
        if (monthlyIncome[j][luna - 1] != 0) {
            printf("%d\t%.2f\n", j, monthlyIncome[j][luna - 1]);
        }
    }
}
void tendinteVanzari(Magazin *m, int size, char subcategorie[100], int an) {
    // Inițializăm un vector pentru a stoca vânzările lunare pentru subcategoria dată
    float vanzariLunare[12] = {0};

    // Calculăm vânzările lunare pentru subcategoria și anul specificat
    for (int i = 0; i < size; i++) {
        if (strcmp(m[i].sub_categorie, subcategorie) == 0 && m[i].anul == an) {
            vanzariLunare[m[i].luna - 1] += m[i].cantitate;
        }
    }

    // Afișăm graficul de linii pentru tendințele vânzărilor lunare
    printf("\nTendinte in vanzarile lunare pentru subcategoria '%s' in anul %d:\n", subcategorie, an);
    printf("Luna | Vanzari\n");
    printf("-----|--------\n");
    for (int i = 0; i < 12; i++) {
        printf("%4d |", i + 1);
        for (int j = 0; j < vanzariLunare[i]; j++) {
            printf("*");
        }
        printf(" %.0f\n", vanzariLunare[i]);
    }
}

int Import(Magazin **m, FILE *file) {
    int size = 10000;
    int counter = 0;

    while (fscanf(file, "%d-%d-%d,%d,%99[^,],%99[^,],%99[^,],%f,%d,%99[^,],%99[^\n]\n",
                  &(*m)[counter].anul, &(*m)[counter].luna, &(*m)[counter].ziua,
                  &(*m)[counter].id_produs, (*m)[counter].nume_produs, (*m)[counter].categorie_produs,
                  (*m)[counter].sub_categorie, &(*m)[counter].pret_unit, &(*m)[counter].cantitate,
                  (*m)[counter].tara, (*m)[counter].orasul) == 11) {

        if (counter >= size) {
            size = size * 2;
            *m = realloc(*m, size * sizeof(Magazin));

            if (*m == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                return counter;
            }
        }

        counter++;
    }

    return counter;
}

int main() {
    FILE *file = fopen("sales.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    int size = 100000;
    char subcategoria[100];
    Magazin *m = malloc(size * sizeof(Magazin));
    if (m == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int counter = 0;
    counter = Import(&m, file);
    fclose(file);

    int choice;
    int luna;
    int an;

    do {
       printf("\n=== Meniu ===\n");
printf("1. Venit lunar\n");
printf("2. Top 5 produse\n");
printf("3. Distributia vanzarilor pe categorii\n");
printf("4. Oras cu cele mai multe vanzari pentru fiecare tara\n");
printf("5. Tendinte in vanzarile lunare pentru diferite subcategorii de produse\n");
printf("0. Iesire\n");
printf("Alege o optiune: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Alege luna (1-12): ");
                scanf("%d", &luna);
                venitlunar(m, counter, luna);
                break;
            case 2:
                bestvenit(m, counter);
                break;
            case 3:
                fix(m, counter);
                break;
            case 4:
                orasMaxVanzari(m, counter);
                break;
case 5:
    printf("Introdu subcategoria: ");
    scanf("%s", subcategoria);
    printf("Introdu anul: ");
    scanf("%d", &an);
    tendinteVanzari(m, counter, subcategoria, an);
    break;

            case 0:
                printf("Programul s-a incheiat.\n");
                break;
            default:
                printf("Optiune invalida. Te rog sa alegi din nou.\n");
        }
    } while (choice != 0);

    free(m);
    return 0;
}
