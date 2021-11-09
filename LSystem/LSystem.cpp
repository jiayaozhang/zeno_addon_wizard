#include "zeno/zeno.h"
#include "zeno/types/StringObject.h"
#include "zeno/types/PrimitiveObject.h"

/* todo
#include "R2/R2.h"
#include "R3/R3.h"
#include "R3Mesh.h"
*/

#include <string>
#include <string_view>
#include <unordered_map>

namespace zeno
{
    static const std::unordered_map<std::string, char> kConvTable{
        {"turnRight", '+'},
        {"turnLeft", '-'},
        {"pitchDown", '&'},
        {"pitchUp", '^'},
        {"rollLeft", '<'},
        {"rollRight", '<'},
        {"turn180Degree", '|'},
        {"drawBranch", 'f'},
        {"goForward", 'g'},
        {"saveState", '['},
        {"restoreState", ']'},
    };

    struct AppendLOP : zeno::INode
    {
        virtual void apply() override
        {
            auto LCommand = std::make_shared<zeno::StringObject>();

            auto instring = get_input<zeno::StringObject>("LCommand")->get();
            auto type = get_param<std::string>("op_type");
            instring += kConvTable.at(type);
            LCommand->set(instring);

            set_output("LOP", std::move(LCommand));
        }
    };

    ZENDEFNODE(AppendLOP,
               {{
                    {"StringObject", "LCommand", ""},
                },
                {
                    {"StringObject", "LOP"},
                },
                {
                    {"enum Begin "
                     //maybe use x-marco way
                     "turnRight" " "
                     "turnLeft" " "
                     "pitchDown" " "
                     "pitchUp" " "
                     "rollLeft" " "
                     "rollRight" " "
                     "turn180Degree" " "
                     "drawBranch" " "
                     "goForward" " "
                     "saveState" " "
                     "restoreState",
                     "op_type", "turnRight"},
                },
                {"LSystem"}});

    struct LSysGenerator : zeno::IObject
    {
        std::string code;
        std::string getCode() { return code; }
        void appendOp(const char &s)
        {
            code += s;
        }
    };

    struct ProceduralTree : zeno::INode
    {
        virtual void apply() override
        {
            auto prim = std::make_shared<zeno::PrimitiveObject>();

            auto generator = get_input<zeno::LSysGenerator>("LSysGenerator");
            auto code = generator->getCode();
            auto iterations = get_param<int>("iterations");

            /*need check
            auto mesh = std::make_unique<R3Mesh>();
            mesh->Tree(code, iterations);

            auto prim = std::make_shared<zeno::PrimitiveObject>();
            auto &pos = prim->add_attr<zeno::vec3f>("pos");
            auto &uv = prim->add_attr<zeno::vec3f>("uv");
            auto &nrm = prim->add_attr<zeno::vec3f>("nrm");
            ​
            std::unordered_map<R3MeshVertex *, int> m;
            ​for (auto i{0}; i < mesh->NVertices(); ++i)
            {
                const auto& v{mesh->Vertex(i)};

                const auto& p{v->position};
                pos.push_back(zeno::vec3f(p.X(), p.Y(), p.Z()));

                const auto& t{v->texcoords};
                uv.push_back(zeno::vec3f(t.X(), t.Y(), 0.0));

                const auto& n{v->normal};
                nrm.push_back(zeno::vec3f(n.X(), n.Y(), n.Z()));

                m[v] = i;
            }

            ​for (auto i{0}; i < mesh->NFaces(); ++i)
            {
                const auto& f{mesh->Face(i)};
                auto t0 = m[f->vertices[0]];
                auto t1 = m[f->vertices[1]];
                auto t2 = m[f->vertices[2]];
                prim->tris[i] = zeno::vec3i(t0, t1, t2);
            }
            */

            set_output("prim", prim);
        }
    };

    ZENDEFNODE(ProceduralTree, {{
                                    "LSysGenerator",
                                },
                                {
                                    {"primitive", "prim"},
                                },
                                {
                                    {"int", "iterations", "0"},
                                },
                                {"LSystem"}});

    struct R3MeshToPrim : zeno::INode
    {
        virtual void apply() override
        {
            auto prim = std::make_shared<zeno::PrimitiveObject>();

            //auto mesh = get_input<R3Mesh>("R3Mesh");

            // todo conv

            set_output("prim", prim);
        }
    };

    ZENDEFNODE(R3MeshToPrim,
                   {/* inputs: */ {
                        "R3Mesh",
                    },
                    /* outputs: */ {
                        "prim",
                    },
                    /* params: */ {},
                    /* category: */ {
                        "LSystem",
                    }});

    struct PrimToR3Mesh : zeno::INode
    {
        virtual void apply() override
        {
            //auto mesh = std::make_shared<R3Mesh>();

            auto prim = get_input<zeno::PrimitiveObject>("prim");

            // todo conv

            //set_output("R3Mesh", mesh);
        }
    };
    ZENDEFNODE(PrimToR3Mesh,
               {/* inputs: */ {
                    "prim",
                },
                /* outputs: */ {
                    "R3Mesh",
                },
                /* params: */ {},
                /* category: */ {
                    "LSystem",
                }});
}