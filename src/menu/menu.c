//
// Created by Marc Bosch Manzano on 26/4/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "language.h"
#include "menu.h"
#include "new_user/new_user.h"
#include "list_users/list_users.h"
#include "operate_user/operate_user.h"
#include "network_data_control.h"
#include "network_file_control.h"
#include "option_utils.h"

void showMenu(Network *net) {
    printf("\nWelcome to ZHIYUMARC Network!\n");
    printf("What do you want to do?\n");

    int option;
    do {
        printf("\n===== PRINCIPAL MENU =====\n\n");
        
        printf("%d. Insert new user.\n", OPTION_NEW_USER);
        printf("%d. List all existing users.\n", OPTION_LIST_USERS);
        printf("%d. Operate over an specific user.\n", OPTION_OPERATE_USER);
        printf("%d. Quit.\n", OPTION_QUIT);
        option = readInt("Choose your option:\n");

        system("cls");

        switch (option) {
            case OPTION_NEW_USER: newUser(net); break;
            case OPTION_LIST_USERS: listUsers(net); break;
            case OPTION_OPERATE_USER: operateUserMenu(net); break;
            case OPTION_QUIT: break;
            default: printf("\nInvalid option!\n"); break;
        }
    } while (option != OPTION_QUIT);
}
