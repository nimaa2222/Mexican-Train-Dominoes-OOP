#ifndef player_h
#define player_h


#include "stdafx.h"


class player
{

public:
    
    //*** constructors ***//
    player();
    player(const int);
    player(const player&);
    
    //*** destrcutor ***//
    ~player();
    
    //*** getters and setters ***//
    int getScore() const;
    void updateScore(const int);
    
    //*** other ***//
    int takeTurn(round&, int&, bool&, bool&, player*[], const int, int&) const;
    void displayGame(round, const int, const int, const int) const;
    void pressEnter() const;
    bool playerCanMove(round&, const int) const;
    int tileTrainSelection(round&) const;
    int matchTileTrain(round&, const int, const int) const;
    void appendTileToTrain(round&, const int, const int) const;
    vector<int> identifyEligibleTrains(round&) const;
    vector<tile> identifyTileCandidates(round&) const;
    
    //*** overloaded operators ***//
    player& operator= (player&);
    
    //*** pure virtual functions ***//
    virtual int selectTileIndex(round&) const = 0;
    virtual int selectTrainIndex(round&, int&) const = 0;
    virtual int selectAction() const = 0;
    
protected:
    int m_score;
    
};

#endif
