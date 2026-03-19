//
// Created by Usuari on 13/5/2023.
//

#ifndef XARXA_SOCIAL_FILE_CONTROL_H
#define XARXA_SOCIAL_FILE_CONTROL_H

#define JUMP_BUG 2

#define READING_PLUS_MODE "r+"
#define READING_MODE "r"
#define APPENDING_MODE "a"

typedef struct Network Network;
typedef struct User User;

/// Llegim els usuaris del fitxer en mode lectura.
/// Llegim caràcter a caràcter cadascuna de les strings separades per comes i les col·loquem a xarxa social.
void readUsersFile(Network *net, const char *fileName);

/// Afegim un usuari al fitxer d'usuaris.
void appendUsersFile(User user, const char *fileName);

#endif //XARXA_SOCIAL_FILE_CONTROL_H

