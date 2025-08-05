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
	
	"Source/Core/Factories/EntityFactory.h"
	"Source/Core/Factories/EntityFactory.cpp"

	"Source/Core/Entity/Component.h"

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
)

source_group("Core\\Entities" FILES
	"Source/Core/Entity/Component.h"
)

source_group("Core\\Factories" FILES
	"Source/Core/Factories/EntityFactory.h"
	"Source/Core/Factories/EntityFactory.cpp"
)

set_target_properties(Shooter_Raylib PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$(SolutionDir)$(Configuration)"
)

target_link_libraries(Shooter_Raylib PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Shooter_Raylib PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
