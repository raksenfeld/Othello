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
    // Start timer
    time_t startT;
    time_t lastT;
    time(&startT);
    
    // Processes opponent move
    if(opponentsMove != nullptr)
    {
        this->gameBoard->doMove(opponentsMove, this->opponentSide);
    }
    
    // Check if time is left
    time(&lastT);
    int diffT=difftime(lastT, startT);
    
    if(msLeft == -1 )
    {
        msLeft = 999999999;
    }
    if(diffT >= msLeft)
    {
        return nullptr;
    }

    return doHeurMove(opponentsMove, time(&lastT));
    
}


/***
 * Compute the next random move given the opponent's last move. Your AI is
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
Move *doRandomMove(Move *opponentsMove, int msLeft) {
	// Start timer
    time_t startT;
    time_t lastT;
    time(&startT);
    
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
}


/***
 * Compute the next move given the opponent's last move using heuristics.
 * Your AI is expected to keep track of the board on its own.
 * If this is the first move, or if the opponent passed on the last 
 * move, then opponentsMove will be nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *doHeurMove(Move *opponentsMove, int msLeft) {
	// Start timer
    time_t startT;
    time_t lastT;
    time(&startT);
    
    // THIS IS THE CORNER
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(i, j);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    
    // This is for the edges
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 2; j < 6; j++)
        {
            Move *temp = new Move(i, j);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    
    for(int i = 0; i < 8; i+=7)
    {
        for(int j = 2; j < 6; j++)
        {
            Move *temp = new Move(j, i);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    
    // This is for the middle
    for(int i = 1; i < 7; i++)
    {
        for(int j = 1; j < 7; j++)
        {
            if(((i == 1 && j == 1) || (i == 1 && j == 6) || (i == 6 && j == 1) || (i == 6 && j == 6))==false)
            {
                Move *temp = new Move(i, j);
                time(&lastT);
				int diffT=difftime(lastT, startT);
				if(diffT >= msLeft)
				{
					return nullptr;
				}
                else if(this->gameBoard->checkMove(temp, this->ourSide))
                {
                    this->gameBoard->doMove(temp, this->ourSide);
                    return temp;
                }
                delete temp;
            }
        }
    }
    
    // This is for the catty corners
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(j, i);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    
    
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 0; j < 8; j+=7)
        {
            Move *temp = new Move(i, j);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    
    // This is for the inner corners
    for(int i = 1; i < 7; i+=5)
    {
        for(int j = 1; j < 7; j+=5)
        {
            Move *temp = new Move(i, j);
            time(&lastT);
            int diffT=difftime(lastT, startT);
            if(diffT >= msLeft)
            {
				return nullptr;
            }
            else if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                this->gameBoard->doMove(temp, this->ourSide);
                return temp;
            }
            delete temp;
        }
    }
    return nullptr;
}


/***
 * Compute the next move given the opponent's last move using minimax
 * algorithm. Your AI is expected to keep track of the board on its own.
 * If this is the first move, or if the opponent passed on the last 
 * move, then opponentsMove will be nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *doMinimaxMove(Move *opponentsMove, int msLeft) {
	// Start timer
    time_t startT;
    time_t lastT;
    time(&startT);
    
    return nullptr;
}


