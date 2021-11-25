#ifndef tile_h
#define tile_h

#include "stdafx.h"

class tile
{
public:
    
    //*** constructors ***//
    tile();
    tile(const int, const int);
    tile(const tile&);
    
    //*** destrcutor ***//
    ~tile();
    
    //*** getters and setters ***//
    int getFrontEnd() const;
    int getBackEnd() const;
    int getTileSum() const;
    bool isDouble() const;
    
    void setTile(const int, const int);
    void flip();
    
    //*** other ***//
    void displayTile() const;
    
    //*** overloaded operators ***//
    bool operator == (const tile&) const;
    bool operator != (const tile&) const;
    
    //map implementation purposes
    bool operator < (const tile&) const;
    tile& operator = (const tile&);
    
private:
    int m_front_end;
    int m_back_end;
};

#endif
