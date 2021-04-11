#ifndef CENTITY_H
#define CENTITY_H

#include <comun.h>
/** \brief Entidad basica
 */
class CEntity
{
public:

    int id;
    TiposSprite Tipo;
    //Posicion del objeto
    Vec3D Pos;
    //Posicion Anterior del objeto
    Vec3D PosAnt;
    //tamaño del bouding box del objeto
    Vec3D Size;

    Vec2D PosProj;
    CEntity();
    virtual ~CEntity();

    virtual void Update(double deltaTime)=0;

    /** \brief evento on colision el parametro el la entidad contra la que colisiona
     *
     * \param ent CEntity*
     * \return virtual void
     *
     */
    virtual void onCollision(CEntity *ent)=0;

protected:

private:
};

#endif // CENTITY_H
