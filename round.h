#ifndef round_h
#define round_h

#include "stdafx.h"


class round
{
public:
    
    //*** constructors ***//
    round();
    round(const train[], const pile[], const tile, const int);
    round(const round&);
    
    //*** destrcutor ***//
    ~round();
    
    //*** getters and setters ***//
    int getSize() const;
    int getCurrentPlayer() const;
    int getNextPlayer() const;
    int getWinner() const;
    pile* getPiles();
    train* getTrains();
    tile getEngine() const;
    
    void setWinner(const int);
    void switchToOtherPlayer();
    
    
    //*** other ***//
    
    //used to display round number and scores
    void displayRoundNumber(const int) const;
    void formatScore(const string, const int, const int) const;
    
    
    //used to display player hands
    void displayPlayerHands(const int, const int) const;
    void displayOuterHandElements(const pile) const;
    void displayOuterTileElement(const tile) const;
    void displayInnerHandElements(const pile) const;
    void displayInnerTileElement(const tile) const;
    
    //used to display boneyard
    void displayBoneyard(const string) const;
    
    //used to display the trains
    void displayPlayerTrains() const;
    void printOuterPlayerTrain() const;
    void printInnerPlayerTrain() const;
    
    //used to display the mexican train
    void displayMexicanTrain() const;
    
    
private:
    static const int m_size = 3;
    pile m_round_piles[m_size];
    train m_round_trains[m_size];
    tile m_engine;
    int m_current_player;
    int m_winner;
};

#endif
