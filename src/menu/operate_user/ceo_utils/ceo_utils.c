#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "language.h"
#include "ceo_utils.h"
#include "dictionary_utils.h"
#include "network_data_control.h"
#include "network_file_control.h"
#include "search_utils.h"
#include "sort_utils.h"
#include "option_utils.h"

void unbanUser(Network *net){

    // Mida de l'estructura dels usuaris banejats.
    int size = net->size_banned_users;

    // Triem l'usuari a desbanejar pel seu nom. Mirem que existeixi a la llista.
    printf("\nWhich user do you want to unban?\n");
    char *name = readString();

    int banned_idx = searchInStringArray (name, net->banned_user, size);

    if (banned_idx == STRING_NOT_FOUND){
        printf("\nThis user is not banned!\n");
        return;
    }

    // En cas de trobar l'usuari banejat, ens el borra de la llista dels banejats.
    delete_String_In_StringArray(net->banned_user, banned_idx, size);
    net->size_banned_users += DECREMENT_SIZE;

    printf("Now, this user is not banned from ZhiYuMarc Network.\n");
}

void banUser(Network *net){

    // Triem l'usuari a banejar pel seu nom. Mirem que existeixi a la llista.
    printf("\nWhich user do you want to ban?\n");
    char *name = readString();

    if (searchNetwork (name, net, NAME) == USER_NOT_FOUND){
        printf("\nThe user was not found!\n");
        return;
    }

    int last = net->size_banned_users;

    // Expandim la llista d'strings dels usuaris banejats.
    net->banned_user = expandStringArray(net->banned_user, last);
    net->size_banned_users += INCREMENT_SIZE;

    // Afegim aquest nou usuari banejat a l'última posició. Només ens cal anotar el seu nom.
    net->banned_user[last] = name;

    printf("\n%s has been banned from the Social Network!\n", name);
}

int isBanned(const Network *net, int user_idx) {
    return (
        searchInStringArray(
            net->user[user_idx].data[NAME], 
            net->banned_user, 
            net->size_banned_users
        ) != STRING_NOT_FOUND
    );
}

// Imprimim el fitxer amb els Termes i d'Ús de la xarxa.
void printIsBannedMessage() {
    printf("\nYour account has been disabled for violating our terms.\n");
    printf("Learn how you may be able to restore your account entering\n");
    printf("in our Social Network Terms of Use.\n");

    int option = readInt("If you want to see our Terms of Use, click 1.\n");

    if (option != SEE_TERMS_OF_USE)
        return;

    FILE *fp = fopen(CONDITION_TERMS_PATH, READING_MODE);

    printf("%d",fp == NULL);
    char c;
    do{
        c = fgetc(fp);
        printf("%c",c);
    } while (c != EOF);

    printf("\n");
    fclose(fp);

    printf("Press ENTER to continue...");
    scanf("%c", &c);
}

void listBannedUsers(const Network *net){
    char **banned_user = net->banned_user; 
    int size = net->size_banned_users;
    printf("\nThese are the banned users:\n");
    for (int i = 0; i < size; i++)
        printf("%d. %s\n", i+1, banned_user[i]);
}

void getMostUsedWords(Network *net) {
    net->dictionary->element[0].value = 0;
    selectiveSort(net->dictionary);
    printDictionaryElements(net->dictionary);
}

void ceoMenu(Network *net){
    int option;
    do {
        printf("\n===== DEVELOPER MENU =====\n\n");

        printf("%d. Search 10 most used words.\n", OPTION_MOST_USED_WORDS);
        printf("%d. Ban user.\n", OPTION_BAN_USER);
        printf("%d. Unban user.\n",OPTION_UNBAN_USER);
        printf("%d. List banned users.\n",OPTION_LIST_BANNED);
        printf("%d. Return to principal menu.\n",OPTION_RETURN_MENU);

        option = readInt("Choose your option:\n");

        system("cls");

        switch (option) {
            case OPTION_MOST_USED_WORDS: getMostUsedWords(net); break;
            case OPTION_BAN_USER: banUser(net); break;
            case OPTION_UNBAN_USER: unbanUser(net); break;
            case OPTION_LIST_BANNED: listBannedUsers(net); break;
            case OPTION_RETURN_MENU: break;
            default: printf("\nInvalid option!\n"); break;
        }
    } while(option != OPTION_RETURN_MENU);
}


