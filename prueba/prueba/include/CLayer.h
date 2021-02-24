#ifndef CLAYER_H
#define CLAYER_H

#include <CTile.h>
#include <vector>
#include <string>
using namespace std;
class CLayer
{
public:

    CLayer();
    virtual ~CLayer();

    vector<CTile *>tiles;
    int height;
    int width;
    string name;
    bool visible;
protected:

private:
};

#endif // CLAYER_H
