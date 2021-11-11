#ifndef _L_MESH_H_
#define _L_MESH_H_

#include <string>

class LMesh
{
private:
    void _update();

public:
    void tree(std::string &&code);
}; // class LMesh

#endif