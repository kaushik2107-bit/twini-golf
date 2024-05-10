cmake_minimum_required(VERSION 3.27)
project(golf VERSION 0.1 LANGUAGES C CXX)

# ---- Set C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# ---- Name of executable ----
set(EXEC "golf")

# ---- External Directories ----
include_directories(lib/glad/include)

# ---- Define the executable target ----
add_executable(${EXEC} src/renderer.cpp src/load_assets.cpp src/init.cpp src/loader.cpp src/main.cpp lib/glad/src/glad.c)

# ---- Set compiler flags for Debug and Release builds ----
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # ---- Debug build ----
    message("Debug build")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od /Wall /Zi /fsanitize=address")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
    endif()
else()
    # ---- Release build ----
    message("Release build")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    endif()
endif()

# ---- Specify additional flags for specific compilers or platforms ----
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

target_link_libraries(${EXEC} -lSDL2 -lSDL2_ttf -lSDL2_image -ldl)
