#pragma once
#define QUANTUM_RENDER_TARGET
#include <cstdint>
#include <memory>
namespace Quantum {

struct RenderTargetDescription{
    uint32_t width;
    uint32_t height;
};

class RenderTarget
{
public:
    virtual ~RenderTarget() = default;

    virtual void beginFrame() const = 0;
    virtual void endFrame() const = 0;

    virtual uint32_t width() const = 0;
    virtual uint32_t height() const = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;

    static std::unique_ptr<RenderTarget> create(
        const RenderTargetDescription& description
    );
};
}