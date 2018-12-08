#pragma once
#include <Box2D/Box2D.h>

class MathTools {
public:
    static float distance(float x1, float y1, float x2, float y2) {
        auto x = x1 - x2;
        auto y = y1 - y2;
        auto xSquare = x*x;
        auto ySquare = y*y;
        return std::sqrt(xSquare + ySquare);
    }

    static int pnpoly(int nvert, b2Vec2* verts, float testx, float testy)
    {
            int i, j, c = 0;
            for (i = 0, j = nvert-1; i < nvert; j = i++) {
                    if ( ((verts[i].y>testy) != (verts[j].y>testy)) &&
                         (testx < (verts[j].x-verts[i].x) * (testy-verts[i].x) / (verts[j].y-verts[i].y) + verts[i].x) )
                            c = !c;
            }
            return c;
    }

};