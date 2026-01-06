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