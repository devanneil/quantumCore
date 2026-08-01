#ifndef QUANTUM_SHADER
#define QUANTUM_SHADER

namespace Quantum
{
class Shader
{
public:
    Shader() = default;
    //char* compileString();
};

inline Shader createPinholeShader(const float FoV)
{   
    printf("THIS IS A TEMPORARY FUNCTION: createPinholeShader\n");
    Shader shader;
    return shader;
}

}
#endif