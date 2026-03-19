//
// Created by Usuari on 14/6/2023.
//

#include <stdio.h>
#include <string.h>
#include "print_utils.h"
#include "network_data_control.h"
#include "network_file_control.h"

// Ens imprimeix una llista de cadenes.
// Who pot ser "You" o "Friend" i StringType pot ser "request", "post" o "friend".
void listStringArray (char **StringArray, int SizeArray, char *Who, char *StringType) {

    if (SizeArray == NULL_SIZE) {
        printf("\n%s don't have any %s!\n",Who,StringType);
        return;
    }
    if (SizeArray == ONE_SIZE){
        printf("%s have 1 %s.\n", Who, StringType);
    }
    else{
        printf("%s have %d %ss.\n", Who, SizeArray, StringType);
    }

    for (int i = 0; i < SizeArray; i++) {
        printf("%d. %s\n", i+1, StringArray[i]);
    }
}

/// Imprimir espais.
void printSpaces (char previous_string[], int max_length){
    int spaces = max_length - strlen(previous_string);
    for (int j = 0; j < spaces; ++j) {
        printf(" ");
    }
}

