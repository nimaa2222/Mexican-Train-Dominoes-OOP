#include "stdafx.h"

//*** constructors ***//
game::game()
{
    m_game_deck = deck();
    m_round_number = 0;
}

game::game(player* comp_pl, player* human_pl, deck game_deck)
{
    m_game_deck = game_deck;
    m_players[comp_player] = comp_pl;
    m_players[human_player] = human_pl;
    m_round_number = 0;
}

game::game(const game& other_game)
{
    m_game_deck = other_game.m_game_deck;
    m_rounds = other_game.m_rounds;
    
    for (int i=0; i<m_max_players; i++)
        m_players[i] = other_game.m_players[i];
   
    m_round_number = other_game.m_round_number;
}

game::~game()
{
    //m_max_players --> static variable will be automatically destroyed
    //m_game_deck --> underlying object destructor called
    //m_rounds --> standard library container will take care of its own memory management
    //m_players --> static array destoyed + underlying object destructor called
    //m_round_number --> static variable will be automatically destroyed
}

//*** getters and setters ***//
int game::getRoundNumber() const
{
    return m_round_number;
}

int game::getMaxPlayers() const
{
    return m_max_players;
}

void game::setRoundNumber(const int new_round_num)
{
    m_round_number = new_round_num;
}


void game::addRound(const round& this_round)
{
    m_rounds.push_back(this_round);
}


