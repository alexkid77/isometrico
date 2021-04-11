#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <comun.h>
#include <vector>
#include <utils.h>
#include <algorithm>
#include <CEntity.h>
using namespace std;

/** \brief Entidad basica de sprite
 */
class CSprite:public CEntity
{
public:
    //colisiones
    vector<CSprite*> vColisiones;

    //profundida de dibujado
    int Depth;
    //lista de entidades que estan por debajo de este sprite y se dibujaran antes
    vector<CSprite*> entidadesDebajo;
    bool visitado;



    /** \brief devuelve un vector con las coordenadas de los tiles que ocupa un sprite en el mapa
     *
     * \return vector<Vec2D>
     *
     */
    vector<Vec2D> getTilesOcupados();


    /** \brief obtiene las coordenadas convertidas para mostrar en pantalla
     *
     * \return Vec2D
     *
     */
    Vec2D getPosProj();


    /** \brief dadas unas coordenadas de tile indica si esta ocupado el el sprite o no
     *
     * \param x int
     * \param y int
     * \return bool
     *
     */
    bool OcupaTile(int x,int y);


    /** \brief indica si se solapan dos sprites
     *
     * \param b CSprite*
     * \return bool
     *
     */
    bool SolapaEntidad(CSprite *b);
    CSprite();

    /** \brief
     *
     * \param tileGridW int
     * \param tileGridH int
     * \param tileSize int
     * \param BoxSize Vec3D
     *
     */
    CSprite(int tileGridW,int tileGridH,int tileSize,Vec3D BoxSize);



    virtual ~CSprite();

    virtual void onCollision(CEntity *ent);
    virtual bool hasCollision(CEntity *ent);
    Vec3D getIntersection(CEntity *ent);
    virtual void Update(double deltaTime);

    void ClearDepth();
    int getDepth()
    {
        return this->Depth;
    }

protected:
    int tileSize;
private:
    int tileGridW,tileGridH;

};

#endif // ENTIDAD_H
