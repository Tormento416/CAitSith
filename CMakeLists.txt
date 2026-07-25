cmake_minimum_required(VERSION 3.16)
project(CAitSith VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Core Executable Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# FetchContent for automatic dependency fetching if system packages are missing
include(FetchContent)

# 1. GLFW
message(STATUS "Configuring GLFW...")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# 2. GLM (OpenGL Mathematics)
message(STATUS "Configuring GLM...")
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# 3. nlohmann_json
message(STATUS "Configuring nlohmann_json...")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Source files
set(SOURCES
    src/main.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/SculptEngine.cpp
    src/AIPipeline.cpp
    src/ViewportUI.cpp
)

set(HEADERS
    include/Camera.hpp
    include/Lighting.hpp
    include/Mesh.hpp
    include/SculptEngine.hpp
    include/AIPipeline.hpp
    include/ViewportUI.hpp
)

add_executable(CAitSith ${SOURCES} ${HEADERS})

target_include_directories(CAitSith PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(CAitSith PRIVATE
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
)

# Shader and asset copy rule
add_custom_command(
    TARGET CAitSith POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:CAitSith>/assets
)
