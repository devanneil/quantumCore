add_library(
    QuantumMath
    STATIC
)

target_sources(
    QuantumMath
    PRIVATE
        quantumLinearMath.cpp
)

target_include_directories(
    QuantumMath
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_library(
    Quantum::Math
    ALIAS QuantumMath
)