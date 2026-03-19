//
// Created by Usuari on 13/5/2023.
//

#include <stdio.h>
#include "language.h"
#include "network_file_control.h"
#include "network_data_control.h"

/// Escriu totes les dades dels usuaris en un fitxer.
void writeFile(User *user, int users_size, FILE *fp){
    fprintf(fp,"NAME,AGE,E-MAIL,HOME,HOBBY 1,HOBBY 2,HOBBY 3,HOBBY 4,HOBBY 5\n");
    for (int i = 0; i < users_size; ++i) {
        for (int j = 0; j < SIZE_DATA; ++j) {
            fputs(user[i].data[j], fp);
            if (j< HOBBY5)
                fprintf(fp,",");
        }
        if(i<users_size-1)
            fprintf(fp,"\n");
    }
    fclose(fp);
}

// Llegim per caràcters la primera línia, la qual és la dels títols (no la utilitzem).
void Read_Titles_Line(char * buffer, FILE *fp){
    fgets(buffer,BUFFER_SIZE,fp);
}

void Read_Users_Lines(Network *net, char* attribute, FILE *fp){
    User *user = initUser();
    char **data = initStringArray(SIZE_DATA);
    char c;
    // Índexs per a recórrer les dades dels ususaris.
    int idx_user = SET_ZERO;
    int idx_data = SET_ZERO;
    int idx_char = SET_ZERO;
    // Per a solucionar el bug que es produeix quan últimes files buides del fitxer.
    int jump_count = SET_ZERO;

    do{
        c = fgetc(fp);

        // Si el caràcter no és coma, salt de línia o final de fitxer, col·loquem el càracter dins la string auxiliar
        // Incrementem l'índex dels caràcters i ressetegem el comptador de salt.
        if(!(c==',' || c=='\n' || c == EOF)){
            attribute[idx_char] = c;
            idx_char++; jump_count = RESET;
        }

        // Altramentm, després de l'últim caràcter de l'atribut llegit, hi col·loquem l'acabament de string.
        // Copiem l'atribut en una posició de la llista de dades.
        else{
            attribute[idx_char] = '\0';
            data[idx_data] = copyString(attribute);
            idx_data++; idx_char = RESET;

            // Si detectem un salt de línia, hem llegit una fila de dades del fitxer.
            // Amplem la llista d'ususaris i hi copiem les dades; inicialtiztem els altres atributs de l'usuari.
            if (c=='\n' || c==EOF){

                jump_count++;if (jump_count == JUMP_BUG) break;

                user = expandUsers(user, idx_user);
                user[idx_user].data = copyStringArray(data, SIZE_DATA);

                user[idx_user].post = initStringArray(ONE_SIZE);
                user[idx_user].size_posts = SET_ZERO;

                user[idx_user].friend = initStringArray(ONE_SIZE);
                user[idx_user].size_friends = SET_ZERO;

                user[idx_user].request = initStringArray(ONE_SIZE);
                user[idx_user].size_requests = SET_ZERO;

                idx_user++; idx_data = RESET;
            }
        }
    } while (c!=EOF);

    // Copiem la llista d'usuaris a la xarxa.
    net->user = user;
    net->size_users = idx_user;
    net->order_users = NOT_ORDERED;
}

void readUsersFile(Network *net, const char *fileName){
    FILE *fp = fopen(fileName,READING_PLUS_MODE);
    char buffer[BUFFER_SIZE];
    Read_Titles_Line(buffer, fp);
    Read_Users_Lines(net, buffer, fp);
    fclose(fp);
}

void appendUsersFile(User user, const char *fileName){
    FILE *fp = fopen(fileName,APPENDING_MODE);
    fprintf(fp,"\n");
    for (int j = 0; j < SIZE_DATA; ++j) {
        fputs(user.data[j], fp);
        if (j< HOBBY5)
            fprintf(fp,",");
    }
    fclose(fp);
}

