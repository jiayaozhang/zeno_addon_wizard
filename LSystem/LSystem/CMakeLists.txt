cmake_minimum_required(VERSION 3.18)
project(LSystem LANGUAGES CXX)

add_library(LSystem)

target_sources(LSystem 
  PRIVATE	LCore.cpp LMesh.cpp
)
target_include_directories(LSystem 
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(LSystem PUBLIC cxx_std_17)
set_target_properties(LSystem
	PROPERTIES	POSITION_INDEPENDENT_CODE ON
)
