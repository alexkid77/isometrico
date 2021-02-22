#ifndef CENTITY_H
#define CENTITY_H


class CEntity
{
public:
    int id;
    CEntity();
    virtual ~CEntity();
    void(*onCollision)(void);
protected:

private:
};

#endif // CENTITY_H
