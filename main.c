#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef struct Document
{
    int id_document;
    char *nume_document;
    int numar_linii_total;
    int linii_ramase;
    struct Document *next;
} Document;

typedef struct Imprimanta
{
    int id_imprimanta;
    int timp_imprimare;
    Document *document_imprimanta;
    struct Imprimanta *next;
} Imprimanta;

void adauga_document_in_coada(Document **coada_documente, int id, char *nume, int total_linii, int linii_ramase)
{
    Document *nou_document = (Document*)malloc(sizeof(Document));
    nou_document->id_document = id;
    nou_document->nume_document = strdup(nume);
    nou_document->numar_linii_total = total_linii;
    nou_document->linii_ramase = linii_ramase;
    nou_document->next = NULL;

    if (*coada_documente == NULL)
    {
        *coada_documente = nou_document;
    }
    else
    {
        Document *temp = *coada_documente;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = nou_document;
    }
}

void sterge_document_din_coada(Document **ref_documente, int id)
{
    if (*ref_documente == NULL)
    {
        printf("Coada de documente este goală\n");
        return;
    }

    Document *nod_curent = *ref_documente;
    Document *nod_anterior = NULL;

    while (nod_curent != NULL)
    {
        if (nod_curent->id_document == id)
        {
            if (nod_anterior == NULL)
            {
                *ref_documente = nod_curent->next;
                free(nod_curent);
                return;
            }
            else
            {
                nod_anterior->next = nod_curent->next;
                free(nod_curent);
                return;
            }
        }
        nod_anterior = nod_curent;
        nod_curent = nod_curent->next;
    }
}

Imprimanta *initializeaza_imprimanta()
{
    int timp_imprimare;
    static int nr_imprimante = 1;
    Imprimanta *imprimanta = (Imprimanta *)malloc(sizeof(Imprimanta));
    imprimanta->id_imprimanta = nr_imprimante;
    printf("Introduceți timpul de imprimare pentru imprimanta %d: ", nr_imprimante);
    scanf("%d", &timp_imprimare);
    getchar(); // Consumă caracterul newline
    imprimanta->timp_imprimare = timp_imprimare;
    imprimanta->document_imprimanta = NULL;
    imprimanta->next = NULL;
    nr_imprimante++;
    return imprimanta;
}

void adauga_imprimanta(Imprimanta **lista_imprimante)
{
    Imprimanta *noua_imprimanta = initializeaza_imprimanta();
    if (*lista_imprimante == NULL)
    {
        *lista_imprimante = noua_imprimanta;
    }
    else
    {
        Imprimanta *temp = *lista_imprimante;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = noua_imprimanta;
    }
}

void sterge_imprimanta(Imprimanta **lista_imprimante, int id_imprimanta)
{
    if (*lista_imprimante == NULL)
    {
        printf("Lista de imprimante este goală\n");
        return;
    }

    Imprimanta *nod_curent = *lista_imprimante;
    Imprimanta *imprimanta_anterioara = NULL;

    while (nod_curent)
    {
        if (nod_curent->id_imprimanta == id_imprimanta)
        {
            if (imprimanta_anterioara == NULL)
            {
                *lista_imprimante = nod_curent->next;
                free(nod_curent);
                return;
            }
            else
            {
                imprimanta_anterioara->next = nod_curent->next;
                free(nod_curent);
                return;
            }
        }
        imprimanta_anterioara = nod_curent;
        nod_curent = nod_curent->next;
    }
}

void distribuie_documente(Document **coada_documente, Imprimanta **lista_imprimante)
{
    if (*coada_documente == NULL || *lista_imprimante == NULL)
    {
        printf("Nu există documente sau imprimante disponibile.\n");
        return;
    }

    Document *nod_document = *coada_documente;
    Imprimanta *nod_imprimanta = *lista_imprimante;

    int imprimante_disponibile = 0;

    while (nod_imprimanta != NULL)
    {
        if ((nod_imprimanta->document_imprimanta == NULL) || (nod_imprimanta->document_imprimanta->linii_ramase == 0))
        {
            imprimante_disponibile++;
        }
        nod_imprimanta = nod_imprimanta->next;
    }

    if (imprimante_disponibile == 0)
    {
        printf("Nu există imprimante disponibile\n");
        return;
    }
    else
    {
        while (nod_document != NULL && imprimante_disponibile != 0)
        {
            if (nod_document->linii_ramase > 0)
            {
                int timp_max_imprimare = -1000;
                nod_imprimanta = *lista_imprimante;
                Imprimanta *imprimanta_selectata = nod_imprimanta;
                while (nod_imprimanta != NULL)
                {
                    if (timp_max_imprimare < nod_imprimanta->timp_imprimare && nod_imprimanta->document_imprimanta == NULL)
                    {
                        timp_max_imprimare = nod_imprimanta->timp_imprimare;
                        imprimanta_selectata = nod_imprimanta;
                    }
                    nod_imprimanta = nod_imprimanta->next;
                }
                if (imprimanta_selectata != NULL)
                {
                    imprimanta_selectata->document_imprimanta = nod_document;
                    printf("Documentul = %s(%d/%d) a fost alocat la imprimanta %d cu timpul %d\n",
                           imprimanta_selectata->document_imprimanta->nume_document,
                           imprimanta_selectata->document_imprimanta->linii_ramase,
                           imprimanta_selectata->document_imprimanta->numar_linii_total,
                           imprimanta_selectata->id_imprimanta,
                           imprimanta_selectata->timp_imprimare);
                    imprimante_disponibile--;
                }
            }
            nod_document = nod_document->next;
        }
    }
}

void afiseaza_stare_curenta_imprimante_si_documente(Document *coada_documente, Imprimanta *lista_imprimante)
{
    printf("Coada de documente:\n");
    Document *temp_document = coada_documente;

    while (temp_document != NULL)
    {
        printf("Document %d: %s (%d/%d)\n",
               temp_document->id_document,
               temp_document->nume_document,
               temp_document->linii_ramase,
               temp_document->numar_linii_total);
        temp_document = temp_document->next;
    }

    printf("\nLista de imprimante:\n");
    Imprimanta *temp_imprimanta = lista_imprimante;

    while (temp_imprimanta != NULL)
    {
        printf("Imprimanta %d: timp de imprimare %d\n",
               temp_imprimanta->id_imprimanta,
               temp_imprimanta->timp_imprimare);

        temp_imprimanta = temp_imprimanta->next;
    }
}

void actualizeaza_stare_imprimante_si_documente(Imprimanta **lista_imprimante)
{
    Imprimanta *nod_imprimanta = *lista_imprimante;
    int documente_neimprimate = 0;

    while (nod_imprimanta)
    {
        if (nod_imprimanta->document_imprimanta != NULL && nod_imprimanta->document_imprimanta->linii_ramase >= 0)
        {
            nod_imprimanta->document_imprimanta->linii_ramase -= nod_imprimanta->timp_imprimare;

            if (nod_imprimanta->document_imprimanta->linii_ramase <= 0)
            {
                nod_imprimanta->document_imprimanta->linii_ramase = 0;
                printf("Documentul %s(%d/%d) s-a tipărit cu imprimanta %d\n",
                       nod_imprimanta->document_imprimanta->nume_document,
                       nod_imprimanta->document_imprimanta->linii_ramase,
                       nod_imprimanta->document_imprimanta->numar_linii_total,
                       nod_imprimanta->id_imprimanta);
                nod_imprimanta->document_imprimanta = NULL;
            }
            else
            {
                documente_neimprimate++;
            }
        }
        nod_imprimanta = nod_imprimanta->next;
    }
    if (documente_neimprimate == 0)
        printf("Documentele sunt în curs de printare\n");
}

void elibereaza_memorie(Document **ref_documente, Imprimanta **ref_imprimante)
{
    Document *nod_document = *ref_documente;
    while (nod_document != NULL)
    {
        Document *temp_document = nod_document;
        nod_document = nod_document->next;
        free(temp_document->nume_document);
        free(temp_document);
    }
    *ref_documente = NULL;

    Imprimanta *nod_imprimanta = *ref_imprimante;
    while (nod_imprimanta != NULL)
    {
        Imprimanta *temp_imprimanta = nod_imprimanta;
        nod_imprimanta = nod_imprimanta->next;
        free(temp_imprimanta);
    }
    *ref_imprimante = NULL;
}

void arata_meniu()
{
    printf("\nAlegeti o optiune:\n");
    printf("1. Adauga documente\n");
    printf("2. Adauga imprimante\n");
    printf("3. Arata starea curenta a cozii de documente\n");
    printf("4. Anuleaza tiparirea unui element\n");
    printf("5. Elibereaza toata memoria\n");
    printf("6. Distribuie documentele din coada catre imprimante\n");
    printf("7. Actualizeaza starea imprimantelor si a documentelor\n");
    printf("8. Sterge o imprimanta după ID\n");
    printf("0. Iesire din program\n");
}

int main()
{
    Document *coada_documente = NULL;
    Imprimanta *lista_imprimante = NULL;
    int total_documente = 1;
    int optiune;

    while (optiune != 0)
    {
        int nr_imprimante;
        int nr_documente;
        char nume_document[30];
        int nr_total_linii;
        int nr_linii_ramase;
        int id_document_sters;
        int id_imprimanta_stearsa;

        arata_meniu();
        scanf("%d", &optiune);
        getchar();

        switch (optiune)
        {
            case 1:
                printf("Introduceți numărul de documente\n");
                scanf("%d", &nr_documente);
                getchar();

                for (int i = 1; i <= nr_documente; i++)
                {
                    int id = total_documente;
                    total_documente++;

                    printf("Introduceți numele documentului:\n");
                    scanf("%29s", nume_document);
                    getchar();

                    printf("Introduceți numărul total de linii:\n");
                    scanf("%d", &nr_total_linii);
                    getchar();

                    printf("Introduceți numărul de linii rămase de tipărit:\n");
                    scanf("%d", &nr_linii_ramase);
                    getchar();

                    adauga_document_in_coada(&coada_documente, id, nume_document, nr_total_linii, nr_linii_ramase);
                }
                break;

            case 2:
                printf("Introduceți numărul de imprimante de introdus\n");
                scanf("%d", &nr_imprimante);
                getchar();
                for (int i = 0; i < nr_imprimante; i++)
                {
                    adauga_imprimanta(&lista_imprimante);
                }
                break;

            case 3:
                afiseaza_stare_curenta_imprimante_si_documente(coada_documente, lista_imprimante);
                break;

            case 4:
                printf("Introduceți numărul documentului de șters\n");
                scanf("%d", &id_document_sters);
                sterge_document_din_coada(&coada_documente, id_document_sters);
                break;

            case 5:
                elibereaza_memorie(&coada_documente, &lista_imprimante);
                break;

            case 6:
                distribuie_documente(&coada_documente, &lista_imprimante);
                break;

            case 7:
                actualizeaza_stare_imprimante_si_documente(&lista_imprimante);
                break;

            case 8:
                printf("Introduceți ID-ul imprimantei\n");
                scanf("%d", &id_imprimanta_stearsa);
                sterge_imprimanta(&lista_imprimante, id_imprimanta_stearsa);
                break;

            case 0:
                elibereaza_memorie(&coada_documente, &lista_imprimante);
                exit(0);
                break;

            default:
                printf("Opțiune invalidă\n");
        }
    }

    return 0;
}
