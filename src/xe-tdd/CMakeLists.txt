
set (target xe-tdd)
set (sources Main.cpp TestVector.cpp TestMatrix.cpp TestQuaternion.cpp TestMesh.cpp)

add_definitions(-DXE_SHARED)

add_executable(${target} ${sources})

source_group(\\ FILES ${sources})

target_link_libraries(${target} xe UnitTest++)
