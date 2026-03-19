//
// Created by Usuari on 26/4/2023.
//

#include <stdio.h>
#include "option_utils.h"

// Funció que s'encarrega de cancel·lar el bucle que es produiria en el programa 
// si no s'introdueix un enter a la funció read_int. És la funció que supleix a 
// fgetc(stdin), però és més efectiva, ja que esborra més d'un caràcter
// incorrecte.
void flushInput (){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInt(const char* message){
    int num, matched;
    printf("%s",message);

    matched = scanf("%d",&num);

    // Si no és un enter, li demanem a l'usuari que ho repeteixi.
    while (matched == FALSE){
        flushInput();
        printf("Try again!\n");
        printf("%s",message);
        matched = scanf("%d",&num);
    }
    flushInput();
    return num;
}
