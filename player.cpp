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
    testingMinimax = true;
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
    std::cerr<<"HEREE"<<std::endl;
    if(diffT >= msLeft)
    {
        return nullptr;
    }

    return doMinimaxMove(opponentsMove, msLeft);
    //return doHeurMove(opponentsMove, time(&lastT));
    
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
Move *Player::doRandomMove(Move *opponentsMove, int msLeft) {
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
Move *Player::doHeurMove(Move *opponentsMove, int msLeft) {
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
Move *Player::doMinimaxMove(Move *opponentsMove, int msLeft) {
	// Start timer
    time_t startT;
    time_t lastT;
    time(&startT);
    int mX = -1;
    int mY = -1;
    int curMaxScore = -99999999;
    Board *tempbd = this->gameBoard->copy();
    

    
    int scores[8][8]  = {
        {9999999, -50, 100, 100, 100, 100, -50, 9999999},
        {-50, -9999999, 0, 0, 0, 0, -9999999, -50},
        {100, 0, 0, 0, 0, 0, 0, 100},
        {100, 0, 0, 0, 0, 0, 0, 100},
        {100, 0, 0, 0, 0, 0, 0, 100},
        {100, 0, 0, 0, 0, 0, 0, 100},
        {-50, -9999999, 0, 0, 0, 0, -9999999, -50},
        {9999999, -50, 100, 100, 100, 100, -50, 9999999}};

    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            Move *temp = new Move(i, j);
            if(this->gameBoard->checkMove(temp, this->ourSide))
            {
                tempbd->doMove(temp, this->ourSide);
                std::cerr << i <<" | "<<j<< std::endl;
                scores[i][j] += this->dfs(tempbd, this->opponentSide, 3, this->ourSide);
                if(scores[i][j] == 0)
                {
                    scores[i][j] = -1;
                }
                if(scores[i][j] > curMaxScore && scores[i][j] != 0)
                {
                    std::cerr <<"Best Cur "<< i <<" | "<<j<< std::endl;
                    curMaxScore = scores[i][j];
                    mX = i;
                    mY = j;
                }
            }
            else
            {
                scores[i][j] = 0;
            }
            
        }
    }
    std::cerr <<"IM HERE"<<std::endl;
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            std::cerr << scores[i][j] <<" , ";
        }
        std::cerr<<std::endl;
    }
    
    if(mX >= 0 && mY >= 0)
    {
        
        Move *temp = new Move(mX, mY);

        this->gameBoard->doMove(temp, this->ourSide);
        return temp;
    }
        
    return nullptr;
}

int Player::dfs(Board *tpBoard, Side curside, int depth, Side otherside)
{
    if(depth <= 0 || (tpBoard->hasMoves(curside) && tpBoard->hasMoves(otherside)))
    {
        return  tpBoard->count(this->opponentSide)-tpBoard->count(this->ourSide);
    }
    depth--;
    int tempIntDFS = 0 ;
    int better = 0;
    //if(tpBoard->hasMoves(curside) && tpBoard->)
    if(this->ourSide == curside)
    {
        better = 999999;
    }
    else
    {
        better = -999999;
    }
    
    
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            Move *temp = new Move(i, j);
            if(tpBoard->checkMove(temp, curside))
            {
                //std::cerr << i <<" | "<<j<< std::endl;
                Board *tpBoardTwo = tpBoard->copy();
                tpBoardTwo->doMove(temp, curside);
                tempIntDFS = this->dfs(tpBoardTwo, otherside, depth, curside);
                tempIntDFS*=-1;
                if(this->ourSide == curside)
                {
                    tempIntDFS*=-1;
                    better = min(better, tempIntDFS);
                }
                else
                {
                    
                    better = max(better, tempIntDFS);
                }
                
            }
        }
    }
    return better;
    
}


