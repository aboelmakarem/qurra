# MeshGen
# Ahmed Hussein (amhussein4@gmail.com)
# March 28th 2024

cmake_minimum_required(VERSION 2.9)

project(meshgen, C)

# run cmake on dependencies
add_subdirectory(base)

# define an executable target, its include directories and link libraries
add_executable(meshgen meshgen.c)
target_include_directories(meshgen PUBLIC ${PROJECT_SOURCE_DIR}/base)
target_link_libraries(meshgen PRIVATE base)
