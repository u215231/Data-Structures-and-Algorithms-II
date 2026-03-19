//
// Created by Usuari on 13/5/2023.
//

#ifndef XARXA_SOCIAL_LIST_USERS_H
#define XARXA_SOCIAL_LIST_USERS_H

#define MAX_LENGTH 10
#define TITLES 5

typedef struct Network Network;

/// Imprimeix tots els usuaris que hi ha inscrits.
void listUsers(const Network *net);

#endif //XARXA_SOCIAL_LIST_USERS_H