# CMakeList.txt : CMake project for Shooter_Raylib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 4.0)
project(Shooter_Raylib)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#Debugging
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# Raylib options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # global CMake switch
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)    # don’t pull Raylib’s example builds

# Jolt Options
set(OPTION_OVERRIDE_LIBCXX OFF CACHE BOOL "" FORCE) # Ensures runtime libraries match
set(CPP_RTTI_ENABLED ON CACHE BOOL "" FORCE)        # Fixes MSVC compilation errors with RTTI
set(FORCE_INSTALLER_CRT_DYNAMIC ON CACHE BOOL "" FORCE)
# Force /MD
set(USE_STATIC_MSVC_RUNTIME OFF CACHE BOOL "" FORCE)
# If Jolt is specifically looking for this common toggle:
set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
# Disable Jolt's extra stuff to speed up your build
set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)

set(DOUBLE_PRECISION OFF)
set(CROSS_PLATFORM_DETERMINISTIC ON)
set(CPP_RTTI_ENABLED OFF)
set(OBJECT_LAYER_BITS 16)

# Remove Warnings as Errors for Windows
if(MSVC)
	add_compile_options(/wd4865)
	set(FLAGS_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
	# Set runtime library
	if (USE_STATIC_MSVC_RUNTIME_LIBRARY)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()
endif()

include(FetchContent)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
		JoltPhysics
		GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
		GIT_TAG "v5.4.0"
		SOURCE_SUBDIR "Build"
)
FetchContent_MakeAvailable(JoltPhysics)

file(GLOB_RECURSE SHOOTER_SOURCES
	"Source/*.cpp"
	"Source/*.h"
)

# Add source to this project's executable.
add_executable (Shooter_Raylib ${SHOOTER_SOURCES}
		Source/Core/Nodes/World/CameraNode.cpp
		Source/Core/Nodes/World/CameraNode.h
		Source/Core/Nodes/World/CameraNode.h
		Source/Core/Meshes/Renderable.cpp
		Source/Core/Meshes/Renderable.h)

# Mirror folder structure
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SHOOTER_SOURCES})

set_target_properties(Shooter_Raylib PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Game"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Game"
)

set(CMAKE_CROSSCONFIG_DEFAULT_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Game")
set(CMAKE_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Game")

target_include_directories(Shooter_Raylib PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/Source
		${CMAKE_SOURCE_DIR}/ThirdParty/rapidjson/include
		${JoltPhysics_SOURCE_DIR}/..
)

target_link_libraries(Shooter_Raylib PRIVATE
	raylib
	Jolt
)

target_compile_features(Shooter_Raylib PUBLIC cxx_std_20)

# TODO: Add tests and install targets if needed.
