#include "R3Mesh.h"
#include "Core.h"

#include <iostream>

void R3Mesh::tree(std::string &&code)
{
    Core core{this};
    auto axiom{core.genAxiomFromCode(std::move(code))};
    core.draw(axiom);
    _update();
}

void R3Mesh::_update()
{
    // todo
}