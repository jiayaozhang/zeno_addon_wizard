#ifndef _L_TURTLE_H_
#define _L_TURTLE_H_

#include "LMesh.h"

#include <stack>

// Composite 组合模式
class LTurtleComponent
{
public:
    virtual ~LTurtleComponent() = default;
    void turnRight(float angle);
    void turnLeft(float angle);
    void pitchDown(float angle);
    void pitchUp(float angle);
    void rollLeft(float angle);
    void rollRight(float angle);
    void move(float distance);
    void turn180(float temp);
    void thicken(float param);
    void narrow(float param);
    void setThickness(float param);
    void setReduction(float param);
}; // class LTurtleComponent

class LTurtleComposite
    : public LTurtleComponent
{
    LMesh *_mesh;
    std::stack<LTurtleComponent> _children;

public:
    LTurtleComposite(LMesh *mesh);
    void save();
    void restore();
    void draw(float param);
    void drawLeaf(float param);
}; // class LTurtleComposite

#endif