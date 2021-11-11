#ifndef _L_CORE_H_
#define _L_CORE_H_

#include "R3Mesh.h"
#include "Turtle.h"

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

using AssociativeArray = std::unordered_map<
    std::string,
    std::vector<std::string>>;

class Core
{
private:
    R3Mesh *_mesh;
    TurtleComposite _turtle;
    float _defaultCoefficient{0.0f};

    std::string _reproduce(
        std::string &&axiom,
        const AssociativeArray &rules,
        const int iterations);

    std::string _produce(
        std::string &&axiom,
        const AssociativeArray &rules);

    std::string _replaceAll(
        std::string &&str,
        std::string_view from,
        std::string_view to);

    void _run(const char command,const float param);

public:
    Core(R3Mesh *mesh);
    std::string genAxiomFromCode(std::string &&code);
    void draw(std::string axiom);
}; // class Core

#endif