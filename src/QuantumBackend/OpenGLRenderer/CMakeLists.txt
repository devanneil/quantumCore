add_library(glad glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_library(
    QuantumGLBackend
    STATIC
)

target_sources(
    QuantumGLBackend
    PRIVATE
        OpenGlRenderer.cpp
)

target_link_libraries(
    QuantumGLBackend
    glad
)
target_include_directories(
    QuantumGLBackend
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_library(
    Quantum::GLBackend
    ALIAS QuantumGLBackend
)