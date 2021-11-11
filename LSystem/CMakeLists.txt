cmake_minimum_required(VERSION 3.10)

include_directories(L3D L3D/R2 L3D/R3 L3D/jpeg)
aux_source_directory(L3D L3D)
aux_source_directory(L3D/R2 R2)
aux_source_directory(L3D/R3 R3)
aux_source_directory(L3D/jpeg jpeg)

# ZENO extension must be a SHARED library with name starting with `zeno_`
# otherwise it won't be automcatically loaded on ZENO startup
add_library(zeno_LSystem SHARED
    LSystem.cpp
    ${L3D}
    ${R2}
    ${R3}
    ${jpeg}
)

# Finally don't forget to link zeno.dll
target_link_libraries(zeno_LSystem PUBLIC zeno)