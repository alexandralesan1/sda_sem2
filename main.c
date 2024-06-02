#include <stdio.h>
#include <stdlib.h>

struct Flight {
    int number;
    char destination[50];
    char departureTime[10];
    char arrivalTime[10];
    float ticketPrice;
    struct Flight *next;
};

struct Flight *head = NULL; // Capul listei

void adaugaElement() {
    struct Flight *nou = (struct Flight*)malloc(sizeof(struct Flight));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }
    printf("Introduceti numarul zborului: ");
    scanf("%d", &nou->number);
    printf("Introduceti destinatia: ");
    scanf("%s", nou->destination);
    printf("Introduceti ora de plecare: ");
    scanf("%s", nou->departureTime);
    printf("Introduceti ora de sosire: ");
    scanf("%s", nou->arrivalTime);
    printf("Introduceti pretul biletului: ");
    scanf("%f", &nou->ticketPrice);

    nou->next = NULL; // Noul element va fi ultimul din listă, deci următorul său va fi NULL

    if (head == NULL) { // Verifica dacă lista este goală
        head = nou;
    } else {
        struct Flight *temp = head;
        while (temp->next != NULL) { // Parcurge lista până la ultimul element
            temp = temp->next;
        }
        temp->next = nou; // Adaugă noul element la sfârșitul listei
    }
}


void afiseazaLista() {
    struct Flight *temp = head;
    printf("Lista de zboruri:\n");
    while (temp != NULL) {
        printf("Numar zbor: %d, Destinatie: %s, Ora plecare: %s, Ora sosire: %s, Pret: %.2f\n",
                temp->number, temp->destination, temp->departureTime, temp->arrivalTime, temp->ticketPrice);
        temp = temp->next;
    }
}

void cautaElement(int numarCautat) {
    struct Flight *temp = head;
    int gasit = 0;
    while (temp != NULL) {
        if (temp->number == numarCautat) {
            printf("Zborul cu numarul %d a fost gasit.\n", numarCautat);
            printf("Detalii zbor: Destinatie: %s, Ora plecare: %s, Ora sosire: %s, Pret: %.2f\n",
                temp->destination, temp->departureTime, temp->arrivalTime, temp->ticketPrice);
            gasit = 1;
            break;
        }
        temp = temp->next;
    }
    if (!gasit) {
        printf("Zborul cu numarul %d nu a fost gasit.\n", numarCautat);
    }
}

void elibereazaMemorie() {
    struct Flight *temp = head;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp); // Eliberează memoria pentru fiecare element al listei
    }
    printf("Memoria listei a fost eliberata.\n");
}

void sortarePret() {
    if (head == NULL || head->next == NULL) {
        printf("Lista este goala sau contine un singur element. Nu este nevoie de sortare.\n");
        return;
    }

    int schimbare;
    struct Flight *temp;
    struct Flight *ultim = NULL;

    do {
        schimbare = 0;
        temp = head;

        while (temp->next != ultim) {
            if (temp->ticketPrice > temp->next->ticketPrice) {
                // Schimbă pozițiile elementelor
                float tempPret = temp->ticketPrice;
                temp->ticketPrice = temp->next->ticketPrice;
                temp->next->ticketPrice = tempPret;
                schimbare = 1;
            }
            temp = temp->next;
        }
        ultim = temp;
    } while (schimbare);

    printf("Lista a fost sortata dupa pretul biletului.\n");
}

*

void insereazaLaPozitie(int pozitie) {
    if (pozitie < 0) {
        printf("Pozitie invalida.\n");
        return;
    }

    struct Flight *nou = (struct Flight*)malloc(sizeof(struct Flight));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }
    printf("Introduceti numarul zborului: ");
    scanf("%d", &nou->number);
    printf("Introduceti destinatia: ");
    scanf("%s", nou->destination);
    printf("Introduceti ora de plecare: ");
    scanf("%s", nou->departureTime);
    printf("Introduceti ora de sosire: ");
    scanf("%s", nou->arrivalTime);
    printf("Introduceti pretul biletului: ");
    scanf("%f", &nou->ticketPrice);

    if (pozitie == 0) {
        nou->next = head;
        head = nou;
    } else {
        struct Flight *temp = head;
        for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
            temp = temp->next;
        }
        if (temp == NULL) {
            printf("Pozitie invalida.\n");
            free(nou);
            return;
        }
        nou->next = temp->next;
        temp->next = nou;
    }
    printf("Elementul a fost inserat la pozitia %d.\n", pozitie);
}

void stergeDeLaPozitie(int pozitie) {
    if (head == NULL) {
        printf("Lista este goala. Nu exista elemente de sters.\n");
        return;
    }

    if (pozitie < 0) {
        printf("Pozitie invalida.\n");
        return;
    }

    if (pozitie == 0) {
        struct Flight *temp = head;
        head = head->next;
        free(temp);
        printf("Elementul de pe pozitia %d a fost sters.\n", pozitie);
        return;
    }

    struct Flight *anterior = head;
    struct Flight *curent = head->next;
    int i = 1;

    while (curent != NULL && i < pozitie) {
        anterior = anterior->next;
        curent = curent->next;
        i++;
    }

    if (curent == NULL) {
        printf("Pozitie invalida.\n");
        return;
    }

    anterior->next = curent->next;
    free(curent);
    printf("Elementul de pe pozitia %d a fost sters.\n", pozitie);
}

void adaugaLaInceput() {
    struct Flight *nou = (struct Flight*)malloc(sizeof(struct Flight));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }
    printf("Introduceti numarul zborului: ");
    scanf("%d", &nou->number);
    printf("Introduceti destinatia: ");
    scanf("%s", nou->destination);
    printf("Introduceti ora de plecare: ");
    scanf("%s", nou->departureTime);
    printf("Introduceti ora de sosire: ");
    scanf("%s", nou->arrivalTime);
    printf("Introduceti pretul biletului: ");
    scanf("%f", &nou->ticketPrice);

    nou->next = head; // Noul element devine capul listei
    head = nou; // Noua listă începe cu noul element
}

void inverseazaLista() {
    if (head == NULL || head->next == NULL) {
        printf("Lista este goala sau contine un singur element. Nu este necesara inversarea.\n");
        return;
    }

    struct Flight *anterior = NULL;
    struct Flight *curent = head;
    struct Flight *urmator = NULL;

    while (curent != NULL) {
        urmator = curent->next; // Memorează următorul element
        curent->next = anterior; // Schimbă direcția pointerului către elementul anterior
        anterior = curent; // Actualizează pointerul către elementul anterior pentru următoarea iterație
        curent = urmator; // Avansează către următorul element din lista originală
    }

    head = anterior; // Noua "capăt" al listei va fi ultimul element, deoarece lista a fost inversată complet
    printf("Lista a fost inversata cu succes.\n");
}
void curataLista() {
    struct Flight *temp = NULL;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Lista a fost curatata.\n");
}




int main(){
    int optiune, numarCautat, pozitie;

do {
        printf("\tMeniu:\n");
        printf("1) Adauga un element in lista\n");
        printf("2) Afiseaza toata lista\n");
        printf("3) Cauta un element din lista\n");
        printf("4) Elibereaza memoria listei\n");
        printf("5) Sortarea dupa pret\n");
        printf("6) Inserarea la capat\n");
        printf("7) Inserarea la inceput\n");
        printf("8) Inserarea la pozitia X\n");
        printf("9) Stergerea elementului pe pozitia X\n");
        printf("10) Inversarea listei\n");
        printf("11) Curatarea listei\n");
        printf("0) Iesire\n");
        printf("\nAlege o optiune: ");
        scanf("%d", &optiune);

        switch(optiune) {
            case 1:
                adaugaElement();
                break;
            case 2:
                afiseazaLista();
                break;
            case 3:
                printf("Introduceti numarul zborului cautat: ");
                scanf("%d", &numarCautat);
                cautaElement(numarCautat);
                break;
            case 4:
                elibereazaMemorie();
                break;
            case 5:
                sortarePret();
                break;
            case 6:
                adaugaElement();
                break;
            case 7:
                adaugaLaInceput();
                break;
            case 8:
                printf("Introdu pozitia: ");
                scanf("%d", &pozitie);
                insereazaLaPozitie(pozitie);
                break;
            case 9:
                printf("Introdu pozitia: ");
                scanf("%d", &pozitie);
                stergeDeLaPozitie(pozitie-1);
                break;
            case 10:
                inverseazaLista();
                break;
            case 11:
                curataLista();
                break;
            case 0:
                printf("Iesire...\n");
                break;
            default:
                printf("Optiune invalida.\n");
        }
    } while(optiune != 0);

    return 0;
}
