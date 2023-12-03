#pragma once

#include <string>
#include <vector>
#include <filesystem>

enum class RWS : short int
{
    READ, WRITE, STRING, UNCERTAIN
};

struct Command
{
    Command() = delete;
    Command(const std::string& command_line);

    RWS command;
    short int arg1;
    short int arg2;
};

using test_t = std::pair<std::string, std::vector<Command>>; //pair of task description and vector of commands