#ifndef train_h
#define train_h

#include "stdafx.h"

//collection of tiles
//computer train, human train, mexican train
class train
{
public:
    //*** constructors ***//
    train();
    train(const vector<tile>, const bool, const bool);
    train(const train&);
    
    //*** destrcutor ***//
    ~train();
    
    //*** getters and setters ***//
    int getSize() const;
    int getEndVal() const;
    tile getTile(const int) const;
    vector<tile> getDoubleTiles() const;
    bool isOrphanDouble() const;
    bool endsWithDouble() const;
    
    void setOrphanDouble();
    void addTile(const tile);
    void reverseTrain();
    
    //for personal train markers
    bool hasMarker() const;
    void addMarker();
    void removeMarker();
    
    //*** overloaded operators ***//
    train& operator = (const train&);
    
private:
    vector<tile> m_train_tiles;
    bool m_marker;
    bool m_orphan_double;
};

#endif
