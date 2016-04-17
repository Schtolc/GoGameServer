//
// Created by pavelgolubev345 on 11.04.16.
//

#ifndef GOGAMESERVER_BACKEND_H
#define GOGAMESERVER_BACKEND_H

#include <array>
#include <map>
#include <iostream>
#include <assert.h>

#define BUFFER_SIZE 6
#define WAITING 4
#define SERVERREADY 0
#define SERVERFULL 2
#define GAMEOVER 1

#define SERVER_STATE 10
#define IS_LOCKED 11
#define REGISTER 12
#define MAKESTEP 13
#define GETSTEP 14
#define PASSSTEP 15
#define GET_GAMEOVER 16


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

class Backend {
private:
    int amount;
    int state;
    std::map<int,Player> players;
    int currentToken;
    Step lastStep;

    Backend() = default;

public:
    Backend(int playerAmount);

    std::array<int, BUFFER_SIZE> parse_request(std::array<int, BUFFER_SIZE> &request);

    int serverState();
    bool isLocked(int token);
    int registerPlayer(int token);
    bool makeStep(int token, Step step);
    Step getStep(int token);
    bool passStep(int token);
    ~Backend() = default;
};


#endif //GOGAMESERVER_BACKEND_H
