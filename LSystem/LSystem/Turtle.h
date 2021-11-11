#ifndef _TURTLE_H_
#define _TURTLE_H_

#include "R3Mesh.h"

#include <stack>

// Composite 组合模式
class TurtleComponent
{
public:
    virtual ~TurtleComponent() = default;
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
}; // class TurtleComponent

class TurtleComposite
    : public TurtleComponent
{
    R3Mesh *_mesh;
    std::stack<TurtleComponent> _children;

public:
    TurtleComposite(R3Mesh *mesh);
    void save();
    void restore();
    void draw(float param);
    void drawLeaf(float param);
}; // class TurtleComposite

#endif