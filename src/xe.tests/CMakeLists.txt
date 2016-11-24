
find_package(UnitTest++ REQUIRED)

include_directories(${UTPP_INCLUDE_DIRS})

set (sources Main.cpp TestVector.cpp TestMatrix.cpp TestQuaternion.cpp)
set (target xe.tests)

add_definitions(-DXE_SHARED)

add_executable(${target} ${sources})

source_group(\\ FILES ${target})

target_link_libraries(${target} xe UnitTest++)
