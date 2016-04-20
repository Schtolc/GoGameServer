//
// Created by pavelgolubev345 on 20.04.16.
//

#ifndef GOGAMESERVER_BACKEND_H
#define GOGAMESERVER_BACKEND_H

#include <vector>
#include "Lobby.h"
#include "Definitions.h"



class Backend {
private:
    std::vector<Lobby> lobbies;
    int player_amount;
    int lobby_size;
    Backend() = default;
public:
    Backend(int size);
    std::array<int, BUFFER_SIZE> handle_request(std::array<int, BUFFER_SIZE> &request);
};


#endif //GOGAMESERVER_BACKEND_H
