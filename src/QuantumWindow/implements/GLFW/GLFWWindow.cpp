#include <QuantumCore/Window/Window.hpp>
#include <GLFW/glfw3.h>

namespace Quantum {

class GLFWWindow final : public Window
{
public:
    explicit GLFWWindow(const WindowDescription& description)
    {
        window_ = glfwCreateWindow(
            description.width,
            description.height,
            description.title,
            nullptr,
            nullptr
        );
    }

    ~GLFWWindow() override
    {
        glfwDestroyWindow(window_);
    }

    void pollEvents() override
    {
        glfwPollEvents();
    }

    bool shouldClose() const override
    {
        return glfwWindowShouldClose(window_);
    }

    uint32_t width() const override
    {
        int width;
        int height;
        glfwGetWindowSize(window_, &width, &height);
        return static_cast<uint32_t>(width);
    }

    uint32_t height() const override
    {
        int width;
        int height;
        glfwGetWindowSize(window_, &width, &height);
        return static_cast<uint32_t>(height);
    }

private:
    GLFWwindow* window_;
};

std::unique_ptr<Window>
Window::create(const WindowDescription& description)
{
    if (!glfwInit())
    {
        return nullptr;
    }
    return std::make_unique<GLFWWindow>(description);
}

}