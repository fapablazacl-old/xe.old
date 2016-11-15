
set (sources Main.cpp TestVector.cpp TestMatrix.cpp TestQuaternion.cpp)
set (target xe.tests)

add_definitions(-DXE_SHARED)
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(${target} ${sources})

target_link_libraries(${target} xe ${Boost_LIBRARIES})
