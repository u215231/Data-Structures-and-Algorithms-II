//
// Created by Usuari on 26/4/2023.
//

#ifndef XARXA_SOCIAL_SORT_UTILS_H
#define XARXA_SOCIAL_SORT_UTILS_H

typedef struct Dict Dict;
typedef struct Network Network;

// Funció que ordena els usuaris si hi ha més d'un usuari i si el tipus d'atribut que volem ordenar no està ordenat.
// Ens ordena ascendentment una llista d'usuaris a partir de l'ordenació combinada i recursiva (merge sort).
void sortNetwork(Network *net, int type);
void selectiveSort(Dict *dictionary);

#endif //XARXA_SOCIAL_SORT_UTILS_H

