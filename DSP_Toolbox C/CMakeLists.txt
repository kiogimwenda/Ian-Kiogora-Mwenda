# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name and specify C as the language
project(DSP_Toolbox C)

# Set the C standard (here C99)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set the output directory for the executable to the 'bin' folder in the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include the 'include' directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all source files from the src directory
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Create the executable from the source files
add_executable(dsp_demo ${SOURCES})

# Link against the math library (needed for functions like sin, cos, etc.)
#target_link_libraries(dsp_demo m)
