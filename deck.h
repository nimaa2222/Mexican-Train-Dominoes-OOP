#ifndef deck_h
#define deck_h

#include "stdafx.h"

class deck
{
public:
    
    //*** constructors ***//
    deck();
    deck(const vector<tile>);
    deck(const deck&);
    
    //*** destrcutor ***//
    ~deck();
    
    //*** getters and setters ***//
    int getMaxSize() const;
    int getCurrentSize() const;
    tile getTile(const int) const;
    
    void Shuffle();
    void removeTile(const tile);
    
    //*** overloaded operators ***//
    deck& operator = (const deck&);
    
private:
    static const int m_max_size = 55;
    vector<tile> m_deck_tiles;
};

#endif
