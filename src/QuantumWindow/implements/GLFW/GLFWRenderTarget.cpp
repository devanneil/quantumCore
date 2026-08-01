#include <QuantumCore/Renderer/RenderTarget.hpp>
#include <QuantumCore/Scene/Camera.hpp>
#include <GLFW/glfw3.h>

namespace Quantum {

class GLFWRenderTarget final : public RenderTarget
{
    public:
    GLFWRenderTarget(const Camera& camera, const size_t width, const size_t height, GLFWwindow* window_handle)
    {
        camera_ = camera;
        width_ = width;
        height_ = height;
        window_handle_ = window_handle;
    }
    ~GLFWRenderTarget() = default;

    void beginFrame() const
    {
        glfwMakeContextCurrent(window_handle_);
    }
    void endFrame() const
    {

    }

    uint32_t width() const
    {
        return width_;
    }
    uint32_t height() const
    {
        return height_;
    }

    void resize(uint32_t width, uint32_t height)
    {
        width_ = width;
        height_ = height;
    }

    Camera& getCamera()
    {
        return camera_;
    }

    private:
    uint32_t width_;
    uint32_t height_;
    Camera camera_;
    GLFWwindow* window_handle_;
};

}