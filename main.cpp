#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Math/Utils.hpp>
#include <QuantumCore/Window/Window.hpp>
#include <QuantumCore/Scene/Camera.hpp>
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
    Quantum::Matrix4<float> cameraTF{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    auto window = Quantum::Window::create({
        .title = "Quantum Engine",
        .width = 1280,
        .height = 720
    }, Quantum::createPinholeCamera(cameraTF, 45));
    if(!window) {
        return -1;
    }

    auto window2 = Quantum::Window::create({
        .title = "Quantum Engine 2",
        .width = 1280,
        .height = 720
    }, Quantum::createPinholeCamera(cameraTF, 70));

    auto& renderingTarget1 = window->getRenderTarget();
    auto& renderingTarget2 = window2->getRenderTarget();
    while (true)
    {
        window->pollEvents();
        window2->pollEvents();

        if (window->shouldClose() || window2->shouldClose()) break;

        //renderer.beginFrame(renderingTarget1);
        renderingTarget1.beginFrame();
        clear();
        drawTriangle();
        endFrame();
        //renderer.endFrame(renderingTarget1);
        renderingTarget1.endFrame();
        window->present();

        renderingTarget2.beginFrame();
        beginFrame();
        clear();
        drawOtherTriangle();
        endFrame();
        renderingTarget2.endFrame();
        window2->present();
    }
}