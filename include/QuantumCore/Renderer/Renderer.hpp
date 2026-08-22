#pragma once
#define QUANTUM_RENDERER
#include "RenderTarget.hpp"
#include <QuantumCore/Core/Shader.hpp>
#include <QuantumCore/Scene/Object.hpp>
#include <QuantumCore/Scene/Camera.hpp>
namespace Quantum
{
    /// @brief Quantum renderer class for rendering quantum objects
    class Renderer
    {
    private:
        class RenderImpl;

        std::unique_ptr<RenderImpl> _PImpl;

        std::shared_ptr<RenderTarget> _currentTarget;
        std::shared_ptr<Shader> _currentShader;

        Renderer();
        static std::unique_ptr<Renderer::RenderImpl> createImpl();
    public:
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        static Renderer& getInstance() {
            static Renderer instance; 
            return instance;
        }
        
        void renderPrimitive(/*QuantumPrimitive prim*/) const;
        void renderObject(QuantumObject mesh) const;
        void renderScene(/*QuantumScene scene,*/ RenderTarget& target, Camera& camera);

        void uploadShader(Shader& shader);
        std::unique_ptr<Shader> getShader() const;

        void setRenderTarget(RenderTarget& target);
        std::shared_ptr<RenderTarget> getRenderTarget() const;

        static void* compileShader(Shader& shader);
    };
} // namespace Quantum
