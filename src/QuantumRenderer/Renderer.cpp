
#include <QuantumCore/Renderer/Renderer.hpp>

namespace Quantum {

class Renderer::RenderImpl
{   
    virtual ~RenderImpl();

    virtual void beginFrame(RenderTarget& target) const;
    virtual void endFrame(RenderTarget& target) const;

    virtual void uploadObject(QuantumObject& object);
    virtual void useShader(Shader& shader);
};

Renderer::Renderer() 
{
    _PImpl = createImpl();
    _currentTarget = {};
    _currentShader = {};
}

Renderer::~Renderer() 
{

}

void Renderer::renderPrimitive(/*QuantumPrimitive prim*/) const 
{

}

void Renderer::renderObject(/*QuantumObject mesh*/) const 
{

}

void Renderer::renderScene(/*QuantumScene scene,*/ RenderTarget& target, Camera& camera) 
{

}

void Renderer::uploadShader(Shader& shader) 
{

}

std::unique_ptr<Shader> Renderer::getShader() const 
{
    std::unique_ptr<Shader> returnValue;
    return returnValue;
}

void Renderer::setRenderTarget(RenderTarget& target) 
{

}

std::shared_ptr<RenderTarget> Renderer::getRenderTarget() const 
{
    std::shared_ptr<RenderTarget> returnValue;
    return returnValue;
}

void* Renderer::compileShader(Shader& shader) 
{
    void* returnValue;
    return returnValue;
}

}