#pragma once

#include <cstdint>
#include <memory>

namespace Quantum {

struct WindowDescription
{
    const char* title;
    uint32_t width;
    uint32_t height;
};

class Window
{
public:
    virtual ~Window() = default;

    virtual void pollEvents() = 0;
    virtual bool shouldClose() const = 0;

    virtual uint32_t width() const = 0;
    virtual uint32_t height() const = 0;

    static std::unique_ptr<Window> create(
        const WindowDescription& description
    );
};
}