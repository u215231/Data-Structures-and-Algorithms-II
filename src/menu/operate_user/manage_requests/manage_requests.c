//
// Created by Usuari on 28/5/2023.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manage_requests.h"
#include "network_data_control.h"
#include "search_utils.h"
#include "option_utils.h"
#include "print_utils.h"

/// Funcions per a afegir o eliminar element en una cua de sol·licituds d'un usuari.

void enqueueRequest (Network* net, char* operating_user_name, int idx_requested_user) {

    // Mida de les sol·licituds de l'usuari a sol·licitar amistat.
    int size_requests = net->user[idx_requested_user].size_requests;
    // Llista de les seves sol·licituds.
    char **request = net->user[idx_requested_user].request;

    // Expansió de memòria de les sol·liciuds.
    net->user[idx_requested_user].request = expandStringArray (request, size_requests);

    // Afegim l'usuari operant com a nou sol·licitador d'amistat.
    net->user[idx_requested_user].request[size_requests] = copyString(operating_user_name);
    net->user[idx_requested_user].size_requests += INCREMENT_SIZE;
}

void dequeueRequest (User * operating_user){
    // Esborrem la primera sol·licitud, ja que és una cua.
    delete_String_In_StringArray(operating_user->request, operating_user->size_requests, FIRST);
    operating_user->size_requests += DECREMENT_SIZE;
}


/// Funció dedicada a enviar una sol·licitud d'amistat a un usuari que volguem.

void sendChoosedUserRequest (Network *net, int idx_operating_user){

    // Mida de la llista dels amics de l'usuari operant.
    int size_friends = net->user[idx_operating_user].size_friends;

    // Llista dels seus amics.
    char **friend = net->user[idx_operating_user].friend;

    // El nom de l'usuari operant.
    char *operating_user_name = net->user[idx_operating_user].data[NAME];

    // Demanem a l'usuari operant que ens esculli un usuari a enviar sol·licitud.
    printf("\nIntroduce the name of the user that you want to send a friend request.\n");
    char *requested_user_name = readString();

    // Condicions per enviar la sol·licitud:

    // 1) Mirem que no coindeixi aquest nom d'usuari a sol·licitar amistat amb el teu propi nom.
    if (strcmp(requested_user_name, operating_user_name) == EQUAL) {
        printf("You can't send friend request to yourself!\n");
        return;
    }

    // 2) Mirem que l'usuari a sol·licitar no estigui a la llista d'amics de l'usuari operant. Fem una cerca seqüencial.
    if(searchInStringArray (requested_user_name, friend, size_friends) != STRING_NOT_FOUND){
        printf("%s and you are already friends!\n", requested_user_name);
        return;
    }

    // 3) Mirem que l'usuari no estigui banejat.
    if(searchInStringArray (requested_user_name, net->banned_user, net->size_banned_users) != STRING_NOT_FOUND){
        printf("The user %s is banned.",requested_user_name);
    }

    // 4) Mirem que aquest usuari existeixi a la llista d'usuaris.
    int idx_requested_user = searchNetwork(requested_user_name, net, NAME);

    if (idx_requested_user == USER_NOT_FOUND) {
        printf("\nThe user was not found!\n");
        return;
    }

    // 5) Si tot és correcte, li enviem la sol·licitud a l'usuari a sol·licitar amistat.
    enqueueRequest(net, operating_user_name, idx_requested_user);

    printf("You have send a friend request to %s successfully.\n", requested_user_name);
}





/// Funcions dedicades a enviar sol·licituds a tres usuaris aleatoris.

// Funció que comprova si hi ha suficients usuaris per a enviar-los sol·licitud d'amistat.
// Si tenim masses amics, podrem remetre menys sol·licituds.
int maxRandomUsersRequests (int size_users, int size_friends){
    int friends_proportion = size_users - (size_friends+1);
    if (MAX_RANDOM_USERS < friends_proportion){
        return MAX_RANDOM_USERS;
    }
    return friends_proportion;
}


RandomUsers* fullRandomUsers (Network* net, int idx_operating_user, int max_stack) {

    RandomUsers* random_users = initRandomUsers();

    // Mida de la llista dels amics de l'usuari operant.
    int size_friends = net->user[idx_operating_user].size_friends;

    // Llista dels seus amics.
    char **friend = net->user[idx_operating_user].friend;

    // El nostre nom.
    char *operating_user_name = net->user[idx_operating_user].data[NAME];

    int isItself, isFriend, isBanned, isInStack;
    int idx_random_user; char *random_user_name;

    for (int i = 0; i<max_stack; i++) {

        do {
            // Obtenció d'un índex aleatori d'un usuari i el seu nom.
            idx_random_user = (rand()%net->size_users);
            random_user_name = net->user[idx_random_user].data[NAME];

            // 1) Comprovació que l'usuari no sigui ell mateix.
            isItself = strcmp(random_user_name, operating_user_name) == EQUAL;

            // 2) Comprovació que l'usuari no sigui ja un amic.
            isFriend = searchInStringArray(random_user_name, friend, size_friends) != STRING_NOT_FOUND;

            // 3) Comprovació que no estigui banejat.
            isBanned = searchInStringArray(random_user_name, net->banned_user, net->size_banned_users) != STRING_NOT_FOUND;

            // 4) Comprovació que no hagi sortit ja com aleatori.
            isInStack = searchInIntArray (idx_random_user, random_users->stack, random_users->top);

        } while (isItself && isFriend && isBanned && isInStack);

        // Col·loquem l'usuari a la pila.
        pushRandomUser (random_users, idx_random_user);
    }
    return random_users;
}

// Funció que implementa una pila i simula Tinder.
void sendRandomUsersRequest (Network* net, int idx_operating_user) {

    // Mida de la llista dels amics de l'usuari operant.
    int size_friends = net->user[idx_operating_user].size_friends;

    // El nom de l'usuari operant.
    char *operating_user_name = net->user[idx_operating_user].data[NAME];

    // Podem afegir entre 3 i 0 nous usuaris aleatoris, depenent de la quantitat d'amics que tingui l'operant.
    int max_stack = maxRandomUsersRequests(net->size_users, size_friends);

    printf("\nWe are going to select %d random users to send a request.\n",max_stack);
    printf("[1 for YES, 0 for NO]\n");

    // Pila amb els usuaris aleatoris a enviar sol·licitud.
    RandomUsers* random_users = fullRandomUsers (net, idx_operating_user, max_stack);

    for (int i = 0; i < max_stack; ++i) {

        int idx_requested_user = topRandomUser(random_users);
        char *requested_user_name = net->user[idx_requested_user].data[NAME];

        printf("\n%d. Send a request to user %s?", i+1, requested_user_name);
        int option = readInt("\n");

        // Cas on acceptem d'enviar-li sol·licitud a l'usuari a sol·licitar.
        if (option == ACCEPT){
            enqueueRequest (net, operating_user_name, idx_requested_user);
            printf("Request sent to %s successfully.\n",  requested_user_name);
        }
            // Cas on ho deneguem.
        else if (option == DENY){
            printf("Request cancelled.\n");
        }
        // Opció invàlida.
        while (option == INVALID_OPTION){
            printf("Invalid option!\n");
            option = readInt("\n");
        }
        popRandomUser (random_users);
    }
    free (random_users);
}

/// Funcions dedicades a gestionar les sol·licituds rebudes.

// Copiem l'usuari que ens ha enviat la sol·licitud a la nostra estructura d'amics.
// Com que les requests són una cua, llegim del primer a l'últim.
void insertNewFriend (Network *net, int idx_user, char *new_friend_name){

    int last =  net->user[idx_user].size_friends;

    net->user[idx_user].friend = expandStringArray (net->user[idx_user].friend,last);
    net->user[idx_user].friend[last] = copyString(new_friend_name);
    net->user[idx_user].size_friends += INCREMENT_SIZE;
}


void acceptOrDenyRequest (Network* net, int idx_operating_user) {

    int size_requests = net->user[idx_operating_user].size_requests;
    char **request = net->user[idx_operating_user].request;

    if (size_requests == NULL_SIZE){
        printf("\nYou don't have any requests.\n");
        return;
    }

    listStringArray(request, size_requests, "You", "request");

    printf("\nWe are going to manage the requests.\n");
    printf("[1 for YES, 0 for NO]\n");

    int option = INVALID_OPTION;

    // Triem si acceptar o no les sol·licituds.
    for (int i=0; i < size_requests; i++){

        printf("\nHi I'm %s! Do you want to be my friend?", request[i]);
        option = readInt ("\n");

        if (option == ACCEPT){

            // Nom de l'usuari acceptat, nom de l'usuari operant i l'índex de l'acceptat.
            char *accepted_user_name = request[i];
            char *operating_user_name = net->user[idx_operating_user].data[NAME];
            int idx_accepted_user = searchNetwork(accepted_user_name,net,NAME);

            // Afegim l'usuari acceptat dins l'usuari operant.
            insertNewFriend (net, idx_operating_user, accepted_user_name);

            // L'usuari acceptat afegeix també a l'operant dins dels seus amics.
            insertNewFriend (net, idx_accepted_user, operating_user_name);

            printf("You have accepted %s as a friend!\n", request[i]);

        }else{
            printf("Request denied\n");
        }

        // Després de llegir una sol·licitud, sempre l'esboreem de la llista.
        dequeueRequest(&net->user[idx_operating_user]);
    }
}

void manageRequestsMenu(Network *net, int user) {
    int option;
    do {
        printf("\n=== MANAGE REQUESTS MENU ===\n\n");

        printf("%d. Send friend request to choosed user.\n", OPTION_SEND_TO_CHOOSED_USER);
        printf("%d. Send friend request to random user.\n", OPTION_SEND_TO_RANDOM_USER);
        printf("%d. Accept/deny the pending requests.\n", OPTION_ACCEPT_DENY_REQUESTS);

        printf("%d. Return to previous menu.\n",OPTION_RETURN_TO_OPERATE_USER_MENU);
        option = readInt("Choose your option:\n");

        system("cls");

        switch (option) {
            case OPTION_SEND_TO_CHOOSED_USER: sendChoosedUserRequest(net, user); break;
            case OPTION_SEND_TO_RANDOM_USER: sendRandomUsersRequest(net, user); break;
            case OPTION_ACCEPT_DENY_REQUESTS: acceptOrDenyRequest(net, user); break;
            case OPTION_RETURN_TO_OPERATE_USER_MENU: break;
            default: printf("\nInvalid option!\n"); break;
        }
    } while (option != OPTION_RETURN_TO_OPERATE_USER_MENU);
}
