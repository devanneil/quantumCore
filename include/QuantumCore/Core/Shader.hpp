#pragma once
#define QUANTUM_SHADER

namespace Quantum
{
class Shader
{
public:
    Shader() = default;
private:
    void* _handle;
};

inline Shader createPinholeShader(const float FoV)
{   
    printf("THIS IS A TEMPORARY FUNCTION: createPinholeShader\n");
    Shader shader;
    return shader;
}

}