#include "LMesh.h"
#include "LCore.h"

#include <iostream>

void LMesh::tree(std::string &&code)
{
    LCore core{this};
    auto axiom{core.generateFromCode(std::move(code))};
    std::cout << axiom << '\n';
}