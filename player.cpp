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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    //Process the opponents move
    int moveScore = 0;
    int maxScore = -50; //Ensures a valid move is made even if only move is bad
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
        //Let's just return a random move. Iterate through the board and return
        //the first valid move
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
                    if(moveScore > maxScore)
                    {
                        nextMove->setX(testMove->getX());
                        nextMove->setY(testMove->getY());
                        maxScore = moveScore;
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
