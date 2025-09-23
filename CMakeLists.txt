# CMakeList.txt : CMake project for Shooter_Raylib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 4.0)

project(Shooter_Raylib)

include(FetchContent)
FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

# Add source to this project's executable.
add_executable (Shooter_Raylib
	"Source/Shooter_Raylib.cpp"
	"Source/Shooter_Raylib.h"
	
	"Source/Tools/IniParser.h"
	"Source/Tools/IniParser.cpp"
	
	"Source/Debugging/Logger.h"
	"Source/Debugging/Logger.cpp"
	
	"Source/Core/Window.h"
	"Source/Core/Window.cpp"

	"Source/Core/Nodes/Node.cpp"
	"Source/Core/Nodes/Node.h"
	"Source/Core/IDAllocator.cpp"
	"Source/Core/IDAllocator.h"
	Source/Core/World.cpp
	Source/Core/World.h
	Source/Core/Nodes/World/WorldRoot.cpp
	Source/Core/Nodes/World/WorldRoot.h
	Source/Core/Nodes/2D/Circle2D.cpp
	Source/Core/Nodes/2D/Circle2D.h
	Source/Core/LevelLoader.cpp
	Source/Core/LevelLoader.h
	Source/Core/NodeFactory.h
        Source/Core/NodeFactory.cpp
)

source_group("Source" FILES
	"Source/Shooter_Raylib.cpp"
	"Source/Shooter_Raylib.h"
)

source_group("Tools" FILES
	"Source/Tools/IniParser.h"
	"Source/Tools/IniParser.cpp"
)

source_group("Debugging" FILES
	"Source/Debugging/Logger.h"
	"Source/Debugging/Logger.cpp"
)

source_group("Core" FILES
	"Source/Core/Window.h"
	"Source/Core/Window.cpp"
	"Source/Core/IDAllocator.cpp"
	"Source/Core/IDAllocator.h"
)

source_group("Core\\Nodes" FILES
	"Source/Core/Nodes/Node.cpp"
	"Source/Core/Nodes/Node.h"
)

set_target_properties(Shooter_Raylib PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$(SolutionDir)$(Configuration)"
)

target_include_directories(Shooter_Raylib PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/rapidjson/include)
target_link_libraries(Shooter_Raylib PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Shooter_Raylib PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
