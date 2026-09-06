#pragma once
#define QUANTUM_MESH

#include <array>
#include <cstdint>
#include <optional>
#include <vector>

#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Renderer/ResourceHandle.hpp>

namespace Quantum
{

constexpr size_t POSITION_SIZE = 3;
constexpr size_t NORMAL_SIZE   = 3;
constexpr size_t UV_SIZE       = 2;

template<size_t N>
using Attribute = std::vector<Vector<N, float>>;

class Mesh
{
private:
    Attribute<POSITION_SIZE> _vertices;

    std::optional<Attribute<NORMAL_SIZE>> _normals;
    std::optional<Attribute<UV_SIZE>> _texture_coordinates;

    std::vector<uint32_t> _triangle_indices;

    ResourceHandle& gpuResource;

public:
    Mesh() = default;

    Mesh(
        std::vector<Vector3<float>> vertices,
        std::vector<uint32_t> triangle_indices
    );

    ~Mesh();

    size_t vertexCount() const;
    size_t indexCount() const;

    size_t stride() const;

    static constexpr std::array<size_t, 3> get_attrib_descriptor()
    {
        return {POSITION_SIZE, NORMAL_SIZE, UV_SIZE};
    }
};

}