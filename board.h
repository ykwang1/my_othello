#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
#include <vector>
using namespace std;

class Board {
   
private:
    bitset<64> black;
    bitset<64> taken;    
    int weights[8][8] = {{7,  -3, 5, 5, 5, 5,  -3, 7}, 
                         {-3,  -5, 1, 1, 1, 1, -5, -3}, 
                         {5,   1, 1, 1, 1, 1,  1, 5},
                         {5,   1, 1, 1, 1, 1,  1, 5},
                         {5,   1, 1, 1, 1, 1,  1, 5},
                         {5,   1, 1, 1, 1, 1,  1, 5},
                         {-3,  -5, 1, 1, 1, 1, -5, -3},
                         {7,  -3, 5, 5, 5, 5,  -3, 7}};
    /*
    int weights[8][8] = {{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1}};
    */
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
    
public:
    Board();
    ~Board();
    
    Board *copy();
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    int scoreMove(Move *m, Side side, bool test);
    int countWithWeights(Side side);
    
	vector<Move> possible(Side playing);
    void setBoard(char data[]);
};

#endif
