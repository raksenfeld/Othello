#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {
    

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *doRandomMove(Move *opponentsMove, int msLeft);
    Move *doHeurMove(Move *opponentsMove, int msLeft);
    Move *doMinimaxMove(Move *opponentsMove, int msLeft);
    int dfs(Board *tpBoard, Side curside, int depth, Side otherside);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side ourSide;
    Side opponentSide;
    Board *gameBoard;
};

#endif
