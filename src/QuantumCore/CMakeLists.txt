add_library(
    QuantumCamera
    STATIC
)
target_sources(QuantumCamera PRIVATE
    QuantumScene/CameraUtils.cpp
)
target_include_directories(
    QuantumCamera
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
add_library(
    Quantum::Scene::Camera
    ALIAS QuantumCamera
)