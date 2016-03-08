#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

class Board {
   
private:
    bitset<64> black;
    bitset<64> taken;    

    // int weights[8][8] = {15, 10, 5, 5, 5, 5, 10, 15, 
    //                      10, -5, 1, 1, 1, 1, -5, 10, 
    //                      5,   1, 1, 1, 1, 1,  1, 5,
    //                      5,   1, 1, 1, 1, 1,  1, 5,
    //                      5,   1, 1, 1, 1, 1,  1, 5,
    //                      5,   1, 1, 1, 1, 1,  1, 5,
    //                      10, -5, 1, 1, 1, 1, -5, 10,
    //                      15, 10, 5, 5, 5, 5, 10, 15};
       
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
    int scoreMove(Move *m, Side side);

    void setBoard(char data[]);
};

#endif
