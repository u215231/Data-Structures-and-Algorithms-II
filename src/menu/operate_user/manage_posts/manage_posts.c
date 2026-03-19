//
// Created by Usuari on 28/5/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "manage_posts.h"
#include "dictionary_utils.h"
#include "network_data_control.h"
#include "option_utils.h"
#include "print_utils.h"

void newPost (Network *net, int idx_operating_user) {

    int last = net->user[idx_operating_user].size_posts;

    // Expandim l'estructura de posts.
    net->user->post = expandStringArray(net->user->post, last);
    net->user[idx_operating_user].size_posts += INCREMENT_SIZE;

    // Llegim una string per consola (un nou post).
    printf("\nWrite your new post:\n");
    net->user[idx_operating_user].post[last] = readString();

    // Expandim l'estructura del diciconari.
    net->dictionary = expandElements(net->dictionary,net->dictionary->size_elements);

    // Fem el recompte de les paraules al diccionari.
    readWords(net->dictionary, net->user[idx_operating_user].post[last]);
}

void removePost (Network* net, int idx_operating_user, char **post, int size_posts){

    if(size_posts == NULL_SIZE){
        printf("You don't have any post!\n");
        return;
    }

    int idx_post = readInt("\nWhich post do you want to remove? Write a number of publication (0,1,2...).\n");

    if (idx_post > size_posts){
        printf("\nThat post does not exist!\n");
        return;
    }

    delete_String_In_StringArray(post, size_posts, idx_post);
    net->user[idx_operating_user].size_posts += DECREMENT_SIZE;

    printf("Your post number %d has been removed from your posts!\n", idx_post);
}

void managePostsMenu(Network *net, int user) {
    int option;
    do {
        printf("\n==== MANAGE POSTS MENU ====\n\n");

        printf("%d. Make a new post.\n", OPTION_NEW_POST);
        printf("%d. List all of my posts.\n", OPTION_LIST_POSTS);
        printf("%d. Remove post.\n", OPTION_REMOVE_POST);

        printf("%d. Return to previous menu.\n", OPTION_RETURN_TO_OPERATE_USER_MENU);
        option = readInt("Choose your option:\n");

        system("cls");

        char **post = net->user[user].post;
        int size_posts = net->user[user].size_posts;

        switch (option) {
            case OPTION_NEW_POST: newPost(net, user); break;
            case OPTION_LIST_POSTS: listStringArray(post, size_posts, "You", "post"); break;
            case OPTION_REMOVE_POST: removePost(net, user, post, size_posts); break;
            case OPTION_RETURN_TO_OPERATE_USER_MENU: break;
            default: printf("\nInvalid option!\n"); break;
        }
    } while (option != OPTION_RETURN_TO_OPERATE_USER_MENU);
}
