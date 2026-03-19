//
// Created by Usuari on 27/5/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operate_user.h"
#include "ceo_utils/ceo_utils.h"
#include "manage_requests/manage_requests.h"
#include "manage_friends/manage_friends.h"
#include "manage_posts/manage_posts.h"
#include "network_data_control.h"
#include "option_utils.h"
#include "search_utils.h"

int chooseOperatingUser(Network *net){

    printf("\nWhich user do you want to operate with?\n");

    char *name = readString();
    if (strcmp(name, "CEO") == 0){
        ceoMenu(net);
        return EXIT;
    }

    int user_idx = searchNetwork(name, net, NAME);
    if (user_idx == USER_NOT_FOUND){
        printf("\nThe user was not found!\n");
        return EXIT;
    }

    if (isBanned(net, user_idx)) {
        printIsBannedMessage();
        return EXIT;
    }

    printf("\nProfile of user %s initialized!\n", net->user[user_idx].data[NAME]);
    return user_idx;
}


void operateUserMenu (Network *net) {

    int user = chooseOperatingUser(net);
    if (user == EXIT){
        return;
    }

    int option;
    do {
        printf("\n==== OPERATE USER MENU ====\n\n");

        printf("%d. Manage Requests\n", OPTION_MANAGE_REQUESTS);
        printf("%d. Manage Friends\n", OPTION_MANAGE_FRIENDS);
        printf("%d. Manage Posts\n", OPTION_MANAGE_POSTS);
        printf("%d. Return to principal menu.\n",OPTION_RETURN_MENU);

        option = readInt("Choose your option:\n");

        system("cls");

        switch(option) {
            case OPTION_MANAGE_REQUESTS: manageRequestsMenu(net, user); break;
            case OPTION_MANAGE_FRIENDS: manageFriendsMenu(net, user); break;
            case OPTION_MANAGE_POSTS: managePostsMenu(net, user); break;
            case OPTION_RETURN_MENU: break;
            default: printf("\nInvalid option!\n"); break;
        }        
    } while (option != OPTION_RETURN_MENU);
}
