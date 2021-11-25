#include "stdafx.h"

//*** constructors ***//
train::train()
{
    m_marker = false;
    m_orphan_double = false;
}

train::train(const vector<tile> train_tiles, const bool marker, const bool orphan_double)
{
    m_train_tiles = train_tiles;
    m_marker = marker;
    m_orphan_double = orphan_double;
}

train::train(const train& other_train)
{
    m_train_tiles = other_train.m_train_tiles;
    m_marker = other_train.m_marker;
    m_orphan_double = other_train.m_orphan_double;
}

//*** destrcutor ***//
train::~train()
{
    //m_train_tiles --> standard library container will take care of its own memory management
    //m_marker --> static variable will be automatically destroyed
    //m_orphan_double --> static variable will be automatically destroyed
}

//*** getters and setters ***//

int train::getSize() const
{
    return (int)m_train_tiles.size();
}

int train::getEndVal() const
{
    return m_train_tiles[m_train_tiles.size()-1].getBackEnd();
}

tile train::getTile(const int tile_index) const
{
    return m_train_tiles[tile_index];
}

/* *********************************************************************
Function Name: getDoubleTiles
Purpose: To get a copy of the double tiles in the pile
Parameters: None
Return Value: a collection of tiles, a tile class vector
Assistance Received: None
********************************************************************* */
vector<tile> train::getDoubleTiles() const
{
    vector<tile> doubles_in_train;
    
    for (int i=0; i<m_train_tiles.size(); i++)
    {
        if (m_train_tiles[i].isDouble())
            doubles_in_train.push_back(m_train_tiles[i]);
    }
    
    return doubles_in_train;
}

bool train::isOrphanDouble() const
{
    return m_orphan_double;
}

bool train::endsWithDouble() const
{
    return m_train_tiles[m_train_tiles.size() - 1].isDouble();
}

/* *********************************************************************
Function Name: setOrphanDouble
Purpose: To mark trains that end with a double as orphan double
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void train::setOrphanDouble()
{
    //an empty train can't be an orphan double
    if (m_train_tiles.size() == 0)
        m_orphan_double = false;
    
    //an orphan double ends with a double
    else if (this->endsWithDouble())
        m_orphan_double = true;
    
    else
        m_orphan_double = false;
}

void train::addTile(const tile newTile)
{
    m_train_tiles.push_back(newTile);
}

/* *********************************************************************
Function Name: reverseTrain
Purpose: To reverse the tile ordering of the train
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void train::reverseTrain()
{
    vector<tile> temp;
    
    //make a copy of the train
    for (int i=0; i<m_train_tiles.size(); i++)
        temp.push_back(m_train_tiles[i]);
    
    //clear the train
    m_train_tiles.clear();
    
    //write the copy in reverse order back into train
    for (int i = (int)temp.size() - 1; i > -1; i--)
        m_train_tiles.push_back(temp[i]);
}

bool train::hasMarker() const
{
    return m_marker;
}

void train::addMarker()
{
    m_marker = true;
}

void train::removeMarker()
{
    m_marker = false;
    
}

//*** overloaded operators ***//
train& train::operator = (const train& other_train)
{
    m_train_tiles = other_train.m_train_tiles;
    m_marker = other_train.m_marker;
    return *this;
}




