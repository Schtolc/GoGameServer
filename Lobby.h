//
// Created by pavelgolubev345 on 11.04.16.
//

#ifndef LOBBY_H
#define LOBBY_H

#include <array>
#include <map>
#include <iostream>
#include <assert.h>

#include "Definitions.h"



struct Player {
    int score;
    int team;
    bool UpdateRequired;

    Player() : score(0), team(-1), UpdateRequired(false) { }
    Player(int s, int t, bool update) : score(s), team(t), UpdateRequired(update) { }

};

struct Step {
    int X;
    int Y;
    int team;

    Step() : X(0), Y(0), team(0) {}
    Step(int x, int y, int t) : X(x), Y(y), team(t) {}
    Step(const Step& other) : X(other.X), Y(other.Y), team(other.team) {}

};

class Lobby {
private:
    int lobby_id;
    int amount;
    int state;
    std::map<int,Player> players;
    int currentToken;
    Step lastStep;

    Lobby() = default;

public:
    Lobby(int id, int playerAmount);

    std::array<int, BUFFER_SIZE> parse_request(std::array<int, BUFFER_SIZE> &request);

    int serverState();
    bool isLocked(int token);
    int registerPlayer(int token);
    bool makeStep(int token, Step step);
    Step getStep(int token);
    bool passStep(int token);
    ~Lobby() = default;
};


#endif //LOBBY_H
