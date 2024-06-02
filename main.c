#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct aviaruta {
    char numarul[50];
    char destinatiaa[100];
    char ora_plecarii[50];
    char ora_sosirii[50];
    float costul;
};

void citire(struct aviaruta **tablou, int *n) {
    printf("Introduceti numarul de elemente din tablou: ");
    scanf("%d", n);
    *tablou = (struct aviaruta *)malloc(*n * sizeof(struct aviaruta));
    for (int i = 0; i < *n; i++) {
        printf("Introduceti informatiile pentru aviaruta %d: \n", i + 1);
        printf("Numarul: ");
        scanf(" %[^\n]%*c", (*tablou)[i].numarul);
        printf("Destinatiaa: ");
        scanf(" %[^\n]%*c", (*tablou)[i].destinatiaa);
        printf("Ora plecarii (ora:minute): ");
        scanf(" %[^\n]%*c", (*tablou)[i].ora_plecarii);
        printf("Ora sosirii (ora:minute): ");
        scanf(" %[^\n]%*c", (*tablou)[i].ora_sosirii);
        printf("Costul [cu cifre, euro]: ");
        scanf("%f", &(*tablou)[i].costul);
    }
}

void afisare(struct aviaruta *tablou, int n) {
    printf("Elementele din tablou sunt: \n");
    for (int i = 0; i < n; i++) {
        printf("%d. Numarul: %s, Destinatiaa: %s, Ora plecarii: %s, Ora sosirii: %s, Costul: %.2f\n", i + 1,
               tablou[i].numarul, tablou[i].destinatiaa, tablou[i].ora_plecarii, tablou[i].ora_sosirii, tablou[i].costul);
    }
}

int cautare(struct aviaruta *tablou, int n, char valoare[100])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(tablou[i].numarul, valoare) == 0)
        {
            return i;
        }
    }
    return -1;
}

void eliberare(struct aviaruta *tablou)
{
    free(tablou);
}

void sortare(struct aviaruta *tablou, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tablou[i].costul > tablou[j].costul)
            {
                struct aviaruta temp = tablou[i];
                tablou[i] = tablou[j];
                tablou[j] = temp;
            }
        }
    }
}

void inserare_final(struct aviaruta **tablou, int *n, struct aviaruta valoare)
{
    (*n)++;
    *tablou = (struct aviaruta *)realloc(*tablou, *n * sizeof(struct aviaruta));
    (*tablou)[*n - 1] = valoare;
}

void inserare_inceput(struct aviaruta **tablou, int *n, struct aviaruta valoare)
{
    (*n)++;
    *tablou = (struct aviaruta *)realloc(*tablou, *n * sizeof(struct aviaruta));
    for (int i = *n - 1; i >= 1; i--)
    {
        (*tablou)[i] = (*tablou)[i - 1];
    }
    (*tablou)[0] = valoare;
}

void inserare_pe_pozitie(struct aviaruta **tablou, int *n, struct aviaruta valoare, int pozitie)
{
    if (pozitie < 0 || pozitie > *n)
    {
        printf("Pozitie invalida!\n");
        return;
    }
    (*n)++;
    *tablou = (struct aviaruta *)realloc(*tablou, *n * sizeof(struct aviaruta));
    for (int i = *n - 1; i >= pozitie + 1; i--)
    {
        (*tablou)[i] = (*tablou)[i - 1];
    }
    (*tablou)[pozitie] = valoare;
}

void stergere_de_pe_pozitie(struct aviaruta **tablou, int *n, int pozitie)
{
    if (pozitie < 0 || pozitie >= *n)
    {
        printf("Pozitie invalida!\n");
        return;
    }
    for (int i = pozitie; i < *n - 1; i++)
    {
        (*tablou)[i] = (*tablou)[i + 1];
    }
    (*n)--;
    *tablou = (struct aviaruta *)realloc(*tablou, *n * sizeof(struct aviaruta));
}

void modificare(struct aviaruta *tablou, int n, int index, struct aviaruta nouaValoare) {
    if (index >= 0 && index < n) {
        tablou[index] = nouaValoare;
    } else {
        printf("Indexul este invalid.\n");
    }
}

void interschimbare(struct aviaruta *tablou, int n, int index1, int index2) {
    if (index1 >= 0 && index1 < n && index2 >= 0 && index2 < n) {
        struct aviaruta temp = tablou[index1];
        tablou[index1] = tablou[index2];
        tablou[index2] = temp;
    } else {
        printf("Indexuri invalide.\n");
    }
}

void salvare_in_fisier(struct aviaruta *tablou, int n, const char *numeFisier) {
    FILE *fisier = fopen(numeFisier, "w");
    if (fisier == NULL) {
        printf("Nu s-a putut deschide fisierul pentru salvare.\n");
        return;
    }
     fprintf(fisier, "%d ",n);
    for (int i = 0; i < n; i++) {
        fprintf(fisier, "%s %s %s %s %f\n", tablou[i].numarul, tablou[i].destinatiaa, tablou[i].ora_plecarii, tablou[i].ora_sosirii, tablou[i].costul);
    }
    fclose(fisier);
}

void citire_din_fisier(struct aviaruta **tablou, int *n, const char *numeFisier) {
    FILE *fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Nu s-a putut deschide fisierul pentru citire.\n");
        return;
    }
    fscanf(fisier, "%d", n);
    *tablou = (struct aviaruta *)malloc(*n * sizeof(struct aviaruta));
    printf("Numarul de elemente citite din fisier: %d\n", *n);
    for (int i = 0; i < *n; i++) {
        fscanf(fisier, "%s", (*tablou)[i].numarul);
        fscanf(fisier, "%s", (*tablou)[i].destinatiaa);
        fscanf(fisier, "%s", (*tablou)[i].ora_plecarii);
        fscanf(fisier, "%s", (*tablou)[i].ora_sosirii);
        fscanf(fisier, "%f", &((*tablou)[i].costul));
        printf("Elementul %d citit din fisier: Numarul:%s , Destinatiaa:%s , Ora plecarii:%s, Ora sosirii:%s , Costul:%.2f\n",
               i, (*tablou)[i].numarul, (*tablou)[i].destinatiaa, (*tablou)[i].ora_plecarii, (*tablou)[i].ora_sosirii, (*tablou)[i].costul);
    }
    fclose(fisier);
}




int main() {
    struct aviaruta *tablou = NULL;
    int n = 0;
    int optiune, pozitie;
    char numarul[50];
while (1)
  { printf("\n1.Alocare dinamica a memoriei.\n");
      printf("2.Citirea elementelor in tablou\n");
      printf("3. Afisarea elementelor din tablou\n");
      printf("4. Cautarea unui element dupa numarul\n");
      printf("5. Modificarea campurilor unui element din tablou\n");
      printf("6. Interschimbarea a doua elemente indicate din tablou \n");
      printf("7. Sortarea elementelor din tablou dupa cost\n");
      printf("8. Inserarea unui element nou la capatul tabloului\n");
      printf("9. Inserarea unui element nou la inceputul tabloului \n");
      printf("10. Inserarea unui element nou dupa elementul indicat al tabloului \n");
      printf("11. Inserarea unui element nou inaintea elementul indicat al tabloului.\n");
      printf("12. Stergerea de pe pozitie\n");
      printf("13. Salvarea informatiei despre elementele tabloului in fisier \n");
      printf("14. Citirea informației despre elementele tabloului din fisier.\n");
      printf("15. Eliberarea memoriei alocate pentru tablou. .\n");
      printf("16. Iesire din program. \n");
      printf("Introduceti optiunea: ");
      scanf("%d", &optiune);
      switch (optiune)
      {
      case 2:
          citire(&tablou, &n);
          break;
      case 3:
          afisare(tablou, n);
          break;
      case 4:
          printf("Introduceti numarul de cautat: ");
          scanf("%s", numarul);
          pozitie = cautare(tablou, n, numarul);
          if (pozitie == -1)	  {
              printf("Nu s-a gasit niciun element cu numarul %s\n", numarul);     }
          else	{
           printf("Elementul cu numarul %s a fost gasit la pozitia %d in tablou\n", numarul, pozitie);}
   break;
      case 7:
          sortare(tablou, n);
          printf("Elementele au fost sortate cu succes!\n");  break;
      case 8:
          printf("Introduceti informatiile pentru noua aviaruta la final: \n");
          struct aviaruta nou;
          printf("numarul: ");
          scanf(" %[^\n]%*c", nou.numarul);
          printf("destinatiaa:");
          scanf(" %[^\n]%*c", nou.destinatiaa);
          printf("ora_plecarii (ora:minute): ");
          scanf(" %[^\n]%*c", nou.ora_plecarii);
          printf("ora_sosirii (ora:minute) : ");
          scanf(" %[^\n]%*c", nou.ora_sosirii);
          printf("Costul [cu cifre in euro]: ");
          scanf("%f", &nou.costul);
          inserare_final(&tablou, &n, nou);  break;
      case 10:
          printf("Inserare element nou dupa elementul indicat al tabloului. : \n");

           struct aviaruta valoare;
          printf("numarul: ");
          scanf(" %[^\n]%*c", valoare.numarul);
          printf("destinatiaa:");
          scanf(" %[^\n]%*c", valoare.destinatiaa);
          printf("ora_plecarii (ora:minute): ");
          scanf(" %[^\n]%*c", valoare.ora_plecarii);
          printf("ora_sosirii (ora:minute) : ");
          scanf(" %[^\n]%*c", valoare.ora_sosirii);
          printf("Costul [cu cifre in euro]: ");
          scanf("%f", &valoare.costul);
          printf("Introduceti pozitia pe care doriti sa il inserati (in intervalul [0,%d]): ", n);
          scanf("%d", &pozitie);
          inserare_pe_pozitie(&tablou, &n, valoare, pozitie);
          break;

           case 11:
          printf("Inserare element nou ianinte elementul indicat al tabloului. : \n");

           struct aviaruta valoare2;
          printf("numarul: ");
          scanf(" %[^\n]%*c", valoare2.numarul);
          printf("destinatiaa:");
          scanf(" %[^\n]%*c", valoare2.destinatiaa);
          printf("ora_plecarii (ora:minute): ");
          scanf(" %[^\n]%*c", valoare2.ora_plecarii);
          printf("ora_sosirii (ora:minute) : ");
          scanf(" %[^\n]%*c", valoare2.ora_sosirii);
          printf("Costul [cu cifre in euro]: ");
          scanf("%f", &valoare2.costul);
          printf("Introduceti pozitia pe care doriti sa il inserati (in intervalul [0,%d]): ", n);
          scanf("%d", &pozitie);
          inserare_pe_pozitie(&tablou, &n, valoare2, pozitie);
          break;

      case 9:
          printf("Introduceti informatiile pentru noua aviaruta la inceput: \n");
          struct aviaruta nou2;
          printf("numarul: ");
          scanf(" %[^\n]%*c", nou2.numarul);
          printf("destinatiaa:");
          scanf(" %[^\n]%*c", nou2.destinatiaa);
          printf("ora_plecarii (ora:minute): ");
          scanf(" %[^\n]%*c", nou2.ora_plecarii);
          printf("ora_sosirii (ora:minute) : ");
          scanf(" %[^\n]%*c", nou2.ora_sosirii);
          printf("Costul [cu cifre in euro]: ");
          scanf("%f", &nou2.costul);
          inserare_inceput(&tablou, &n, nou2);  break;

          case 12:
          printf("Introduceti pozitia de pe care doriti sa stergeti elementul (in intervalul [0,%d]): ", n - 1);
          scanf("%d", &pozitie);
          stergere_de_pe_pozitie(&tablou, &n, pozitie);
          break;


      case 15:
          eliberare(tablou);
          printf("\nMemorie dinamica eliberata!\n");     break;
      case 1:
           printf("\nMemorie dinamica alocata automat!\n");  break;
      case 5:
          printf("Introduceti indexul elementului pe care doriti sa il modificati: ");
          scanf("%d", &pozitie);
          printf("Introduceti noile informatii pentru elementul %d: \n", pozitie);
          struct aviaruta nouaValoare;
          printf("numarul: ");
          scanf(" %[^\n]%*c", nouaValoare.numarul);
          printf("destinatiaa: ");
          scanf(" %[^\n]%*c", nouaValoare.destinatiaa);
          printf("ora_plecarii: ");
          scanf(" %[^\n]%*c", nouaValoare.ora_plecarii);
          printf("ora_sosirii: ");
          scanf(" %[^\n]%*c", nouaValoare.ora_sosirii);
          printf("Costul: ");
          scanf("%f", &nouaValoare.costul);
          modificare(tablou, n, pozitie, nouaValoare);
          break;
      case 6:
          printf("Introduceti indecsii a doua elemente pe care doriti sa le interschimbati: ");
          int index1, index2;
          scanf("%d %d", &index1, &index2);
          interschimbare(tablou, n, index1, index2);
          break;
      case 13:
          printf("Introduceti numele fisierului pentru salvare: ");
          char numeFisier[100];
          scanf("%s", numeFisier);
          salvare_in_fisier(tablou, n, numeFisier);
          break;
      case 14:
          printf("Introduceti numele fisierului pentru citire: ");
          char numeFisierCitire[10];
          scanf("%s", numeFisierCitire);
          citire_din_fisier(&tablou, &n, numeFisierCitire);
          break;

      case 16:
              printf("\nProgram incheiat! .\n");
         return 0;

      default:
          printf("\nProgram incheiat! .\n");
         return 0;
      }
  }
}
