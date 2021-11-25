#ifndef human_h
#define human_h

#include "stdafx.h"

class human: public player
{
public:
    
    void displayTrainEligiblity(const vector<int>) const;
    
    //pure virutal in parent class
    int selectAction() const;
    int selectTileIndex(round&) const;
    int selectTrainIndex(round&, int&) const;
};

#endif
