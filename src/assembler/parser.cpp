#include <iostream>
#include <list>
#include "mips_sim/assembler/parser.h"

//----------------------------------------------------------------------------
const std::regex Parser::delimiter{"(\\s*,\\s*|\\s)"};
const std::regex Parser::rest_of_line{"(//|#)"};
const std::regex Parser::partial_in_line{"(/\\*.*\\*/)"};
const std::regex Parser::multi_line_begin{"(/\\*.*(?!\\*/))"};
const std::regex Parser::multi_line_end{"((?!/\\*).*\\*/)"};

//----------------------------------------------------------------------------
std::vector<std::string> Parser::parse(const std::string str)
{
    std::string trim_str = remove_comments(str);
    trim_str = trim_space(trim_str);
    return split(trim_str);
}

//----------------------------------------------------------------------------

std::vector<std::string> Parser::split(const std::string str)
{
    std::vector<std::string> tokens;
    std::sregex_token_iterator rit(str.begin(), str.end(), delimiter, -1);
    std::remove_copy_if(rit, std::sregex_token_iterator(),
                        std::back_inserter(tokens),
                        [](std::string const &s)
                        { return s.empty(); });
    return tokens;
}

//----------------------------------------------------------------------------
std::string Parser::trim_space(const std::string &str)
{
    const std::string &whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

//----------------------------------------------------------------------------

std::string Parser::remove_comments(const std::string &input)
{
    std::smatch match;

    const auto search = [&match, &input](const std::regex &re)
    { return std::regex_search(input, match, re); };

    if (is_in_comment && search(multi_line_end))
    {
        is_in_comment = false;
        return remove_comments(match.suffix().str());
    }
    else if (search(partial_in_line))
        return match.prefix().str() + remove_comments(match.suffix().str());
    else if (search(rest_of_line))
        return match.prefix().str();
    else if (search(multi_line_begin))
    {
        is_in_comment = true;
        return match.prefix().str();
    }

    return input;
}
//----------------------------------------------------------------------------