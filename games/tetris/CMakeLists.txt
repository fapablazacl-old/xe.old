
set (target tetris)
set (sources 
	MessageBus.hpp 
	MessageBus.cpp
	System.hpp 
	System.cpp
	GameLogic.hpp
	GameLogic.cpp
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})
