#include <CTileMap.h>

CTileMap::CTileMap()
{
    //ctor
}

CTileMap::~CTileMap()
{
    //dtor
}

CTileMap::CTileMap(string file)
{
    string tileset;
    tmxparser::TmxMap map;
    tmxparser::TmxReturn error = tmxparser::parseFromFile(file, &map,tileset);
    int tileSize=map.tileWidth/2;
    for (auto it = map.layerCollection.begin(); it != map.layerCollection.end(); ++it)
    {
        CLayer *capa=new CLayer();
        capa->height=it->height;
        capa->width=it->width;
        capa->name=it->name;
        capa->visible=it->visible;

        int conta=0;
        for (auto it2 = it->tiles.begin(); it2 != it->tiles.end(); ++it2)
        {
            int j=conta%capa->width;
            int i=conta/capa->width;

            Vec2D vtemp;
            vtemp.y=i*tileSize;
            vtemp.x=j*tileSize;
            vtemp=utils::IsoTo2D(&vtemp);
            int x = vtemp.x;
            int y = vtemp.y;

            Vec3D boxSize=it2->tileFlatIndex==1?Vec3D(32,32,1):Vec3D(32,32,50);
            CTile *t=new CTile(tileSize,tileSize,tileSize,boxSize);
            t->indiceTile=it2->tileFlatIndex;
            t->Pos.x=j*tileSize;
            t->Pos.y=i*tileSize;
            t->Pos.z=0;
            t->i=i;
            t->j=j;
            t->PosProj.x=x;
            t->PosProj.y=y;
            t->id=it2->gid;


            capa->tiles.push_back(t);
            conta++;
        }
        this->Layers.push_back(capa);
    }
}

