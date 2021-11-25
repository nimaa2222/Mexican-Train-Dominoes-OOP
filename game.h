#ifndef game_h
#define game_h

#include "stdafx.h"

class game
{
public:
    
    //*** constructors ***//
    game();
    game(player*, player*, deck);
    game(const game&);
    
    //*** destrcutor ***//
    ~game();
    
    //*** getters and setters ***//
    int getRoundNumber() const;
    int getMaxPlayers() const;

    void setRoundNumber(const int);
    void addRound(const round&);
    
    
private:
    const static int m_max_players = 2;
    deck m_game_deck;
    vector<round> m_rounds;
    player* m_players[m_max_players];
    int m_round_number;
};

#endif
