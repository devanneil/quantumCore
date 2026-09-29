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

size_t alignUp(size_t offset, size_t alignment)
{
    return (offset + alignment - 1) / alignment * alignment;
}

class Mesh
{
    private:
    struct VertexAttribute_t {
        int id;
        size_t size;
        size_t offset;
        size_t alignment;
        VertexAttribute_t() = default;
    };
    std::vector<VertexAttribute_t> attributes;
    std::vector<std::byte> vertex_data;
    size_t vertex_size;
    size_t vertex_count;

    public:
    template<typename T>
    struct VertexAttribute : VertexAttribute_t{
        VertexAttribute(int id)
        {
            static_assert(std::is_trivially_copyable_v<T>);
            this->id = id;
            this->size = sizeof(T);
            this->offset = 0;
            this->alignment = alignof(T);
        }
    };

    struct Vertex{
        Vertex(std::byte* data)
        {
            this->data = data;
        }

        template<typename T>
        void set(const VertexAttribute<T>& attribute, const T& data)
        {
            std::memcpy(this->data + attribute.offset, &data, attribute.size);
        }

        template<typename T>
        T get(const VertexAttribute<T>& attribute)
        {
            T ret;
            std::memcpy(&ret, this->data + attribute.offset, attribute.size);
            return ret;
        }

        template<typename T>
        const T get(const VertexAttribute<T>& attribute) const
        {
            T ret;
            std::memcpy(&ret, this->data + attribute.offset, attribute.size);
            return ret;
        }

        template<typename T>
        const T operator[](const VertexAttribute<T>& attribute) const {return get(attribute);};

        private:
        std::byte* data;
    };

    Mesh(std::vector<VertexAttribute_t> attributes, int vertex_count)
    {
        size_t offset = 0;
        for (auto& attribute : attributes)
            this->attributes.emplace_back(VertexAttribute_t(attribute));
        for (auto& attribute : this->attributes)
        {
            offset = alignUp(offset, attribute.alignment);
            
            attribute.offset = offset;

            offset += attribute.size;
        }

        this->vertex_size = offset;
        this->vertex_count = vertex_count;

        this->vertex_data.resize(this->vertex_size * vertex_count);
    }

    Vertex getVertex(size_t ind)
    {
        if(ind >= vertex_count)
        {
            throw std::out_of_range("Vertex index out of bounds!");
        }
        return Vertex(vertex_data.data() + ind * vertex_size);
    }

    const std::byte* getVertexData() const
    {
        return vertex_data.data();
    }

    size_t size()
    {
        return vertex_data.size() * sizeof(std::byte);
    }

    std::vector<VertexAttribute_t> getAttributeArray()
    {
        return this->attributes;
    }

    Vertex operator[](size_t ind) {return getVertex(ind);};
};
}