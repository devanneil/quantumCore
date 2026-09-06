#pragma once
#define QUANTUM_RESOURCE_HANDLE
#include <cstdint>
namespace Quantum {

struct ResourceHandle
{
    uint64_t id = 0;
    bool valid = false;
};

}