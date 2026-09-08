cmake_minimum_required(VERSION 3.15)
project(A2600-emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Source files, grouped by module for readability ----
set(PROCESSOR_SOURCES
    defs/Processor/CPURuntimeTypes.cpp
    defs/Processor/DecoderHelpers.cpp
    defs/Processor/InstructionDecoder.cpp
    defs/Processor/InstructionDefs.cpp
    defs/Processor/RegisterFile.cpp
)

set(MEMORY_SOURCES
    defs/Memory/MemoryRAM.cpp
)

set(MISC_SOURCES
    defs/Misc/BCDTypeDef.cpp
    defs/Misc/BinaryHelpers.cpp
)

# Assuming src/ holds your entry point (e.g. main.cpp)
file(GLOB SRC_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(A2600-emulator
    ${PROCESSOR_SOURCES}
    ${MEMORY_SOURCES}
    ${MISC_SOURCES}
    ${SRC_SOURCES}
)

target_include_directories(A2600-emulator PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Optional: makes Visual Studio's Solution Explorer mirror your
# on-disk folder structure instead of flattening everything
source_group(TREE ${CMAKE_SOURCE_DIR} FILES
    ${PROCESSOR_SOURCES}
    ${MEMORY_SOURCES}
    ${MISC_SOURCES}
    ${SRC_SOURCES}
)