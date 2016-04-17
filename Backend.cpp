//
// Created by pavelgolubev345 on 11.04.16.
//

#include "Backend.h"

Backend::Backend(int playerAmount) : amount(playerAmount), state(WAITING), currentToken(0), lastStep(Step()) {}



//response [0] - function [1-5] - parameters
std::array<int, BUFFER_SIZE> Backend::parse_request(std::array<int, BUFFER_SIZE> &request) {
    std::array<int, BUFFER_SIZE> response = std::array<int, BUFFER_SIZE>();
    switch (request[0]) {
        case SERVER_STATE:
            response[0] = serverState();
            break;
        case IS_LOCKED:
            response[0] = isLocked(request[1]);
            break;
        case REGISTER:
            response[0] = registerPlayer(request[1]);
            break;
        case MAKESTEP:
            response[0] = makeStep(request[1], Step(request[2], request[3], request[4]));
            break;
        case GETSTEP: {
            Step tmp = getStep(request[1]);
            response[0] = tmp.X;
            response[1] = tmp.Y;
            response[2] = tmp.team;
        }
            break;
        case PASSSTEP:
            response[0] = passStep(request[1]);
            break;
        case GET_GAMEOVER:
            state = GAMEOVER;
            response[0] = true;
            break;
        default:
            std::cout << "error happended" << std::endl;
    }

    return response;
}

int Backend::serverState() {
//
    return state;
}


bool Backend::isLocked(int token) {
    assert (0 <= token && token <= 1000);
    return token != currentToken;
}

int Backend::registerPlayer(int token) {
    assert (0 <= token && token <= 1000);
    if (players.size() == amount) {
        return -1;
    }

    if (players.find(token) == players.end()) {
        if (players.size() == 0) {
            currentToken = token;
        }
        players.insert(std::pair<int, Player>(token, Player(0, players.size(), false)));
        if (players.size() == amount) {
            state = SERVERREADY;
        }
        return players.size() - 1;
    }
    std::cout << "player already registerd" << std::endl;
    return -2;
}

bool Backend::makeStep(int token, Step step) {
    assert (0 <= token && token <= 1000 && 0 <= step.X && step.X <= 18 && 0 <= step.Y && step.Y <= 18 &&
            step.team == players.at(currentToken).team);
    lastStep = step;

    for (auto it = players.begin(); it != players.end(); ++it) {
        if (it->first != token) {
            it->second.UpdateRequired = true;
        }
    }

    int currentTeam = 0;
    if (players.at(token).team != amount-1) {
        currentTeam = players.at(token).team+1;
    }

    for (auto it = players.begin(); it != players.end(); ++it) {
            if(it->second.team == currentTeam) {
                currentToken = it->first;
                break;
            }
    }

    return true;
}

Step Backend::getStep(int token) {
    if (players.at(token).UpdateRequired == true) {
        players.at(token).UpdateRequired = false;
        return lastStep;
    } else {
        return Step (-1,-1,-1);
    }
}

bool Backend::passStep(int token) {
    int currentTeam = 0;
    if (players.at(token).team != amount-1) {
        currentTeam = players.at(token).team+1;
    }

    for (auto it = players.begin(); it != players.end(); ++it) {
        if(it->second.team == currentTeam) {
            currentToken = it->first;
            break;
        }
    }

    return true;
}
