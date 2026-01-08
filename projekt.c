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