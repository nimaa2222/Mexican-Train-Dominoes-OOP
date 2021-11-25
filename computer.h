#ifndef computer_h
#define computer_h

#include "stdafx.h"

class computer: public player
{
public:
    
    bool isDoublePlayed(round&, tile) const;
    void printTileStrategy(round&, const int, const string) const;
    void printTrainStrategy(round&, const int, const string) const;
    
    //pure virutal in parent class
    int selectAction() const;
    int selectTileIndex(round&) const;
    int selectTrainIndex(round&, int&) const;
    
    
};

#endif
