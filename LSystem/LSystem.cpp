#include "zeno/zeno.h"
#include "zeno/types/StringObject.h"
#include "zeno/types/PrimitiveObject.h"

/* todo
#include "R2/R2.h"
#include "R3/R3.h"
#include "R3Mesh.h"
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace zeno
{
    struct LSysGenerator : zeno::IObject
    {
        int iterations_;
        int defaultCoefficient_;
        int thickness_;
        std::vector<std::string> rules_;

        LSysGenerator(
            const int iterations,
            const int defaultCoefficient,
            const int thickness)
            : iterations_{iterations},
              defaultCoefficient_{defaultCoefficient},
              thickness_{thickness},
              rules_{} {}

        std::string getCode()
        {
            std::string code{""};
            code += iterations_ + '\n';
            code += defaultCoefficient_ + '\n';
            code += thickness_ + '\n';
            for (auto rule : rules_)
            {
                code += rule + '\n';
            }
            return code;
        }
        
        void appendRule(const char ruleName)
        {
            rules_.emplace_back(std::string{ruleName} + '=');
        }

        void appendOp(const char op)
        {
            rules_[rules_.size() - 1] += op;
        }
    };

    struct MakeLSysGenerator : zeno::INode
    {
        virtual void apply() override
        {
            auto iterations = get_param<int>("iterations");
            auto defaultCoefficient = get_param<int>("defaultCoefficient");
            auto thickness = get_param<int>("thickness");

            auto generator = std::make_shared<LSysGenerator>(
                iterations, defaultCoefficient, thickness);
            set_output("generator", std::move(generator));
        }
    };

    ZENDEFNODE(MakeLSysGenerator,
        { /* inputs: */ {
        }, /* outputs: */ {
        "generator",
        }, /* params: */ {
        {"int", "iterations", "0"},
        {"int", "defaultCoefficient", "0"},
        {"int", "thicjness", "0"},
        }, /* category: */ {
        "LSystem",
        }});

    struct AppendLSysRule : zeno::INode
    {
        virtual void apply() override
        {
            auto generator = get_input<zeno::LSysGenerator>("generator");
            //cant use char!
            auto ruleName = get_param<std::string>("ruleName")[0];
            generator->appendRule(ruleName);
            set_output("generator", std::move(generator));
        }
    };

    ZENDEFNODE(AppendLSysRule,
               {{
                    {"LSysGenerator", "generator"},
                },
                {
                    {"LSysGenerator", "generator"},
                },
                {
                    //cant use char!
                    //{"char", "ruleName", ""},
                    {"string", "ruleName", ""},
                },
                {"LSystem"}});

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

    struct AppendLSysOP : zeno::INode
    {
        virtual void apply() override
        {
            auto generator = get_input<zeno::LSysGenerator>("generator");
            auto opStr = get_param<std::string>("opStr");
            generator->appendOp(kConvTable.at(opStr));
            set_output("generator", std::move(generator));
            auto LCommand = std::make_shared<zeno::StringObject>();
        }
    };

    ZENDEFNODE(AppendLSysOP,
               {{
                    {"LSysGenerator", "generator"},
                },
                {
                    {"LSysGenerator", "generator"},
                },
                {
                    /*the enum feature is useless???
                    //maybe use x-marco way
                    {"enum Begin "
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
                     */
                    {"string", "op_type", "turnRight"},
                },
                {"LSystem"}});

    struct ProceduralTree : zeno::INode
    {
        virtual void apply() override
        {
            auto prim = std::make_shared<zeno::PrimitiveObject>();

            auto generator = get_input<zeno::LSysGenerator>("LSysGenerator");
            auto code = generator->getCode();
            auto iterations = get_param<int>("iterations");

            std::cout << "my code: " << code << '\n';            

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