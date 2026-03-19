//
// Created by Usuari on 27/4/2023.
//

#ifndef XARXA_SOCIAL_SEARCH_UTILS_H
#define XARXA_SOCIAL_SEARCH_UTILS_H

#define USER_NOT_FOUND (-1)
#define STRING_NOT_FOUND (-1)

typedef struct Network Network;

int searchInIntArray(int integer, int *array, int array_size);
int searchInStringArray(char *String, char **StringArray, int ArraySize);

// Ens busca binàriament un usuari a la llista d'usuaris.
int searchNetwork(char *attribute, Network *net, int type);

#endif //XARXA_SOCIAL_SEARCH_UTILS_H
