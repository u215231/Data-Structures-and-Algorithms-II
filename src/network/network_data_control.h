//
// Created by Usuari on 13/5/2023.
//

#ifndef NETOWRK_DATA_CONTROL_H
#define NETOWRK_DATA_CONTROL_H

#define SIZE_DATA (9)
#define MAX_DICTIONARY_ELEMENTS (10)

#define NAME (0)
#define AGE (1)
#define EMAIL (2)
#define CITY (3)
#define HOBBY1 (4)
#define HOBBY2 (5)
#define HOBBY3 (6)
#define HOBBY4 (7)
#define HOBBY5 (8)

#define NULL_SIZE (0)
#define ONE_SIZE (1)

#define INCREMENT_SIZE (1)
#define DECREMENT_SIZE (-1)
#define MULTIPLICATIVE_FACTOR (5)

#define NOT_ORDERED (-1)

#define BUFFER_SIZE (1024)
#define END_CHARACTER (1)

#define RESET 0
#define SET_ZERO 0

#define LESSTHAN (-1)
#define GREATERTHAN 1
#define EQUAL 0

#define ACCEPT (1)
#define DENY (0)

#define MAX_RANDOM_USERS (3)

#define FIRST (0) // Primer usuari d'una llista.

typedef struct RandomUsers RandomUsers;
typedef struct Element Element;
typedef struct Dict Dict;
typedef struct User User;
typedef struct Network Network;

struct RandomUsers {
    // Pila de tres usuaris aleatoris.
    int stack[MAX_RANDOM_USERS];
    // Mida actual de la pila.
    int top;
};

/// Estructura del diccionari.

struct Element{
    // Paraules dels posts dels ususaris.
    char* key;
    // Quantitat de repeticions
    int value;
};

struct Dict{
    // Elements del diccionari.
    Element* element;
    // Elements actuals del diccionari (com a màxim en poden ser 10).
    int current_elements;
    // Mida real del diccionari.
    int size_elements;
};

/// Estructura dels usuaris.

struct User{
    // Les seves dades: nom, edat, email, etc.
    char** data;

    // Les sol·licituds d'amistat rebudes per part d'altres usuaris.
    char** request;
    int size_requests;

    // Els amics de l'usuari.
    char** friend;
    int size_friends;

    // Les seves publicacions (textos).
    char** post;
    int size_posts;
};

/// Estructura de la xarxa.

struct Network {
    // Array dinàmica d'usuaris.
    User* user;
    int size_users;
    int order_users;

    // Usuaris banejats (s'hi conté el seu nom).
    char **banned_user;
    int size_banned_users;

    // Diccionari per a comptar les paraules més utilitzades.
    Dict* dictionary;
};

/// Inicialització de dades de la Xarxa.

char* initString (int size);
char** initStringArray (int size);
User* initUser();
Dict* initDictionary();
Network* initNetwork ();

/// Expansió de dades.

Dict* expandElements (Dict *dict, int current_size);
User * expandUsers (User *user, int current_size);
char ** expandStringArray (char** stringArray, int current_size);

/// Eliminació de dades concretes de llistes.

void delete_String_In_StringArray(char **string_array, int position_to_delete, int current_size);

/// Neteja de dades de la xarxa.

void clearUsers (User *user, int users_size);
void clearNetwork (Network *network);

/// Còpia de dades.

char* copyString (char *origin);
char** copyStringArray (char **origin, int size);
void copyUser (User* copy, User* origin);

/// Lectura de dades.

char* readString();

/// Funcions específiques de cua.

RandomUsers* initRandomUsers ();
void pushRandomUser (RandomUsers* random_users, int random_user_idx);
void popRandomUser (RandomUsers* random_users);
int topRandomUser (RandomUsers* random_users);

#endif //NETOWRK_DATA_CONTROL_H