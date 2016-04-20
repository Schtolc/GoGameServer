//
// Created by pavelgolubev345 on 20.04.16.
//

#include "Backend.h"

std::array<int, BUFFER_SIZE> Backend::handle_request(std::array<int, BUFFER_SIZE> &request) {
    if (request[0] == REGISTER) {
        if (player_amount == lobby_size * lobbies.size()) {
            lobbies.push_back(Lobby(lobbies.size(), lobby_size));

        }
        player_amount++;
        return lobbies[lobbies.size() - 1].parse_request(request);
    } else {
        int lobby_id = request[BUFFER_SIZE - 1];
        return lobbies[lobby_id].parse_request(request);
    }
}

Backend::Backend(int size) : player_amount(0), lobby_size(size) {

}
