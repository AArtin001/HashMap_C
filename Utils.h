#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALABRA 256

typedef struct {
    long palabras;
    long espacios;
    long signos;
} t_stats;



void menu();

#endif // UTILS_H
