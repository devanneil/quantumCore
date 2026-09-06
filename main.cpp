#define GLFW_INCLUDE_GLCOREARB
#include <glad/gl.h>
#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Math/Utils.hpp>
#include <QuantumCore/Window/Window.hpp>
#include <QuantumCore/Scene/Camera.hpp>
#include <QuantumCore/Renderer/Renderer.hpp>
#include <iostream>
#include <fstream>
#include <sstream>


static void ParseShader(const std::string& file_path, std::string& vertexShader, std::string& fragmentShader)
{
    std::ifstream fstream(file_path);
    if (!fstream)
    {
        printf("File open failure: ");
        printf(file_path.c_str());
        printf("\n");
        return;
    }
    enum class ShaderType 
    {
        NONE = -1, VERTEX = 0, SHADER = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(fstream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else
            {
                type = ShaderType::SHADER;
            }
        }
        else
        {
            if (type != ShaderType::NONE)
            {
                ss[(int)type] << line << '\n';
            }
        }
    }
    vertexShader += ss[0].str();
    fragmentShader += ss[1].str();
}

static unsigned int CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msg);
        std::cout << "Failed to comile " << 
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader: " <<std::endl;
        std::cout << msg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
static unsigned int CreateShader(
    const std::string& vertexShader,
    const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    if (!vs || !fs)
    {
        std::cerr << "Shader compilation failed.\n";
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::string message(length, '\0');
        glGetProgramInfoLog(
            program,
            length,
            nullptr,
            message.data()
        );

        std::cerr << "Shader program failed to link:\n"
                  << message << '\n';

        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);

        return 0;
    }

    glValidateProgram(program);

    int validated;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &validated);

    if (!validated)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::string message(length, '\0');
        glGetProgramInfoLog(
            program,
            length,
            nullptr,
            message.data()
        );

        std::cerr << "Shader program failed validation:\n"
                  << message << '\n';
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



int main()
{
    auto window = Quantum::Window::create({
        .title = "Quantum Engine",
        .width = 1280,
        .height = 720
    });

    if(!window) {
        return -1;
    }
    // auto window2 = Quantum::Window::create({
    //     .title = "Quantum Engine 2",
    //     .width = 1280,
    //     .height = 720
    // }, Quantum::createPinholeCamera(cameraTF, 70));

    auto& renderingTarget1 = window->getRenderTarget();
    // auto& renderingTarget2 = window2->getRenderTarget();

    std::vector<Quantum::Vector4<float>> Cube =
    {
    Quantum::Vector4<float>({-0.5, -0.5, 0.5, 1.0}),
    Quantum::Vector4<float>({-0.5, 0.5, 0.5, 1.0}),
    Quantum::Vector4<float>({0.5, 0.5, 0.5, 1.0}),
    Quantum::Vector4<float>({0.5, -0.5, 0.5, 1.0}),
    Quantum::Vector4<float>({-0.5, -0.5, -0.5, 1.0}),
    Quantum::Vector4<float>({-0.5, 0.5, -0.5, 1.0}),
    Quantum::Vector4<float>({0.5, 0.5, -0.5, 1.0}),
    Quantum::Vector4<float>({0.5, -0.5, -0.5, 1.0})
    };
    std::vector<unsigned int> indices
    {
    1, 0, 3,
    3, 2, 1,
    2, 3, 7,
    7, 6, 2,
    3, 0, 4,
    4, 7, 3,
    6, 2, 1,
    1, 5, 6,
    4, 5, 6,
    6, 7, 4,
    5, 4, 0,
    0, 1, 5
    };
    const float aspect = 1280.0f / 720.0f;
    auto cameraMatrix = Quantum::lookAtMatrix({10.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    auto perspectiveMatrix = Quantum::projectionMatrix(45.0 * M_PI / 180.0, aspect, 0.1, 100.0);
    auto modelMatrix = Quantum::identityMatrix<float>();

    renderingTarget1.beginFrame();

    glViewport(0, 0, 1280, 720);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int cubeBuffer;
    glGenBuffers(1, &cubeBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 4,
        nullptr
    );

    glEnableVertexAttribArray(0);
    std::string vertex_shader = "";
    std::string fragment_shader = "";
    ParseShader("../tempShader.txt", vertex_shader, fragment_shader);
    unsigned int shader = CreateShader(vertex_shader, fragment_shader);
    glUseProgram(shader);

    GLint modelLoc = glGetUniformLocation(shader, "model");
    GLint viewLoc  = glGetUniformLocation(shader, "view");
    GLint projLoc  = glGetUniformLocation(shader, "projection");

    float currentAngle = 0;
    float radPerSeconds = 0.1;
    std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    while (true)
    {
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - last_time).count();
        last_time = now;

        currentAngle += radPerSeconds * dt;

        auto tfMat = Quantum::RotationMatrix<float>(currentAngle * 0.1, currentAngle * 0.5, currentAngle);
        auto cubeInstance = Cube;
        for (int i = 0; i < Cube.size(); i++)
        {
            cubeInstance[i] = Quantum::rightSideVectorMultiply<float>(tfMat, Cube[i]);
        }
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.data());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cameraMatrix.data());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, perspectiveMatrix.data());
        window->pollEvents();
        //window2->pollEvents();

        if (window->shouldClose() /*|| window2->shouldClose()*/) break;
        renderingTarget1.beginFrame();
        //renderer.render(scene, target, camera);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glBufferData(
            GL_ARRAY_BUFFER,
            cubeInstance.size() * sizeof(Quantum::Vector4<float>),
            cubeInstance.data()->data(),
            GL_STATIC_DRAW
        );
        glDrawElements(
            GL_TRIANGLES, 
            indices.size(), 
            GL_UNSIGNED_INT, 
            nullptr
        );
        renderingTarget1.endFrame();
        window->present();
        //window2->present();

        // if(renderer->pollError())
        // {
        //     std::cerr << render->getError() << std::endl;
        // }
        while (GLenum error = glGetError())
        {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
    }
}