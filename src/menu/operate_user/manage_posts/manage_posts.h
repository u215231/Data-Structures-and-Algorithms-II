//
// Created by Usuari on 28/5/2023.
//

#ifndef XARXA_SOCIAL_33_MANAGE_POSTS_H
#define XARXA_SOCIAL_33_MANAGE_POSTS_H

#define OPTION_NEW_POST (1)
#define OPTION_LIST_POSTS (2)
#define OPTION_REMOVE_POST (3)
#define OPTION_RETURN_TO_OPERATE_USER_MENU (0)

typedef struct Network Network;
void managePostsMenu (Network *net, int idx_operating_user);

#endif //XARXA_SOCIAL_33_MANAGE_POSTS_H
