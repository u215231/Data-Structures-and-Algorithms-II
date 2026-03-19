//
// Created by Usuari on 13/5/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_users.h"
#include "network_data_control.h"
#include "print_utils.h"

void createArrayHeader(char header[TITLES][MAX_LENGTH]){
    strcpy(header[NAME], "NAME");
    strcpy(header[AGE], "AGE");
    strcpy(header[EMAIL], "E-MAIL");
    strcpy(header[CITY], "CITY");
    strcpy(header[HOBBY1], "HOBBIES");
}

// De cada columna d'atributs de dades, mirem quina és l'string que té longitud
// màxima i retornem aquest valor.
int maxAttributesLengths(const User *user, int size, int type) {
    int max = 0;
    int length;
    for (int i = 0; i < size; ++i) {
        length = strlen(user[i].data[type]);
        if(max < length)
            max = length;
    }
    return max;
}

int *getMaxAttributesLengthArray(
    const Network* net, 
    int max_attributes_lengths[], 
    char header[][MAX_LENGTH]
){
    const User *user = net->user;
    const int size_users = net->size_users;
    for (int i = 0; i < SIZE_DATA; ++i) {
        max_attributes_lengths[i] = maxAttributesLengths(user, size_users, i);
        if (i<TITLES){
            int length = strlen(header[i]);
            if (length > max_attributes_lengths[i] ){
                max_attributes_lengths[i] = length;
            }
        }
    }
    return max_attributes_lengths;
}

// Imprimim la capçalera d'atributs de la taula d'usuaris.
void printHeader(char header[][MAX_LENGTH], int *max_attributes_lengths){
    for(int i = 0; i < TITLES; i++){
        printf("%s ",header[i]);
        printSpaces (header[i], max_attributes_lengths[i]);
    }
    printf("\n");
}

// Impressió de cada atribut d'un usuari.
// Per a NAME, AGE, EMAIL I CITY, imiprimim l'atribut i omplim amb espais 
// proporcionals. Per als 4 primers hobbies, els imprimim separant-los amb 
// punt i coma. Per a l'últim hobby, l'imprimim amb un caràcter de salt de 
// línia.
void printUser(const User *user, int *max_attributes_lengths){
    for (int i = 0; i < SIZE_DATA; ++i) {
        if (i < HOBBY1) {
            printf("%s ", user->data[i]);
            printSpaces(user->data[i], max_attributes_lengths[i]);
        }
        else if (i <= HOBBY4){
            printf("%s; ", user->data[i]);
        }
        else {
            printf("%s\n", user->data[i]);
        }
    }
}

void listUsers(const Network *net){
    const User *users = net->user;
    const int size_users = net->size_users;

    printf("\nRegistered users: %d\n\n", size_users);

    char header[TITLES][MAX_LENGTH];
    createArrayHeader(header);

    int max_attributes_lengths[SIZE_DATA];
    getMaxAttributesLengthArray(net, max_attributes_lengths, header);

    printHeader(header, max_attributes_lengths);
    for(int i = 0; i < size_users; i++) {
        printUser(&users[i], max_attributes_lengths);
    }

    char c;
    printf("Press ENTER to continue...");
    scanf("%c", &c);
}