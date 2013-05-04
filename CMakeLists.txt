cmake_minimum_required(VERSION 2.8)

project(TriangleSuper)

# Set options
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type ( Debug / Release )" FORCE)
set(SFML_STATIC_LIBS FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
set(THOR_STATIC_LIBS FALSE CACHE BOOL "Choose whether Thor is linked statically or not.")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules;${CMAKE_MODULE_PATH}")

if(SFML_STATIC_LIBS)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

if(THOR_STATIC_LIBS)
    set(THOR_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
find_package(Thor 2 REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

if(THOR_FOUND)
    include_directories(${THOR_INCLUDE_DIR})
else()
    set(THOR_ROOT "" CACHE PATH "Thor top-level directory")
    message("\n-> Thor directory not found. Set THOR_ROOT to Thor's top-level path (containing \"include\" and \"lib\" directories).")
endif()

# Add source files
set(SRC_DIR "src")

message(${CMAKE_SOURCE_DIR})

set( SOURCES
    ${SRC_DIR}/main.cpp
	${SRC_DIR}/Particles.hpp
	${SRC_DIR}/Particles.cpp
	${SRC_DIR}/Enemy.hpp
	${SRC_DIR}/Enemy.cpp
	${SRC_DIR}/Utils.hpp
	${SRC_DIR}/Utils.cpp
)

add_executable(TriangleSuper ${SOURCES})

# Link SFML and Thor
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message("\n-- Linking Thor and SFML in Release mode.")
    target_link_libraries(TriangleSuper ${SFML_GRAPHICS_LIBRARY_RELEASE} ${SFML_WINDOW_LIBRARY_RELEASE} ${SFML_AUDIO_LIBRARY_RELEASE} ${SFML_SYSTEM_LIBRARY_RELEASE})
    target_link_libraries(TriangleSuper ${THOR_LIBRARY_RELEASE})
else()
    message("\n-- Linking Thor and SFML in Debug mode.")
    target_link_libraries(TriangleSuper ${SFML_GRAPHICS_LIBRARY_DEBUG} ${SFML_WINDOW_LIBRARY_DEBUG} ${SFML_AUDIO_LIBRARY_DEBUG} ${SFML_SYSTEM_LIBRARY_DEBUG})
    target_link_libraries(TriangleSuper ${THOR_LIBRARY_DEBUG})
endif()

install(TARGETS TriangleSuper RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
install(DIRECTORY resources DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
