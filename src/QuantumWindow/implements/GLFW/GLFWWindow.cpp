#include <QuantumCore/Window/Window.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "GLFWRenderTarget.cpp"
#include <cstdio>
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
        render_target_ = std::make_unique<GLFWRenderTarget>(GLFWRenderTarget(
            description.width,
            description.height,
            window_
        ));
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

    void updateTitle(char* title) override
    {
        glfwSetWindowTitle(window_, title);
    }
    void resize(uint32_t width, uint32_t height) override
    {
        glfwSetWindowSize(window_, width, height);
        render_target_->resize(width, height);
    }
    void present() const override
    {
        glfwSwapBuffers(window_);
    }

    RenderTarget& getRenderTarget() const override
    {
        return *render_target_;
    }
private:
    GLFWwindow* window_;
    std::unique_ptr<RenderTarget> render_target_;
};

std::unique_ptr<Window>
Window::create(const WindowDescription& description)
{
    if (!glfwInit())
    {
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Required for Mac
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
    #endif
    std::unique_ptr<GLFWWindow> window = std::make_unique<GLFWWindow>(description);

    ///TEMPORARY RENDERER INIT
    window->getRenderTarget().beginFrame();
    if (!gladLoadGL(
        reinterpret_cast<GLADloadfunc>(glfwGetProcAddress)))
    {
    printf("Failed to initialize GLAD");
    return nullptr;
    }
    
    return window;
}

}