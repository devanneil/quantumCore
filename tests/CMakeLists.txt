find_package(GTest REQUIRED)

add_executable(
    QuantumMathTests
    Math/MatrixUnitTests.cpp
    Math/MatrixFunctionTests.cpp
    Math/VectorUnitTests.cpp
    Math/VectorFunctionTests.cpp
)

target_link_libraries(
    QuantumMathTests
    PRIVATE
    Quantum::Math
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(QuantumMathTests)