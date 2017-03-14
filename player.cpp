
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
    if(diffT >= msLeft)
    {
        return nullptr;
    }
    
    if(this->testingMinimax == true)
    {
        return doMinimaxMove(opponentsMove, msLeft);
    }
    else
    {
        return doHeurMove(opponentsMove, time(&lastT));
    }
    
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
    
    // Initialize score array with heuristic values for each spot
  /*  int scores[8][8]  = {

        {9999999, -20, 20, 20, 20, 20, -20, 9999999},
        {-20, 0, 0, 0, 0, 0, 0, -20},
        {20, 0, 0, 0, 0, 0, 0, 20},
        {20, 0, 0, 0, 0, 0, 0, 20},
        {20, 0, 0, 0, 0, 0, 0, 20},
        {20, 0, 0, 0, 0, 0, 0, 20},
        {-20, 0, 0, 0, 0, 0, 0, -20},
        {9999999, -20, 20, 20, 20, 20, -20, 9999999}};
   */

    int scores[8][8]  = {
        
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    
	// Update score array based on current state of game
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			Move *temp = new Move(i, j);
			if(this->gameBoard->checkMove(temp, this->ourSide))
			{
				// Calls dft to find the best move 
				tempbd->doMove(temp, this->ourSide);
				std::cerr<<"currently looking ahead "<<i<<" , "<<j<<std::endl;
				scores[i][j] += this->dfs(tempbd, this->opponentSide, 2, this->ourSide);
				
				if(scores[i][j] == 0)  // WHY ARE WE DOING THIS??
				{
					scores[i][j] = -1;
				}
				
				// Sets the current move to best if better than old best
				if(scores[i][j] > curMaxScore)
				{
					curMaxScore = scores[i][j];
					mX = i;
					mY = j;
				}
			}
			/* else    // Current spot is not a valid move
			{
				scores[i][j] = -8888;
			} */
			delete temp;
		}   
	}
    
    // Prints out score array for testing
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			std::cerr<<scores[i][j]<<" ";
		}
		std::cerr<<std::endl;
	}

	// Play the best move based on score array
	if(mX >= 0 && mY >= 0)
	{
		Move *temp = new Move(mX, mY);
		// Checks if there is time left
		time(&lastT);
		int diffT=difftime(lastT, startT);
		if(diffT >= msLeft)
		{
			return nullptr;
		}
		else
		{
			std::cerr<<"Picked move "<<mX<<" , "<<mY<<std::endl;

			this->gameBoard->doMove(temp, this->ourSide);
			return temp;
		}
	}

    return nullptr;
}

/**
 * 
 */
int Player::dfs(Board *tpBoard, Side curside, int depth, Side otherside)
{
	// Base case; returns the difference in number of pieces on board
    if(depth <= 0 || !(tpBoard->hasMoves(curside) || tpBoard->hasMoves(otherside)))
    {
        
        std::cerr<<"has move current side"<<tpBoard->hasMoves(curside)<<std::endl;
        std::cerr<<"has move other side"<<tpBoard->hasMoves(otherside)<<std::endl;

        return tpBoard->count(this->ourSide)-tpBoard->count(this->opponentSide);
    }
    depth--;
    
    int tempIntDFS = 0 ;
    int better = -999999;
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Move *temp = new Move(i, j);
            if(tpBoard->checkMove(temp, curside))
            {
                Board *tpBoardTwo = tpBoard->copy();
                tpBoardTwo->doMinimaxMove(temp, curside);  //CHANGED THIS TO DO MINMAX MOVE
                tempIntDFS = this->dfs(tpBoardTwo, otherside, depth, curside);
                std::cerr<<"better "<<better<<std::endl;
                if(this->ourSide == curside)
                {
                    std::cerr<<"better max"<<"better"<<better<<", tempint "<<tempIntDFS<<std::endl;
                    better = max(better, tempIntDFS);
                }
                else
                {
                    // tempIntDFS *= -1;
                    std::cerr<<"better min"<<"better"<<better<<", tempint "<<tempIntDFS<<std::endl;
                    better = max(better, -1 * tempIntDFS);
                    //better *= -1;
                }
                
                std::cerr<<"better after "<<better<<std::endl;

            }
        }
    }
    return better;
    
}
