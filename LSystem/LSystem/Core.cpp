#include "Core.h"
#include "R3Mesh.h"

#include <cstdlib>
#include <sstream>
#include <iostream>

Core::Core(R3Mesh *mesh)
    : _mesh{mesh},
      _turtle{mesh} {}

std::string Core::genAxiomFromCode(std::string &&code)
{
    auto isSetIterations{false};
    int iterations;

    auto isSetDefaultCoefficient{false};
    float defaultCoefficient;

    auto isSetThickness{false};
    float thickness;

    std::string axiom;

    AssociativeArray rules;

    std::stringstream ss{std::move(code)};
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
            ss >> defaultCoefficient;
            isSetDefaultCoefficient = true;
            continue;
        }
        if (!isSetThickness)
        {
            ss >> thickness;
            // todo
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

std::string Core::_reproduce(
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

std::string Core::_produce(
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

std::string Core::_replaceAll(std::string &&str, std::string_view from, std::string_view to)
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

void Core::draw(std::string tree)
{
    char paramBuf[1024];
    int bufIndex = 0;
    std::string data = tree;
    float param = 0;
    bool getParam = false, checkParam = false;
    char command;
    for (int i = 0; i < data.size(); ++i)
    {
        char c = data[i];
        if (getParam)
        {
            if (c == ')')
            {
                paramBuf[bufIndex] = 0;
                bufIndex = 0;
                param = atof(paramBuf);
                getParam = false;
                _run(command, param);
            }
            else
                paramBuf[bufIndex++] = c;
            continue;
        }
        if (checkParam)
        {
            checkParam = false;
            if (c == '(')
            {
                param = 0;
                getParam = true;
                continue;
            }
            _run(command, 1);
        }
        command = c;
        checkParam = true;
    }
    if (checkParam)
        _run(command, 1);

    std::cout << data << std::endl;
}

void Core::_run(const char command, const float param)
{
    float co = _defaultCoefficient;
    float num = param;
    if (num == 1)
        num *= co;
    switch (command)
    {
    case '+':
        _turtle.turnLeft(num);
        break;
    case '-':
        _turtle.turnRight(num);
        break;
    case '&':
        _turtle.pitchDown(num);
        break;
    case '^':
        _turtle.pitchUp(num);
        break;
    case '<':
        _turtle.thicken(num);
        break;
    case '\\':
        _turtle.rollLeft(num);
        break;
    case '/':
        ////////////////////////////////////////  L++ ////////////////////////////////////////////////
        _turtle.rollRight(num);
        break;
    case '>':
        _turtle.narrow(num);
        break;
    case '%':
        _turtle.setReduction(param);
        break;
    case '=':
        _turtle.setThickness(param);
        break;
    case '|':
        _turtle.turn180(param);
        break;
    case '*':
        _turtle.drawLeaf(param);
        break;
    case 'F':
        [[fallthrough]];
    case 'f' : 
        _turtle.draw(param);
        [[fallthrough]];
     case 'G' : 
        [[fallthrough]];
    case 'g' :
    _turtle.move(param);
        break;
    case '[':
        _turtle.save();
        break;
    case ']':
        _turtle.restore();
        break;
    default:
        break;
    }
}