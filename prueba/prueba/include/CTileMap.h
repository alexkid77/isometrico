#ifndef CTILEMAP_H
#define CTILEMAP_H

#include <vector>
#include <CTile.h>
#include <CLayer.h>
#include "tmxparser/tmxparser.h"
class CTileMap
{
public:
    vector<CLayer*> Layers;
    CTileMap();
    CTileMap(string file);
    CTile *GetTile(int layerIndex,int x,int y);
    virtual ~CTileMap();

protected:

private:
};

#endif // CTILEMAP_H
