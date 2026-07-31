#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Math/Utils.hpp>
#include <QuantumCore/Window/Window.hpp>
#include <iostream>

#include <OpenGL/gl.h>

void beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f( 0.0f,  0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f( 0.5f, -0.5f);

    glEnd();
}

void drawOtherTriangle()
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f( 0.0f,  0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f( 0.5f, -0.5f);

    glEnd();
}

void endFrame()
{
    glFlush();
}

int main()
{
    auto window = Quantum::Window::create({
        .title = "Quantum Engine",
        .width = 1280,
        .height = 720
    });
    if(!window) {
        return -1;
    }

    auto window2 = Quantum::Window::create({
        .title = "Quantum Engine 2",
        .width = 1280,
        .height = 720
    });

    while (!window->shouldClose())
    {
        window->pollEvents();
        window2->pollEvents();

        beginFrame();
        clear();
        drawTriangle();
        endFrame();
        window->present();

        beginFrame();
        clear();
        drawOtherTriangle();
        endFrame();
        window2->present();
    }
}