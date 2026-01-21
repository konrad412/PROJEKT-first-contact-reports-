#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DINO 100
#define MAX_STR 100

typedef struct {
    char gatunek[MAX_STR];
    char dieta[MAX_STR];
    float masa;
    char zagroda[MAX_STR];
    char temperament[MAX_STR];
    char status[MAX_STR];
} Dinozaur;

Dinozaur baza[MAX_DINO];
int liczba = 0;

void czyscBufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void wczytajLinie(char *bufor, int rozmiar) {
    fgets(bufor, rozmiar, stdin);
    bufor[strcspn(bufor, "\n")] = 0;
}

void dodajDinozaura() {
    if (liczba >= MAX_DINO) {
        printf("Brak miejsca w bazie!\n");
        return;
    }

    Dinozaur d;

    printf("Gatunek: ");
    wczytajLinie(d.gatunek, MAX_STR);

    printf("Zagroda (numer): ");
    wczytajLinie(d.zagroda, MAX_STR);

    for (int i = 0; i < liczba; i++) {
        if (strcmp(baza[i].gatunek, d.gatunek) == 0 &&
            strcmp(baza[i].zagroda, d.zagroda) == 0) {
            printf("Taki dinozaur juz istnieje!\n");
            return;
        }
    }

    printf("Dieta (miesozerny/roslinozerny/wszystkozerny): ");
    wczytajLinie(d.dieta, MAX_STR);

    printf("Masa (kg): ");
    scanf("%f", &d.masa);
    czyscBufor();

    printf("Temperament (spokojny, reaktywny, agresywny, nieprzewidywalny): ");
    wczytajLinie(d.temperament, MAX_STR);

    printf("Status bezpieczenstwa (bezpieczny, pod obserwacja, zagrozenie, ucieczka, awaryjna kwarantanna): ");
    wczytajLinie(d.status, MAX_STR);

    baza[liczba++] = d;
    printf("Dinozaur dodany pomyslnie.\n");
}

void wyswietlDinozaura(Dinozaur d) {
    printf("\nGatunek: %s\n", d.gatunek);
    printf("Dieta: %s\n", d.dieta);
    printf("Masa: %.2f kg\n", d.masa);
    printf("Zagroda: %s\n", d.zagroda);
    printf("Temperament: %s\n", d.temperament);
    printf("Status: %s\n", d.status);
}

void wyszukajDinozaura() {
    char gatunek[MAX_STR], zagroda[MAX_STR];

    printf("Podaj gatunek: ");
    wczytajLinie(gatunek, MAX_STR);

    printf("Podaj zagrode: ");
    wczytajLinie(zagroda, MAX_STR);

    for (int i = 0; i < liczba; i++) {
        if (strcmp(baza[i].gatunek, gatunek) == 0 &&
            strcmp(baza[i].zagroda, zagroda) == 0) {
            wyswietlDinozaura(baza[i]);
            return;
        }
    }
    printf("Nie znaleziono dinozaura.\n");
}

void modyfikujDinozaura() {
    char gatunek[MAX_STR], zagroda[MAX_STR];

    printf("Podaj gatunek: ");
    wczytajLinie(gatunek, MAX_STR);

    printf("Podaj zagrode: ");
    wczytajLinie(zagroda, MAX_STR);

    for (int i = 0; i < liczba; i++) {
        if (strcmp(baza[i].gatunek, gatunek) == 0 &&
            strcmp(baza[i].zagroda, zagroda) == 0) {

            printf("Nowa dieta(miesozerny/roslinozerny/wszystkozerny): ");
            wczytajLinie(baza[i].dieta, MAX_STR);

            printf("Nowa masa(kg): ");
            scanf("%f", &baza[i].masa);
            czyscBufor();

            printf("Nowy temperament(spokojny, reaktywny, agresywny, nieprzewidywalny): ");
            wczytajLinie(baza[i].temperament, MAX_STR);

            printf("Nowy status(bezpieczny, pod obserwacja, zagrozenie, ucieczka, awaryjna kwarantanna): ");
            wczytajLinie(baza[i].status, MAX_STR);

            printf("Dane zmodyfikowane.\n");
            return;
        }
    }
    printf("Nie znaleziono dinozaura.\n");
}

void usunDinozaura() {
    char gatunek[MAX_STR], zagroda[MAX_STR];

    printf("Podaj gatunek: ");
    wczytajLinie(gatunek, MAX_STR);

    printf("Podaj zagrode: ");
    wczytajLinie(zagroda, MAX_STR);

    for (int i = 0; i < liczba; i++) {
        if (strcmp(baza[i].gatunek, gatunek) == 0 &&
            strcmp(baza[i].zagroda, zagroda) == 0) {

            if (strcmp(baza[i].status, "zagrozenie") == 0 ||
                strcmp(baza[i].status, "ucieczka") == 0) {
                printf("Nie mozna usunac dinozaura — status krytyczny!\n");
                return;
            }

            for (int j = i; j < liczba - 1; j++) {
                baza[j] = baza[j + 1];
            }
            liczba--;
            printf("Dinozaur usuniety.\n");
            return;
        }
    }
    printf("Nie znaleziono dinozaura.\n");
}

void sortujPoMasie() {
    for (int i = 0; i < liczba - 1; i++) {
        for (int j = 0; j < liczba - i - 1; j++) {
            if (baza[j].masa > baza[j + 1].masa) {
                Dinozaur tmp = baza[j];
                baza[j] = baza[j + 1];
                baza[j + 1] = tmp;
            }
        }
    }
    printf("Posortowano po masie.\n");
}

void zapiszDoPliku() {
    FILE *f = fopen("dinozaury.txt", "w");
    if (!f) {
        printf("Blad zapisu do pliku.\n");
        return;
    }

        fprintf(f, "%d\n", liczba);
    for (int i = 0; i < liczba; i++) {
        fprintf(f, "%s\n%s\n%f\n%s\n%s\n%s\n",
                baza[i].gatunek,
                baza[i].dieta,
                baza[i].masa,
                baza[i].zagroda,
                baza[i].temperament,
                baza[i].status);
    }
    fclose(f);
    printf("Zapisano do pliku.\n");
}

void wczytajZPliku() {
    FILE *f = fopen("dinozaury.txt", "r");
    if (!f) {
        printf("Brak pliku do odczytu.\n");
        return;
    }

    fscanf(f, "%d\n", &liczba);
    for (int i = 0; i < liczba; i++) {
        fgets(baza[i].gatunek, MAX_STR, f);
        fgets(baza[i].dieta, MAX_STR, f);
        fscanf(f, "%f\n", &baza[i].masa);
        fgets(baza[i].zagroda, MAX_STR, f);
        fgets(baza[i].temperament, MAX_STR, f);
        fgets(baza[i].status, MAX_STR, f);

        baza[i].gatunek[strcspn(baza[i].gatunek, "\n")] = 0;
        baza[i].dieta[strcspn(baza[i].dieta, "\n")] = 0;
        baza[i].zagroda[strcspn(baza[i].zagroda, "\n")] = 0;
        baza[i].temperament[strcspn(baza[i].temperament, "\n")] = 0;
        baza[i].status[strcspn(baza[i].status, "\n")] = 0;
    }
    fclose(f);
    printf("Dane wczytane z pliku.\n");
}

int main() {
    int wybor;

    do {
        printf("\n--- PARK DINOZAUROW ---\n");
        printf("1. Dodaj dinozaura\n");
        printf("2. Wyszukaj dinozaura\n");
        printf("3. Modyfikuj dinozaura\n");
        printf("4. Usun dinozaura\n");
        printf("5. Sortuj po masie\n");
        printf("6. Zapisz do pliku\n");
        printf("7. Wczytaj z pliku\n");
        printf("0. Wyjscie\n");
        printf("Wybor: ");
        scanf("%d", &wybor);
        czyscBufor();

        switch (wybor) {
            case 1: dodajDinozaura(); break;
            case 2: wyszukajDinozaura(); break;
            case 3: modyfikujDinozaura(); break;
            case 4: usunDinozaura(); break;
            case 5: sortujPoMasie(); break;
            case 6: zapiszDoPliku(); break;
            case 7: wczytajZPliku(); break;
            case 0: printf("Zamykanie systemu...\n"); break;
            default: printf("Nieprawidlowy wybor.\n");
        }
    } while (wybor != 0);

    return 0;
}