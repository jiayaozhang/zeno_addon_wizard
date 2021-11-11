#include "LCore.h"
#include "LMesh.h"

#include <cstdlib>
#include <sstream>
#include <iostream>

LCore::LCore(LMesh *mesh)
    : _mesh{mesh} {}

std::string LCore::generateFromCode(std::string &&code)
{
    std::stringstream ss{std::move(code)};
    auto isSetIterations{false};
    int iterations;
    auto isSetDefaultCoefficient{false};
    float defaultCoefficient;
    auto isSetThickness{false};
    float thickness;
    std::string axiom;
    AssociativeArray rules;
    std::cout << "code :" << code << "\n";
    while (!ss.eof())
    {
        char c;
        ss >> c;
        if (c == '@')
        {
            break;
        }
        std::string line;
        if (c == '#')
        {
            getline(ss, line);
            continue;
        }
        ss.putback(c);
        if (!isSetIterations)
        {
            ss >> iterations;
            isSetIterations = true;
            continue;
        }
        if (!isSetDefaultCoefficient)
        {
            std::cout << "3\n";
            ss >> defaultCoefficient;
            isSetDefaultCoefficient = true;
            continue;
        }
        if (!isSetThickness)
        {
            ss >> thickness;
            //turtle.thickness = thickness / 100;
            isSetThickness = true;
            continue;
        }
        getline(ss, line);
        auto equalSignPos{line.find("=")};
        if (equalSignPos == std::string::npos)
        {
            axiom = line;
        }
        else
        {
            rules[line.substr(0, equalSignPos)].push_back(line.substr(equalSignPos + 1));
        }
    }
    return _reproduce(std::move(axiom), rules, iterations);
}

std::string LCore::_reproduce(
    std::string &&axiom,
    const AssociativeArray &rules,
    const int iterations)
{
    if (iterations > 0)
    {
        return _reproduce(_produce(std::move(axiom), rules), rules, iterations - 1);
    }
    return axiom;
}

std::string LCore::_produce(
    std::string &&axiom,
    const AssociativeArray &rules)
{
    for (const auto &[key, value] : rules)
    {
        int index = rand() % value.size();
        axiom = _replaceAll(std::move(axiom), key, value[index]);
    }
    return axiom;
}

std::string LCore::_replaceAll(std::string &&str, std::string_view from, std::string_view to)
{
    if (from.empty())
    {
        return str;
    }
    std::size_t start_pos{0};
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
