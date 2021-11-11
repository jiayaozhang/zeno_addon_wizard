#include "LMesh.h"
#include "LCore.h"

#include <iostream>

void LMesh::tree(std::string &&code)
{
    LCore core{this};
    auto axiom{core.genAxiomFromCode(std::move(code))};
    core.draw(axiom);
    _update();
}

void LMesh::_update()
{
    // todo
}