// Projecte de la Xarxa Social
// Estructures de Dades i Algoritmes II
// Universitat Pompeu Fabra

// Marc Bosch Manzano
// Yuxiang Jiang
// Zhiyuan Lai

#include "menu/menu.h"
#include "network/network_data_control.h"
#include "network/network_file_control.h"
#include "language.h"

int main () {
    Network *net;
    if (!(net = initNetwork())) 
        return 1;
    readUsersFile(net, USERS_PATH);
    showMenu(net);
    clearNetwork(net);
    return 0;
}
