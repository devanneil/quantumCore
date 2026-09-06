add_library(
    QuantumWindowGLFW
)

target_sources(QuantumWindowGLFW PRIVATE
    implements/GLFW/GLFWWindow.cpp
)

target_include_directories(
    QuantumWindowGLFW
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_library(
    Quantum::Window::GLFW
    ALIAS QuantumWindowGLFW
)
find_package(glfw3 3.4 REQUIRED)

target_link_libraries(
    QuantumWindowGLFW
    PUBLIC
        glfw
)