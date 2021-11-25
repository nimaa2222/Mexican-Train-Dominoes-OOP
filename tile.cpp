#include "stdafx.h"

//*** the constructors ***//
tile::tile()
{
    m_front_end = 0;
    m_back_end = 0;
}

tile::tile(const int front_end, const int back_end)
{
    this->m_front_end = front_end;
    this->m_back_end = back_end;
}

tile::tile(const tile &otherTile)
{
    m_front_end = otherTile.m_front_end;
    m_back_end = otherTile.m_back_end;
}

//*** destrcutor ***//
tile::~tile()
{
    //m_front_end --> static variable will be automatically destroyed
    //m_back_end --> static variable will be automatically destroyed
}


//*** getters and setters ***//
int tile::getFrontEnd() const
{
    return m_front_end;
}

int tile::getBackEnd() const
{
    return m_back_end;
}

int tile::getTileSum() const
{
    return m_front_end + m_back_end;
}

bool tile::isDouble() const
{
    return (m_front_end == m_back_end);
}

void tile::setTile(const int new_front, const int new_back)
{
    if (new_front > 9 || new_front < 0)
        return;
    
    if (new_back > 9 || new_back < 0)
        return;
    
    m_front_end = new_front;
    m_back_end = new_back;
}

//switch the front and the back end
void tile::flip()
{
    int temp = m_front_end;
    m_front_end = m_back_end;
    m_back_end = temp;
}

//*** other ***//
void tile::displayTile() const
{
    cout<<m_front_end<<'-'<<m_back_end;
}

//*** overloaded operators ***//
bool tile::operator == (const tile& other_tile) const
{
    if (m_front_end == other_tile.m_front_end && m_back_end == other_tile.m_back_end)
        return true;
    
    if (m_front_end == other_tile.m_back_end && m_back_end == other_tile.m_front_end)
        return true;
    
    return false;
}

bool tile::operator != (const tile& other_tile) const
{
    return !(*this == other_tile);
}

bool tile::operator < (const tile& other_tile) const
{
    return (this->getTileSum() < other_tile.getTileSum());
}

tile& tile::operator = (const tile& other_tile)
{
    m_front_end = other_tile.m_front_end;
    m_back_end = other_tile.m_back_end;
    
    return *this;
}

