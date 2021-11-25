#include "stdafx.h"

//*** constructors ***//
pile::pile()
{
    //cannot initialize with no tiles in the pile
}

pile::pile(const vector<tile> pile_tiles)
{
    m_pile_tiles = pile_tiles;
}

pile::pile(const pile& other_pile)
{
    m_pile_tiles = other_pile.m_pile_tiles;
}

//*** destrcutor ***//
pile::~pile()
{
    //m_pile_tiles --> standard library container will take care of its own memory management
}


//*** getters and setters ***//

int pile::getSize() const
{
    return (int)m_pile_tiles.size();
}


/* *********************************************************************
Function Name: getTileSums
Purpose: To calculate the sum of all tiles' pip sum in the pile
Parameters: None
Return Value: the sum of all tiles' pip sum in the pile
Assistance Received: None
********************************************************************* */
int pile::getTileSums() const
{
    int sum = 0;
    for (int i=0; i<m_pile_tiles.size(); i++)
        sum += m_pile_tiles[i].getTileSum();
    
    return sum;
}

/* *********************************************************************
Function Name: getTileIndex
Purpose: To find the index of a specifc tile in the pile
Parameters:
            tile_to_find, an object of the tile class passed by value.
            It refers to the tile that is being searched in the pile.
Return Value:
            the index of the specified tile, if found (integer)
            otherwise invalid_input (integer-enum)
            
Assistance Received: None
********************************************************************* */
int pile::getTileIndex(const tile tile_to_find) const
{
    for (int i=0; i<m_pile_tiles.size(); i++)
    {
        if (tile_to_find == m_pile_tiles[i])
            return i;
    }
    
    return invalid_input;
}

tile pile::getTile(const int tile_index) const
{
    return m_pile_tiles[tile_index];
}

/* *********************************************************************
Function Name: getTileOnTop
Purpose: To get a copy of top tile and remove this tile from the pile
Parameters: None
Return Value: the top tile, a tile object
Assistance Received: None
********************************************************************* */
tile pile::getTileOnTop()
{
    //identify the tile on the top of the pile
    tile copy;
    copy = m_pile_tiles[m_pile_tiles.size()-1];
    
    //remove the tile from the pile
    m_pile_tiles.erase(m_pile_tiles.begin() + m_pile_tiles.size()-1);
    
    return copy;
}

/* *********************************************************************
Function Name: isValueInPile
Purpose: To determine whether a specified value matches a number on one
         of the tiles in the pile
Parameters:
            value, an integer passed by value. This is the value
            that is being searched for in the pile.
Return Value:
            true if value exists in the pile,
            false otherwise
Assistance Received: None
********************************************************************* */
bool pile::isValueInPile(const int value) const
{
    for (int i=0; i<(int)m_pile_tiles.size(); i++)
    {
        //if the value matches the front or back end of any of the tiles in the pile
        if (m_pile_tiles[i].getFrontEnd() == value || m_pile_tiles[i].getBackEnd() == value)
            return true;
    }
    
    return false;
}

void pile::addToPile(const tile new_tile)
{
    m_pile_tiles.push_back(new_tile);
}


/* *********************************************************************
Function Name: removeFromPile
Purpose: To remove a tile from the pile
Parameters:
            tile_to_remove, an object of the tile class, passed by
            value. It refers to the tile to be removed from the pile.
Return Value: None
Assistance Received: None
********************************************************************* */
void pile::removeFromPile(const tile tile_to_remove)
{
    //find the index of the tile in the pile
    int tile_index = 0;
    for (int i=0; i<(int)m_pile_tiles.size(); i++)
    {
        if (m_pile_tiles[i] == tile_to_remove)
            tile_index = i;
    }
    
    //remove the tile from the pile
    m_pile_tiles.erase(m_pile_tiles.begin() + tile_index);
}

//*** overloaded operators ***//
pile& pile::operator = (const pile& other_pile)
{
    m_pile_tiles = other_pile.m_pile_tiles;
    return *this;
}



