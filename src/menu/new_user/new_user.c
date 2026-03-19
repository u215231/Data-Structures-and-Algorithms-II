//
// Created by Usuari on 13/5/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "language.h"
#include "new_user.h"
#include "network_data_control.h"
#include "network_file_control.h"
#include "option_utils.h"
#include "search_utils.h"

int checkIsEmpty (char* attribute){
    return strlen(attribute) == NULL_SIZE;
}

/// Comprova que un atribut no estigui a la llista d'usuaris. 3 != (-1), llavors exiteix l'usuari.
int checkIsFound (char* attribute, Network *net, int type){
    return searchNetwork(attribute, net, type) != USER_NOT_FOUND;
}

/// D'un correu donat, mira d'extreure la part del domini, si exiteix.
char *createDomain(char *email) {
    char* user_domain = malloc(DOMAIN_LENGHT*sizeof(char));
    char c;

    // Copia els caràcters del final de l'email a una string nova fins que troba un punt.
    int idx_email = strlen(email)-1;
    int idx_array = 0;
    while (idx_email>= 0 && email[idx_email] != '.'){
        user_domain[idx_array] = email[idx_email];
        idx_array++;
        idx_email--;
    }

    // Reverteix els caràcters copiats.
    for (int i = 0; i<idx_array/2; i++) {
        c = user_domain[i];
        user_domain[i] = user_domain[idx_array-i-1];
        user_domain[idx_array-i-1] = c;
    }

    // Caràcter aturador d'string.
    user_domain[idx_array] = '\0';
    return user_domain;
}

/// Comprova si el domini del correu pertany a la llista de dominis.
int checkDomain(char* email) {
    FILE *fp = fopen(DOMAINS_PATH, READING_MODE);

    char* file_domain = malloc(DOMAIN_LENGHT*sizeof(char));
    char* user_domain = createDomain(email);

    while (fscanf(fp, "%s", file_domain) > 0)
        if (strcmp(user_domain, file_domain) == 0)
            return TRUE;
    return FALSE;
}

/// Comprova que un correu tingui arroba.
int checkArroba(char* email) {
    for (int i = 0; (size_t)i < strlen(email); i++)
        if (email[i] == '@')
            return TRUE;
    return FALSE;
}

/// Funció per a la validació del correu de l'usuari.
int readEmail(char *email, Network *net, int type) {

    int isArroba = checkArroba(email);
    if (isArroba == FALSE) printf("E-mail without arroba!\n");

    int isDomain = checkDomain(email);
    if (isDomain == FALSE) printf("Invalid domain!\n");

    int isFound = checkIsFound(email, net, type);
    if (isFound == TRUE) printf("Already registered e-mail!\n");

    return isArroba && isDomain && !(isFound);
}

/// Funció per a la validació del nom de l'usuari.
int readName(char *name, Network *net, int type){

    if (checkIsEmpty (name)){
        printf("The name must not be empty!\n");
        return FALSE;
    }

    if (checkIsFound(name,net,type)){
        printf("Already registered name!\n");
        return FALSE;
    }
    return TRUE;
}

/// Validació de l'edat de l'usuari.
int readAge (char *age) {

    if (checkIsEmpty (age)){
        printf("The age must have a value!\n");
        return FALSE;
    }

    // Valida que l'edat sigui numèrica.
    int i = 0;
    while (age[i] != '\0'){
        if ('0' > age[i] || '9' < age[i]) {
            printf("Invalid age!\n");
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

/// Validació de la residència de l'usuari.
int readCity (char *city) {

    if (checkIsEmpty (city)) {
        printf("The city must not be empty\n!");
        return FALSE;
    }
    return TRUE;
}

/// Validació del nom, l'edat, l'email i el lloc on viu de l'usuari (els hobbies els considerem opcionals).
int checkAttribute (Network *net, char *attribute, int type) {

    switch (type) {
        case NAME:
            // No ha de ser buit i no ha d'estar a la llista d'usuaris.
            return readName (attribute, net, type);
        case AGE:
            // No ha d'estar buit i ha de ser numèric.
            return readAge (attribute);
        case EMAIL:
            // Ha de tenir @, domini vàlid i no ha d'estar a la llista.
            return readEmail (attribute,net,type);
        case CITY:
            // No ha d'estar buit.
            return readCity (attribute);
    }
    return TRUE;
}


/// Impressió de missatges per a l'entrada de valors.
void printInputMessages(int type){

    printf("Introduce your ");

    int num_hobby = type - HOBBY1;
    if (type > HOBBY1)
        type = HOBBY1;

    switch(type){
        case NAME: printf("name:"); break;
        case AGE: printf("age:"); break;
        case EMAIL: printf("e-mail:"); break;
        case CITY:  printf("city:"); break;
        case HOBBY1: printf("hobby %d:", num_hobby+1);
    }
}

/// Lectura per consola dels atributs validats de l'usuari.
char** readUserData (Network net){

    char** data = initStringArray (SIZE_DATA);
    char* attribute;

    // Col·loquem els atributs llegits dins d'una stack d'strings.
    for (int i = 0; i < SIZE_DATA; ++i) {
        do{
            printInputMessages(i);
            attribute = readString();

        } while (checkAttribute(&net, attribute, i) == FALSE);

        data[i] = copyString(attribute);
    }

    free(attribute);

    return data;
}


/// Funció que crea un nou usuari i li afegeix dades entrades per consola.
void newUser(Network *net){

    int last = net->size_users;

    // Expandeix la llista d'usuaris i afegeix les noves dades per a l'últim usuari.
    net->user = expandUsers (net->user,last);

    net->user[last].data = readUserData(*net);

    // Inicialitzem la resta d'estructures associades a l'usuari.
    net->user[last].post = initStringArray(ONE_SIZE);
    net->user[last].size_posts = SET_ZERO;

    net->user[last].friend = initStringArray(ONE_SIZE);
    net->user[last].size_friends = SET_ZERO;

    net->user[last].request = initStringArray(ONE_SIZE);
    net->user[last].size_requests = SET_ZERO;

    appendUsersFile(net->user[last], USERS_PATH);

    net->size_users += INCREMENT_SIZE;
    net->order_users = NOT_ORDERED;
}