#ifndef pile_h
#define pile_h

#include "stdafx.h"

//collection of tiles
//computer hand, human hand, boneyard
class pile
{
public:
    //*** constructors ***//
    pile();
    pile(const vector<tile>);
    pile(const pile&);
    
    //*** destrcutor ***//
    ~pile();
    
    //*** getters and setters ***//
    int getSize() const;
    int getTileSums() const;
    int getTileIndex(const tile) const;
    tile getTile(const int) const;
    tile getTileOnTop();
    bool isValueInPile(const int) const;
    
    void addToPile(const tile);
    void removeFromPile(const tile);
    
    //*** overloaded operators ***//
    pile& operator = (const pile&);
    
private:
    vector<tile> m_pile_tiles;
};

#endif
