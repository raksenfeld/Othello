#include "player.hpp"
#include<iostream>

//If it hits a corner, got there automatic

/**
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    gameBoard = new Board();
    ourSide = side;
    if(ourSide == WHITE)
    {
        opponentSide = BLACK;
    }
    else
    {
        opponentSide = WHITE;
    }
}

/***
 * Destructor for the player.
 */ 
Player::~Player() {
}

/***
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     
    // Processes opponent move
    time_t startT;
    time_t lastT;
    time(&startT);
    if(opponentsMove != nullptr)
    {
        std::cerr<<" || "<<std::endl;
        this->gameBoard->doMove(opponentsMove, this->opponentSide);
    }
    std::cerr<<"FGGGG"<< msLeft<<std::endl;
    
    if(msLeft == 0)
    {
        return nullptr;
    }
    std::cerr<<"T"<<std::endl;

    // NEED MS TIME
    // THIS IS THE CORNER
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
    std::cerr<<"FRST"<<std::endl;
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 2; j < 6; j++)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
      std::cerr<<"SECOND"<<std::endl;
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 2; j < 6; j++)
        {
            Move *temp = new Move(j, i);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
      std::cerr<<"THRID"<<std::endl;
    for(int i = 1; i < 7; i++)
    {
        for(int j = 1; j < 7; j++)
        {
            if(((i == 1 && j == 1) || (i == 1 && j == 6) || (i == 6 && j == 1) || (i == 6 && j == 6))==false)
            {
                Move *temp = new Move(i, j);
                std::cerr<<i<<" || "<<j<<std::endl;
                if(this->gameBoard->checkMove(temp, this->ourSide))
                {
                    this->gameBoard->doMove(temp, this->ourSide);
                    return temp;
                }
            }
        }
    }
      std::cerr<<"EWWWW"<<std::endl;
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(j, i);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
      std::cerr<<"EWW"<<std::endl;
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
     std::cerr<<"EWWWWWW"<<std::endl;
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 1; j < 7; j+=5)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
        }
    }
    return nullptr;
    

    
    //
    /*
    // Check for legal moves
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
               {
                   //Current time, which is higher than startT
                   time(&lastT);
                   int diffT=difftime(lastT, startT);
                   this->gameBoard->doMove(temp, this->ourSide);
                   if(diffT >= msLeft)
                   {
                       return nullptr;
                   }
                   else
                   {
                        return temp;
                   }
               }

        }
    }
    return nullptr;
    */
}
     




