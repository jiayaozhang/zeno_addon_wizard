#ifndef _L_CORE_H_
#define _L_CORE_H_

#include "LMesh.h"

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

using AssociativeArray = std::unordered_map<
    std::string,
    std::vector<std::string>>;

class LCore
{
private:
    LMesh *_mesh;

    std::string _reproduce(
        std::string &&axiom,
        const AssociativeArray &rules,
        const int iterations);

    std::string _produce(
        std::string &&axiom,
        const AssociativeArray &rules);

    void _replaceAll(std::string &str, std::string_view from, std::string_view to);

public:
    LCore(LMesh *mesh);
    std::string generateFromCode(std::string &&code);
}; // class LCore

#endif