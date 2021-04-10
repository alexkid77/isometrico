#include <CTileMap.h>

CTileMap::CTileMap()
{
    //ctor
}

CTileMap::~CTileMap()
{
    //dtor
}

/** \brief Carga un mapa de un fichero tmx, primero carga las propiedades del mapa, y despues las capas con sus tiles
 *
 * \param file string
 *
 */
CTileMap::CTileMap(string file)
{
    string tileset=".";
    tmxparser::TmxMap map;
    tmxparser::TmxReturn error = tmxparser::parseFromFile(file, &map,tileset);
    int tileSize=map.tileWidth/2;

vector< STileProperties*> propiedades;
    for (auto it =   map.tilesetCollection.begin(); it !=   map.tilesetCollection.end(); ++it)
    {
        for (auto it2 = it->tileDefinitions.begin(); it2 != it->tileDefinitions.end(); ++it2)
        {

            STileProperties *prop=new STileProperties();
           string kk= it2->second.propertyMap["alto"];
            printf("id:%d val:%s\n",it2->second.id,kk.c_str());
            prop->Alto=stoi(it2->second.propertyMap["alto"]);
            prop->Ancho=stoi(it2->second.propertyMap["ancho"]);
            prop->Largo=stoi(it2->second.propertyMap["largo"]);
            prop->Indice=it2->second.id;
            propiedades.push_back(prop);

      //  printf("id:%d val:%s\n",it2->second.id,val.c_str());
//            x++;
        }
    }

       sort( propiedades.begin( ), propiedades.end( ), [ ]( const STileProperties* lhs, const STileProperties* rhs )
    {
        return lhs->Indice <rhs->Indice;
    });

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
             STileProperties *prop=propiedades[it2->tileFlatIndex];
            Vec3D boxSize=Vec3D(prop->Ancho,prop->Largo,prop->Alto);
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
