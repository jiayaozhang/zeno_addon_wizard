cmake_minimum_required(VERSION 3.10)

include_directories(L3D)
aux_source_directory(L3D L3D)

# ZENO extension must be a SHARED library with name starting with `zeno_`
# otherwise it won't be automcatically loaded on ZENO startup
add_library(zeno_LSystem SHARED
    LSystem.cpp
    ${L3D}
)

# Finally don't forget to link zeno.dll
target_link_libraries(zeno_LSystem PUBLIC zeno)