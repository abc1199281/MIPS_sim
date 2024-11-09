#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <cstdint>
#include <regex>

class Parser
{
public:
    std::vector<std::string> parse(const std::string str);

    // TODO: how to move these functions into private while keeping unit test?
    std::string trim_space(const std::string &str);
    std::string remove_comments(const std::string &input);
    std::vector<std::string> split(const std::string str);

private:
    static const std::regex delimiter;
    static const std::regex rest_of_line;
    static const std::regex partial_in_line;
    static const std::regex multi_line_begin;
    static const std::regex multi_line_end;
    bool is_in_comment = false;
};

#endif // __PARSER_H__