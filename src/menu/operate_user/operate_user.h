//
// Created by Usuari on 27/5/2023.
//

#ifndef XARXA_SOCIAL_OPERATE_USER_H
#define XARXA_SOCIAL_OPERATE_USER_H

#define OPTION_MANAGE_REQUESTS (1)
#define OPTION_MANAGE_FRIENDS (2)
#define OPTION_MANAGE_POSTS (3)
#define EXIT (-1)

typedef struct Network Network;

/// Menú per a operar amb un usuari
void operateUserMenu(Network *net);

#endif //XARXA_SOCIAL_OPERATE_USER_H