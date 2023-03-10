#include <catch2/catch.hpp>
#include <iostream>

#include "mips_sim/assembler/parser.h"

//----------------------------------------------------------------------------
TEST_CASE("parse string", "[parser]")
{
    Parser parser;
    std::string test_input = "add $s1 , $s2, $s3 #";
    std::vector<std::string> expected_output =
        {"add", "$s1", "$s2", "$s3"};
    std::vector<std::string> rtn = parser.parse(test_input);

    REQUIRE(expected_output.size() == rtn.size());

    for (int i = 0; i < rtn.size(); i++)
    {
        REQUIRE(rtn.at(i) == expected_output.at(i));
    }
}

//----------------------------------------------------------------------------
TEST_CASE("rest of line", "[comment_remover]")
{
    Parser parser;
    std::string test_input = "add $s1 , $s2, $s3 #";
    std::string expected_output = "add $s1 , $s2, $s3 ";
    std::string rtn = parser.remove_comments(test_input);

    REQUIRE(expected_output.compare(rtn) == 0);
}
//----------------------------------------------------------------------------

TEST_CASE("partial in line", "[comment_remover]")
{
    Parser parser;
    std::string test_input = "add $s1 /*, $s2, $s3*/, $s2, $s3";
    std::string expected_output = "add $s1 , $s2, $s3";
    std::string rtn = parser.remove_comments(test_input);
    REQUIRE(expected_output.compare(rtn) == 0);
}

//----------------------------------------------------------------------------
TEST_CASE("multi lines", "[comment_remover]")
{
    Parser parser;
    std::string test_input1 = "add $s1 /*comments";
    std::string test_input2 = "comments */, $s2, $s3";
    std::string expected_output1 = "add $s1 ";
    std::string expected_output2 = ", $s2, $s3";
    std::string rtn1 = parser.remove_comments(test_input1);
    std::string rtn2 = parser.remove_comments(test_input2);

    REQUIRE(expected_output1.compare(rtn1) == 0);
    REQUIRE(expected_output2.compare(rtn2) == 0);
}
//----------------------------------------------------------------------------