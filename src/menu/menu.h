//
// Created by Usuari on 26/4/2023.
//

// MARC BOSCH MANZANO

#ifndef XARXA_SOCIAL_0_MENU_H
#define XARXA_SOCIAL_0_MENU_H

#define OPTION_NEW_USER (1)
#define OPTION_LIST_USERS (2)
#define OPTION_OPERATE_USER (3)
#define OPTION_QUIT (0)

typedef struct Network Network;

// Menú principal del programa. 
//      a) Nou usuari
//      b) Llista d'usuaris
//      c) Operar amb l'usuari
//      d) Sortir
//
// Tenim tres opcions al menú: afegir un nou usuari, enllistar tots els 
// usuaris o operar amb un d'ells.
//
void showMenu(Network *net);

#endif //XARXA_SOCIAL_0_MENU_H
