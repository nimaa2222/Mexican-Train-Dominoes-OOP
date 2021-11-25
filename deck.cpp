#include "stdafx.h"

//*** constructors ***//
deck::deck()
{
    //the tile pips go from 0-9
    int tiles_num = 10;
    
    //create all possible 55 tiles and place in deck
    for (int i=0; i<tiles_num; i++)
    {
        for (int j=i; j<tiles_num; j++)
        {
            tile new_tile(i,j);
            m_deck_tiles.push_back(new_tile);
        }
    }
}

deck::deck(const vector<tile> deck_tiles)
{
    m_deck_tiles = deck_tiles;
}

deck::deck(const deck& other_deck)
{
    m_deck_tiles = other_deck.m_deck_tiles;
}

//*** destrcutor ***//
deck::~deck()
{
    //m_max_size --> static variable will be automatically destroyed
    //m_deck_tiles --> standard library container will take care of its own memory management
}


//*** getters and setters ***//

int deck::getMaxSize() const
{
    return m_max_size;
}

int deck::getCurrentSize() const
{
    return (int)m_deck_tiles.size();
}

tile deck::getTile(const int tile_index) const
{
    return m_deck_tiles[tile_index];
}

/* *********************************************************************
Function Name: Shuffle
Purpose: To shuffle the game deck
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void deck::Shuffle()
{
    //shuffle the tiles in the deck - engine has been removed
    
    //giving each tile 2 chances to be swapped by another tile
    int swap_times = (m_max_size - 1) * 2;
    
    //used to hold 2 random integers for tile swaps
    int first_rand = 0;
    int second_rand = 0;
    
    //swap the tiles in the deck in pairs
    for (int i=0; i<swap_times; i++)
    {
        //generate 2 random numbers in range 0-53
        first_rand = rand() % (m_max_size - 1);
        second_rand = rand() % (m_max_size - 1);
        
        //swap the two tiles based on random indices generated previosuly
        tile temp = m_deck_tiles[first_rand];
        m_deck_tiles[first_rand] = m_deck_tiles[second_rand];
        m_deck_tiles[second_rand] = temp;
    }
}


/* *********************************************************************
Function Name: removeTile
Purpose: To remove a tile from the deck
Parameters:
            tile_to_remove, an object of the tile class passed by
            value. It is used to find and remove the specified tile
            from the deck.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void deck::removeTile(const tile tile_to_remove)
{
    //find the index of the tile in the deck to be removed
    int tile_index = 0;
    for (int i=0; i<(int)m_deck_tiles.size(); i++)
    {
        if (m_deck_tiles[i] == tile_to_remove)
            tile_index = i;
    }
    
    //remove the tile from the deck
    m_deck_tiles.erase(m_deck_tiles.begin() + tile_index);
}

//*** overloaded operators ***//
deck& deck::operator = (const deck& other_deck)
{
    m_deck_tiles = other_deck.m_deck_tiles;
    return *this;
}
