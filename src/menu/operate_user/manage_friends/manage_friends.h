//
// Created by Usuari on 28/5/2023.
//

#ifndef XARXA_SOCIAL_32_MANAGE_FRIENDS_H
#define XARXA_SOCIAL_32_MANAGE_FRIENDS_H

#define OPTION_LIST_FRIENDS (1)
#define OPTION_FRIEND_POST (2)
#define OPTION_REMOVE_FRIEND (3)
#define OPTION_RETURN_TO_OPERATE_USER_MENU (0)

typedef struct Network Network;
void manageFriendsMenu (Network *net, int idx_operating_user);

#endif //XARXA_SOCIAL_32_MANAGE_FRIENDS_H
