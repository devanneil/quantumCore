cmake_minimum_required(VERSION 3.24)

project(
    QuantumCore
    VERSION 0.1.0
    LANGUAGES CXX
)

#
# C++ Settings
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/QuantumBackend)
add_subdirectory(src/QuantumCore)
add_subdirectory(src/QuantumGraphics)
add_subdirectory(src/QuantumMath)
add_subdirectory(src/QuantumWindow)

option(QUANTUM_BUILD_TESTS "Build QuantumCore tests" ON)

if(QUANTUM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_executable(tempExe main.cpp)

target_link_libraries(tempExe
 Quantum::Math
)


