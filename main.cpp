#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Math/Utils.hpp>
#include <QuantumCore/Window/Window.hpp>
#include <iostream>

int main()
{
    auto window = Quantum::Window::create({
        .title = "Quantum Engine",
        .width = 1280,
        .height = 720
    });

    auto window2 = Quantum::Window::create({
        .title = "Quantum Engine 2",
        .width = 1280,
        .height = 720
    });

    while (!window->shouldClose())
    {
        window->pollEvents();
        window2->pollEvents();
    }
}