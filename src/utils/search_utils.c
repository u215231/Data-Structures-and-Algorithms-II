//
// Created by Usuari on 27/4/2023.
//

#include <string.h>
#include "search_utils.h"
#include "sort_utils.h"
#include "network_data_control.h"
#include "option_utils.h"

// Funció que retorna TRUE quan l'atribut és més gran que el primer de la llista o quan és
// més petit que l'últim usuari i FALSE en cas contrari. Si un usuari està fitat, hi ha probabilitat que pugui estar a la llista.
int fencedAttribute (char* attribute, User* user, int size, int type){

    int first = 0;
    int last = size-1;

    int lowBound = strcmp(user[first].data[type], attribute);
    int highBound = strcmp(user[last].data[type], attribute);

    return LESSTHAN <= lowBound && highBound<= GREATERTHAN;
}

// Ens arriba una llista ordenada d'usuaris segons un tipus de dada (NAME, AGE, EMAIL, etc.).
// Ens retorna l'índex de l'usuari dins la llista en cas de ser trobat o un error en cas contrari.
int binarySearch (char* attribute_to_search, User *user, int size, int type){

    int left, right, mid, comparsion;
    left = FIRST;
    right = size-1;

    // Mentre els índexs no es creuin, fem comparació entre l'atribut a cercar i un atribut de la llista.
    while (left<=right) {

        mid = (left+right)/2;
        comparsion = strcmp(attribute_to_search, user[mid].data[type]);

        // L'atribut a cercar pot estar en la part superior de la llsita.
        if (comparsion == GREATERTHAN) {
            left = mid + 1;
        }
        // L'atribut pot estar a la superior de la llsita.
        else if (comparsion == LESSTHAN) {
            right = mid - 1;
        }
        // Hem trobat l'atribut a cercar.
        else {
            return mid;
        }
    }

    // No hem trobat l'atribut en cap moment.
    return USER_NOT_FOUND;
}


// La funció ordena la llista segons el tipus de dada escollida.
// Verifiquem que estigui fitat dins la llista i iniciem la cerca binària de l'atribut.
int searchNetwork(char* attribute_to_search, Network *net, int type){
    sortNetwork(net, type);

    User *user = net->user;
    int size = net->size_users;

    if (size > NULL_SIZE){
        if(fencedAttribute (attribute_to_search, user, size, type) == TRUE){
            return binarySearch (attribute_to_search, user, size, type);
        }
    }
    return USER_NOT_FOUND;
}

// Funció de cerca lineal. Suposem que la quanitat d'usuaris banejats no serà excessivament gran.
int searchInStringArray(char* String, char** StringArray, int ArraySize) {

    for (int idx = 0; idx < ArraySize; idx++)

        // Retornem l'índex d'aquell usuari banejat dins l'estructura dels banejats si el troba.
        if (strcmp(StringArray[idx], String) == 0)
            return idx;

    // Constant retornada de (-1) si no hem trobat l'usuari banejat.
    return STRING_NOT_FOUND;
}

// Funció de cerca lineal.
int searchInIntArray (int integer, int *array, int array_size){
    for (int i=0; i<array_size; i++){
        if(integer == array[i]){
            return TRUE;
        }
    }
    return FALSE;
}