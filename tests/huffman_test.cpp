#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/huffman.hpp"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("compression/decompression")
{
    string text = "Hello World";

    auto result = compress(text);
    auto restored = decompress(result.compressed, result.codes);

    REQUIRE(restored == text);
}

TEST_CASE("empty string")
{
    string text = "";
    auto result = compress(text);
    auto restored = decompress(result.compressed, result.codes);
    REQUIRE(restored == text);
}