#include <catch2/catch.hpp>
#include "mips_sim/utils.h"

//----------------------------------------------------------------------------
TEST_CASE("negative sign extension", "[utils]")
{
    uint32_t input_bin = 0b1001100110011001;
    uint32_t expected_output_bin = 0b11111111111111111001100110011001;
    uint32_t output_bin = sign_extension(input_bin);

    REQUIRE(expected_output_bin == output_bin);
}
//----------------------------------------------------------------------------

TEST_CASE("positive sign extension", "[utils]")
{
    uint32_t input_bin = 0b0001100110011001;
    uint32_t expected_output_bin = 0b00000000000000000001100110011001;
    uint32_t output_bin = sign_extension(input_bin);

    REQUIRE(expected_output_bin == output_bin);
}
//----------------------------------------------------------------------------