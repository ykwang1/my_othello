#include "player.h"
#include <iostream>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;


    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     gameBoard = new Board();
     playing = side;
}

void Player::TestMinimax(char data[])
{
	this->gameBoard->setBoard(data);
}



/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
/*
Move *Player::doMove(Move *opponentsMove, int msLeft) {

     //TODO: Implement how moves your AI should play here. You should first
     //process the opponent's opponents move before calculating your own move
 
    //Process the opponents move
    int moveScore = 0;
    int maxScore = 0; 
    bool firstCheck = true;
    if(playing == WHITE)
    {
        gameBoard->doMove(opponentsMove, BLACK);
    } 
    else
    {
        gameBoard->doMove(opponentsMove, WHITE);
    }

    //Calculate a valid move
    if(gameBoard->hasMoves(playing))
    {
        // Returns the move with the highest score
        Move *testMove = new Move(0,0);
        Move *nextMove = new Move(0,0);
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                testMove->setX(i);
                testMove->setY(j);
                if(gameBoard->checkMove(testMove, playing))
                {
                    moveScore = gameBoard->scoreMove(testMove, playing);
                    cerr << "Move Score was: " << moveScore << " at (" << testMove->getX() <<
                        " , " << testMove->getY() << ")" <<endl;
                    if(moveScore > maxScore or firstCheck)
                    {
                        nextMove->setX(testMove->getX());
                        nextMove->setY(testMove->getY());
                        maxScore = moveScore;
                        firstCheck = false;
                    }
                }

            }
        }
        delete testMove;
        gameBoard->doMove(nextMove, playing);
        cerr << "Max Score was: " << maxScore << " at (" << nextMove->getX() <<
          " , " << nextMove->getY() << ")" <<endl;
        return nextMove;

    }
    return NULL;
}
*/
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    //Process the opponents move
    //int moveScore = 0;
    //int maxScore = 0; 
    //bool firstCheck = true;
    // Create Sdie object for the side not in play
    //    cerr << "score before:  " << gameBoard->scoreMove(opponentsMove, BLACK, true) << endl;
    Side nextPlayer;
    if(playing == WHITE)
    {
		nextPlayer = BLACK;
        gameBoard->doMove(opponentsMove, BLACK);
    } 
    else
    {
		nextPlayer = WHITE;
        gameBoard->doMove(opponentsMove, WHITE);
    }
    
    //Calculate a vector of valid moves
    vector<Move> validMoves = gameBoard->possible(playing);
    //cerr << validMoves.size() << endl;

    if(validMoves.size() > 0)
    {
		// Create int to store move with the minimax, as well as its value
		unsigned int minimaxMove = 0;
		int currScore = -500;
		
		for(unsigned int i=0; i < validMoves.size(); i++)
		{
			Move *testMove = &validMoves[i];
			Board *testBoard = gameBoard->copy();
			testBoard->doMove(testMove, playing);
			vector<Move> nextValidMoves = testBoard->possible(nextPlayer);
			
			// First valid move
			int minScore = testBoard->scoreMove(&nextValidMoves[0], playing, true);
			//cerr << "Next Valid move at (" << nextValidMoves[0].getX() <<
			//  " , " << nextValidMoves[0].getY() << ")" <<endl;
			//cerr << "MinScore:  " << minScore << endl << "curr score:   " << currScore << endl;
			
			// Find minimum score for Side Playing after each next valid move
			for (unsigned int j=1; j < nextValidMoves.size(); j++)
			{
				int testScore = testBoard->scoreMove(&nextValidMoves[j], playing, true);
				if (testScore < minScore)
				{
					minScore = testScore;
					//cerr << "Test score:  " << testScore << endl;
				}
			}
			
			if (minScore >= currScore)
			{
				currScore = minScore;
				minimaxMove = i;
			}
			//cerr << minimaxMove << endl;
			//Manage memory
			delete testBoard;
		}
		
		Move *nextMove = new Move(validMoves[minimaxMove].getX(), validMoves[minimaxMove].getY());
        gameBoard->doMove(nextMove, playing);
        //cerr << "Minimax Score was: " << currScore << " at (" << nextMove->getX() <<
        //  " , " << nextMove->getY() << ")" <<endl;
        return nextMove;
    }
    return NULL;
}

