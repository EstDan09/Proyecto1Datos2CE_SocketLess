set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Proyecto1Datos2CE_Cliente)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(Proyecto1Datos2CE_Cliente main.cpp Entity.cpp Entity.h Background.cpp Background.h Player.cpp Player.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h Declarations.h Ammunation.cpp BulletCollector.cpp BulletD.cpp InGame.cpp ShipEnemy.cpp ShipPlayer.cpp Waves.cpp Strategys.cpp InformationNode.cpp InformationNode.h)
#set(raylib_VERBOSE 1)
target_link_libraries(Proyecto1Datos2CE_Cliente raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
# Encuentra Doxygen y genera la documentación
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/path/to/your/code)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    set(DOXYGEN_PROJECT_NAME "MyProject")
    set(DOXYGEN_PROJECT_VERSION "1.0")
    set(DOXYGEN_EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/path/to/examples)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_GENERATE_LATEX YES)
    set(DOXYGEN_OUTPUT_FORMAT html latex man)
    set(DOXYGEN_RECURSIVE YES)
    doxygen_add_docs(docs ${DOXYGEN_INPUT})
endif(DOXYGEN_FOUND)
